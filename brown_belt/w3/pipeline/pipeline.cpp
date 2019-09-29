#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
private: unique_ptr<Worker> next_{nullptr};
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
    throw logic_error("Unimplemented");
  }

protected:
  void PassOn(unique_ptr<Email> email) const{
      if (next_){
          next_->Process(move(email));
      }
  }

public:
  void SetNext(unique_ptr<Worker> next){
      next_ = move(next);
  }
};


class Reader : public Worker {
public:
    Reader(istream& is) : is_{is}
    {
    }
    void Run() override {
        unique_ptr<Email> new_em = make_unique<Email>();
        while (
                getline(is_, new_em->from) &&
                getline(is_, new_em->to) &&
                getline(is_, new_em->body)
                )
        {
            PassOn(move(new_em));
            new_em = make_unique<Email>();
        }
    }
    void Process(unique_ptr<Email> email = nullptr) override {
        Run();
    };
private:
    istream& is_;
};


class Filter : public Worker {
public:
  using Predicate = function<bool(const Email&)>;
    Filter(Predicate pred)
    : pred_( move(pred) )
    {
    }

public:
    void Process(unique_ptr<Email> email) override {
        if (pred_(*email))
            PassOn(move(email));
    };
private:
    Predicate pred_;
};


class Copier : public Worker {
public:
    Copier(string new_receiver_address) : additional_receiver_address_{move(new_receiver_address)}
    {
    }
    void Process(unique_ptr<Email> email) override {
        if (email->to != additional_receiver_address_){
            Email copy {email->from, additional_receiver_address_, email->body};
            PassOn( move(email) );
            PassOn( make_unique<Email>(copy) );
        }
        else {
            PassOn(move(email));
        }
    };
private:
    const string additional_receiver_address_;
};


class Sender : public Worker {
public:
    Sender(ostream& os) : os_{os}
    {
    }
    void Process(unique_ptr<Email> email) override {
        os_.write(email->from.c_str(), email->from.size());
        os_ << endl;
        os_.write(email->to.c_str(), email->to.size());
        os_ << endl;
        os_.write(email->body.c_str(), email->body.size());
        os_ << endl;
        PassOn(move(email));
    };
private:
    ostream& os_;
};


class PipelineBuilder {
public:
  explicit PipelineBuilder(istream& in)
  : head_{make_unique<Reader>(in)}
  {
  }

  PipelineBuilder& FilterBy(Filter::Predicate filter){
      pipeline_.push_back(make_unique<Filter>(filter));
      return *this;
  }

  PipelineBuilder& CopyTo(string recipient) {
      pipeline_.push_back(make_unique<Copier>(move(recipient)));
      return *this;
  }

  PipelineBuilder& Send(ostream& out){
      pipeline_.push_back(make_unique<Sender>(out));
      return *this;
  }

  unique_ptr<Worker> Build(){
      if (!pipeline_.empty()){
          unique_ptr<Worker> old_tail = move(pipeline_.back());
          pipeline_.pop_back();
          unique_ptr<Worker> new_tail;
          while(!pipeline_.empty()){
              new_tail = move(pipeline_.back());
              new_tail->SetNext(move(old_tail));
              old_tail = move(new_tail);
              pipeline_.pop_back();
          }
          head_->SetNext(move(old_tail)); //
      }
      return move(head_);
  }

private:
    list<unique_ptr<Worker>> pipeline_;
  unique_ptr<Worker> head_;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
