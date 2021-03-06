//
// Created by dkushn on 12.09.19.
//



//template <typename Container, typename ForwardIt>
//ForwardIt LoopIterator(Container& container, ForwardIt pos) {
//    return pos == container.end() ? container.begin() : pos;
//}
//
//template <typename RandomIt>
//void MakeJosephusPermutation(RandomIt first, RandomIt last,
//                             uint32_t step_size) {
//    list<typename RandomIt::value_type> pool;
//    for (auto it = first; it != last; ++it) {
//        pool.push_back(move(*it));
//    }
//
//    auto cur_pos = pool.begin();
//    while (!pool.empty()) {
//        *(first++) = move(*cur_pos);
//        if (pool.size() == 1) {
//            break;
//        }
//        const auto next_pos = LoopIterator(pool, next(cur_pos));
//        pool.erase(cur_pos);
//        cur_pos = next_pos;
//        for (uint32_t step_index = 1; step_index < step_size; ++step_index) {
//            cur_pos = LoopIterator(pool, next(cur_pos));
//        }
//    }
//}