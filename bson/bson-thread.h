/*
 * Copyright 2013 10gen Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BSON_THREAD_H
#define BSON_THREAD_H


#include "bson-config.h"
#include "bson-macros.h"


BSON_BEGIN_DECLS


#if defined(HAVE_PTHREADS)

#include <pthread.h>
#define bson_mutex_t       pthread_mutex_t;
#define bson_mutex_init    pthread_mutex_init
#define bson_mutex_lock    pthread_mutex_lock
#define bson_mutex_unlock  pthread_mutex_unlock
#define bson_thread_t      pthread_t
#define bson_thread_create pthread_create
#define bson_thread_join   pthread_join

#elif defined(HAVE_WINDOWS)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef  WIN32_LEAN_AND_MEAN
#else
#include <windows.h>
#endif
#define bson_mutex_t                 HANDLE
#define bson_mutex_init(m)           CreateMutex(NULL, FALSE, NULL)
#define bson_mutex_lock(m)           WaitforSingleObject((m))
#define bson_mutex_unlock(m)         ReleaseMutex((m))
#define bson_mutex_destroy(m)        CloseHandle((m))
#define bson_thread_t                HANDLE
#define bson_thread_create(t,a,f,d)  (*(t) = CreateThread(NULL, 0, (void*)f, d, 0, NULL))
#define bson_thread_join(t,v)        WaitForSingleObject(t, 0)

#endif


BSON_END_DECLS


#endif /* BSON_THREAD_H */
