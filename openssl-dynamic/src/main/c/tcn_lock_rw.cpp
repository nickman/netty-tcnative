/*
 * Copyright 2017 The Netty Project
 *
 * The Netty Project licenses this file to you under the Apache License,
 * version 2.0 (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
#include "tcn_lock_rw.h"
#include <shared_mutex>

tcn_lock_rw_t tcn_lock_rw_new() {
    auto *m = new std::shared_timed_mutex();
    return (tcn_lock_rw_t) m;
}

void tcn_lock_rw_free(tcn_lock_rw_t lock) {
    auto *m = (std::shared_timed_mutex *) lock;
    delete m;
}

tcn_lock_writer_t tcn_lock_writer_acquire(tcn_lock_rw_t lock) {
    auto *m = (std::shared_timed_mutex *) lock;
    auto *writer_lock = new std::lock_guard<std::shared_timed_mutex>(*m);
    return (tcn_lock_writer_t) writer_lock;
}

void tcn_lock_writer_release(tcn_lock_writer_t lock) {
    auto *writer_lock = (std::lock_guard<std::shared_timed_mutex> *) lock;
    delete writer_lock;
}

tcn_lock_reader_t tcn_lock_reader_acquire(tcn_lock_rw_t lock) {
    auto *m = (std::shared_timed_mutex *) lock;
    auto *reader_lock = new std::shared_lock<std::shared_timed_mutex>(*m);
    return (tcn_lock_reader_t) reader_lock;
}

void tcn_lock_reader_release(tcn_lock_reader_t lock) {
    auto *reader_lock = (std::shared_lock<std::shared_timed_mutex> *) lock;
    delete reader_lock;
}
