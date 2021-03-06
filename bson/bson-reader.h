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


#ifndef BSON_READER_H
#define BSON_READER_H


#include "bson-oid.h"
#include "bson-types.h"


BSON_BEGIN_DECLS


/**
 * bson_reader_init_from_fd:
 * @reader: A bson_reader_t
 * @fd: A file-descriptor to read from.
 * @close_fd: If the file-descriptor should be closed when done.
 *
 * Initializes new bson_reader_t that will read BSON documents into bson_t
 * structures from an underlying file-descriptor.
 *
 * If you would like the reader to call close() on @fd in
 * bson_reader_destroy(), then specify TRUE for close_fd.
 */
void
bson_reader_init_from_fd (bson_reader_t *reader,
                          int            fd,
                          bson_bool_t    close_fd);


/**
 * bson_reader_t:
 * @reader: A bson_reader_t.
 * @data: A buffer to read BSON documents from.
 * @length: The length of @data.
 *
 * Initializes bson_reader_t that will read BSON documents from a memory
 * buffer.
 */
void
bson_reader_init_from_data (bson_reader_t      *reader,
                            const bson_uint8_t *data,
                            size_t              length);



/**
 * bson_reader_destroy:
 * @reader: An initialized bson_reader_t.
 *
 * Releases resources that were allocated during the use of a bson_reader_t.
 * This should be called after you have finished using the structure.
 */
void
bson_reader_destroy (bson_reader_t *reader);


/**
 * bson_reader_read:
 * @reader: A bson_reader_t.
 *
 * Reads the next bson_t in the underlying memory or storage.
 * The resulting bson_t should not be modified or freed. You may
 * copy it and iterate over it. Functions that take a
 * const bson_t* are safe to use.
 *
 * This structure does not survive calls to bson_reader_next() or
 * bson_reader_destroy() as it uses memory allocated by the reader
 * or underlying storage/memory.
 *
 * Returns: A const bson_t that should not be modified or freed.
 */
const bson_t *
bson_reader_read (bson_reader_t *reader);


BSON_END_DECLS


#endif /* BSON_READER_H */
