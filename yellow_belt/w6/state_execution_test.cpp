//
// Created by dkushn on 04.09.19.
//

#include "condition_parser.h"
#include "test_runner.h"
#include "database.h"
#include "condition_parser.h"
#include "event_parser.h"

#include <sstream>
using namespace std;

int DB_Instance_Tester(const vector<string> &commands){

    Database db;

    for (const string &line : commands) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);

        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;

        } else if (command == "Find") {

            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestExecutionStates() {
    {
        vector<string> test_fixture{
                "Add 2017-11-21 Tuesday",
                "Add 2017-11-20 one",
                "Add 2017-11-20 two",
                "Add 2017-11-20 three",
                "Add 2017-11-20 four",
                "Add 2017-11-21 Weekly meeting",
                "Last 2017-11-20",
                "Print",
                "Find event == \"four\"",
                "Del event == \"two\"",
                "Last 2017-11-20",
                "Find event == \"four\"",
                "Del event == \"four\"",
                "Find event == \"four\"",
                "Print",
                "Last 2017-11-20",
                "Last 2017-11-01",
        };
        DB_Instance_Tester(test_fixture);
        vector<string> expeced{
                "2017-11-21 Weekly meeting",
                "Removed 2 entries",
                "2017-11-20 Monday",
                "No entries"
        };
        cout << endl << endl;
        for (const auto& line: expeced){
            cout << line << endl;
        }

    }


}
