/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2021 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_PEMERR_H
# define OPENSSL_PEMERR_H
# pragma once

# include <openssl/opensslconf.h>
# include <openssl/symhacks.h>
# include <openssl/cryptoerr_legacy.h>



/*
 * PEM reason codes.
 */
# define PEM_R_BAD_BASE64_DECODE                          100
# define PEM_R_BAD_DECRYPT                                101
# define PEM_R_BAD_END_LINE                               102
# define PEM_R_BAD_IV_CHARS                               103
# define PEM_R_BAD_MAGIC_NUMBER                           116
# define PEM_R_BAD_PASSWORD_READ                          104
# define PEM_R_BAD_VERSION_NUMBER                         117
# define PEM_R_BIO_WRITE_FAILURE                          118
# define PEM_R_CIPHER_IS_NULL                             127
# define PEM_R_ERROR_CONVERTING_PRIVATE_KEY               115
# define PEM_R_EXPECTING_PRIVATE_KEY_BLOB                 119
# define PEM_R_EXPECTING_PUBLIC_KEY_BLOB                  120
# define PEM_R_HEADER_TOO_LONG                            128
# define PEM_R_INCONSISTENT_HEADER                        121
# define PEM_R_KEYBLOB_HEADER_PARSE_ERROR                 122
# define PEM_R_KEYBLOB_TOO_SHORT                          123
# define PEM_R_MISSING_DEK_IV                             129
# define PEM_R_NOT_DEK_INFO                               105
# define PEM_R_NOT_ENCRYPTED                              106
# define PEM_R_NOT_PROC_TYPE                              107
# define PEM_R_NO_START_LINE                              108
# define PEM_R_PROBLEMS_GETTING_PASSWORD                  109
# define PEM_R_PVK_DATA_TOO_SHORT                         124
# define PEM_R_PVK_TOO_SHORT                              125
# define PEM_R_READ_KEY                                   111
# define PEM_R_SHORT_HEADER                               112
# define PEM_R_UNEXPECTED_DEK_IV                          130
# define PEM_R_UNSUPPORTED_CIPHER                         113
# define PEM_R_UNSUPPORTED_ENCRYPTION                     114
# define PEM_R_UNSUPPORTED_KEY_COMPONENTS                 126
# define PEM_R_UNSUPPORTED_PUBLIC_KEY_TYPE                110

#endif
