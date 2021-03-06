/*
 * Copyright 1997-2002 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 *  
 */
// This file is a derivative work resulting from (and including) modifications
// made by Azul Systems, Inc.  The date of such changes is 2010.
// Copyright 2010 Azul Systems, Inc.  All Rights Reserved.
//
// Please contact Azul Systems, Inc., 1600 Plymouth Street, Mountain View, 
// CA 94043 USA, or visit www.azulsystems.com if you need additional information 
// or have any questions.
#ifndef FIELDTYPE_HPP
#define FIELDTYPE_HPP

#include "symbolOop.hpp"

// Note: FieldType should be based on the SignatureIterator (or vice versa).
//       In any case, this structure should be re-thought at some point.

// A FieldType is used to determine the type of a field from a signature string.

class FieldType: public AllStatic {
 private:  
  static void skip_optional_size(symbolOop signature, int* index);
  static bool is_valid_array_signature(symbolOop signature);
 public:
 
  // Return basic type
  static BasicType basic_type(symbolOop signature);  

  // Testing
  static bool is_array(symbolOop signature) { return signature->utf8_length() > 1 && signature->byte_at(0) == '[' && is_valid_array_signature(signature); }

  static bool is_obj(symbolOop signature) {
     int sig_length = signature->utf8_length();
     // Must start with 'L' and end with ';'
     return (sig_length >= 2 &&
             (signature->byte_at(0) == 'L') &&
             (signature->byte_at(sig_length - 1) == ';'));
  }

  // Parse field and extract array information. Works for T_ARRAY only.  
  static BasicType get_array_info(symbolOop signature, jint* dimension, symbolOop *object_key, TRAPS);
};

#endif // FIELDTYPE_HPP
