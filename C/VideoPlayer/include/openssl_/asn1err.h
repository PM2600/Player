/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2021 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_ASN1ERR_H
# define OPENSSL_ASN1ERR_H
# pragma once

# include <openssl/opensslconf.h>
# include <openssl/symhacks.h>
# include <openssl/cryptoerr_legacy.h>



/*
 * ASN1 reason codes.
 */
# define ASN1_R_ADDING_OBJECT                             171
# define ASN1_R_ASN1_PARSE_ERROR                          203
# define ASN1_R_ASN1_SIG_PARSE_ERROR                      204
# define ASN1_R_AUX_ERROR                                 100
# define ASN1_R_BAD_OBJECT_HEADER                         102
# define ASN1_R_BAD_TEMPLATE                              230
# define ASN1_R_BMPSTRING_IS_WRONG_LENGTH                 214
# define ASN1_R_BN_LIB                                    105
# define ASN1_R_BOOLEAN_IS_WRONG_LENGTH                   106
# define ASN1_R_BUFFER_TOO_SMALL                          107
# define ASN1_R_CIPHER_HAS_NO_OBJECT_IDENTIFIER           108
# define ASN1_R_CONTEXT_NOT_INITIALISED                   217
# define ASN1_R_DATA_IS_WRONG                             109
# define ASN1_R_DECODE_ERROR                              110
# define ASN1_R_DEPTH_EXCEEDED                            174
# define ASN1_R_DIGEST_AND_KEY_TYPE_NOT_SUPPORTED         198
# define ASN1_R_ENCODE_ERROR                              112
# define ASN1_R_ERROR_GETTING_TIME                        173
# define ASN1_R_ERROR_LOADING_SECTION                     172
# define ASN1_R_ERROR_SETTING_CIPHER_PARAMS               114
# define ASN1_R_EXPECTING_AN_INTEGER                      115
# define ASN1_R_EXPECTING_AN_OBJECT                       116
# define ASN1_R_EXPLICIT_LENGTH_MISMATCH                  119
# define ASN1_R_EXPLICIT_TAG_NOT_CONSTRUCTED              120
# define ASN1_R_FIELD_MISSING                             121
# define ASN1_R_FIRST_NUM_TOO_LARGE                       122
# define ASN1_R_HEADER_TOO_LONG                           123
# define ASN1_R_ILLEGAL_BITSTRING_FORMAT                  175
# define ASN1_R_ILLEGAL_BOOLEAN                           176
# define ASN1_R_ILLEGAL_CHARACTERS                        124
# define ASN1_R_ILLEGAL_FORMAT                            177
# define ASN1_R_ILLEGAL_HEX                               178
# define ASN1_R_ILLEGAL_IMPLICIT_TAG                      179
# define ASN1_R_ILLEGAL_INTEGER                           180
# define ASN1_R_ILLEGAL_NEGATIVE_VALUE                    226
# define ASN1_R_ILLEGAL_NESTED_TAGGING                    181
# define ASN1_R_ILLEGAL_NULL                              125
# define ASN1_R_ILLEGAL_NULL_VALUE                        182
# define ASN1_R_ILLEGAL_OBJECT                            183
# define ASN1_R_ILLEGAL_OPTIONAL_ANY                      126
# define ASN1_R_ILLEGAL_OPTIONS_ON_ITEM_TEMPLATE          170
# define ASN1_R_ILLEGAL_PADDING                           221
# define ASN1_R_ILLEGAL_TAGGED_ANY                        127
# define ASN1_R_ILLEGAL_TIME_VALUE                        184
# define ASN1_R_ILLEGAL_ZERO_CONTENT                      222
# define ASN1_R_INTEGER_NOT_ASCII_FORMAT                  185
# define ASN1_R_INTEGER_TOO_LARGE_FOR_LONG                128
# define ASN1_R_INVALID_BIT_STRING_BITS_LEFT              220
# define ASN1_R_INVALID_BMPSTRING_LENGTH                  129
# define ASN1_R_INVALID_DIGIT                             130
# define ASN1_R_INVALID_MIME_TYPE                         205
# define ASN1_R_INVALID_MODIFIER                          186
# define ASN1_R_INVALID_NUMBER                            187
# define ASN1_R_INVALID_OBJECT_ENCODING                   216
# define ASN1_R_INVALID_SCRYPT_PARAMETERS                 227
# define ASN1_R_INVALID_SEPARATOR                         131
# define ASN1_R_INVALID_STRING_TABLE_VALUE                218
# define ASN1_R_INVALID_UNIVERSALSTRING_LENGTH            133
# define ASN1_R_INVALID_UTF8STRING                        134
# define ASN1_R_INVALID_VALUE                             219
# define ASN1_R_LIST_ERROR                                188
# define ASN1_R_MIME_NO_CONTENT_TYPE                      206
# define ASN1_R_MIME_PARSE_ERROR                          207
# define ASN1_R_MIME_SIG_PARSE_ERROR                      208
# define ASN1_R_MISSING_EOC                               137
# define ASN1_R_MISSING_SECOND_NUMBER                     138
# define ASN1_R_MISSING_VALUE                             189
# define ASN1_R_MSTRING_NOT_UNIVERSAL                     139
# define ASN1_R_MSTRING_WRONG_TAG                         140
# define ASN1_R_NESTED_ASN1_STRING                        197
# define ASN1_R_NESTED_TOO_DEEP                           201
# define ASN1_R_NON_HEX_CHARACTERS                        141
# define ASN1_R_NOT_ASCII_FORMAT                          190
# define ASN1_R_NOT_ENOUGH_DATA                           142
# define ASN1_R_NO_CONTENT_TYPE                           209
# define ASN1_R_NO_MATCHING_CHOICE_TYPE                   143
# define ASN1_R_NO_MULTIPART_BODY_FAILURE                 210
# define ASN1_R_NO_MULTIPART_BOUNDARY                     211
# define ASN1_R_NO_SIG_CONTENT_TYPE                       212
# define ASN1_R_NULL_IS_WRONG_LENGTH                      144
# define ASN1_R_OBJECT_NOT_ASCII_FORMAT                   191
# define ASN1_R_ODD_NUMBER_OF_CHARS                       145
# define ASN1_R_SECOND_NUMBER_TOO_LARGE                   147
# define ASN1_R_SEQUENCE_LENGTH_MISMATCH                  148
# define ASN1_R_SEQUENCE_NOT_CONSTRUCTED                  149
# define ASN1_R_SEQUENCE_OR_SET_NEEDS_CONFIG              192
# define ASN1_R_SHORT_LINE                                150
# define ASN1_R_SIG_INVALID_MIME_TYPE                     213
# define ASN1_R_STREAMING_NOT_SUPPORTED                   202
# define ASN1_R_STRING_TOO_LONG                           151
# define ASN1_R_STRING_TOO_SHORT                          152
# define ASN1_R_THE_ASN1_OBJECT_IDENTIFIER_IS_NOT_KNOWN_FOR_THIS_MD 154
# define ASN1_R_TIME_NOT_ASCII_FORMAT                     193
# define ASN1_R_TOO_LARGE                                 223
# define ASN1_R_TOO_LONG                                  155
# define ASN1_R_TOO_SMALL                                 224
# define ASN1_R_TYPE_NOT_CONSTRUCTED                      156
# define ASN1_R_TYPE_NOT_PRIMITIVE                        195
# define ASN1_R_UNEXPECTED_EOC                            159
# define ASN1_R_UNIVERSALSTRING_IS_WRONG_LENGTH           215
# define ASN1_R_UNKNOWN_DIGEST                            229
# define ASN1_R_UNKNOWN_FORMAT                            160
# define ASN1_R_UNKNOWN_MESSAGE_DIGEST_ALGORITHM          161
# define ASN1_R_UNKNOWN_OBJECT_TYPE                       162
# define ASN1_R_UNKNOWN_PUBLIC_KEY_TYPE                   163
# define ASN1_R_UNKNOWN_SIGNATURE_ALGORITHM               199
# define ASN1_R_UNKNOWN_TAG                               194
# define ASN1_R_UNSUPPORTED_ANY_DEFINED_BY_TYPE           164
# define ASN1_R_UNSUPPORTED_CIPHER                        228
# define ASN1_R_UNSUPPORTED_PUBLIC_KEY_TYPE               167
# define ASN1_R_UNSUPPORTED_TYPE                          196
# define ASN1_R_WRONG_INTEGER_TYPE                        225
# define ASN1_R_WRONG_PUBLIC_KEY_TYPE                     200
# define ASN1_R_WRONG_TAG                                 168

#endif
