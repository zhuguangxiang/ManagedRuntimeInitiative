/*
 * Copyright 1997-2005 Sun Microsystems, Inc.  All Rights Reserved.
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
#ifndef MULTNODE_HPP
#define MULTNODE_HPP


#include "node.hpp"
class Matcher;
class ProjNode;

//------------------------------MultiNode--------------------------------------
// This class defines a MultiNode, a Node which produces many values.  The
// values are wrapped up in a tuple Type, i.e. a TypeTuple.
class MultiNode : public Node {
public:
  MultiNode( uint required ) : Node(required) {
    init_class_id(Class_Multi);
  }
virtual int Opcode()const=0;
  virtual const Type *bottom_type() const = 0;
  virtual bool       is_CFG() const { return true; }
  virtual uint hash() const { return NO_HASH; }  // CFG nodes do not hash
  virtual const RegMask &out_RegMask() const;
  virtual Node *match( const ProjNode *proj, const Matcher *m );
  virtual uint ideal_reg() const { return NotAMachineReg; }
  ProjNode* proj_out(uint which_proj) const; // Get a named projection

};

//------------------------------ProjNode---------------------------------------
// This class defines a Projection node.  Projections project a single element
// out of a tuple (or Signature) type.  Only MultiNodes produce TypeTuple
// results.
class ProjNode : public Node {
protected:
  virtual uint hash() const;
  virtual uint cmp( const Node &n ) const;
  virtual uint size_of() const;
  void check_con() const;       // Called from constructor.

public:
  ProjNode( Node *src, uint con, bool io_use = false ) 
    : Node( src ), _con(con), _is_io_use(io_use) 
  {
    init_class_id(Class_Proj);
    debug_only(check_con());
  }
  const uint _con;              // The field in the tuple we are projecting
  const bool _is_io_use;        // Used to distinguish between the projections
                                // used on the control and io paths from a macro node
  virtual int Opcode() const;
  virtual bool      is_CFG() const;
  virtual const Type *bottom_type() const;
  virtual const TypePtr *adr_type() const;
  virtual bool pinned() const;
  virtual const Type *Value( PhaseTransform *phase ) const;
  virtual uint ideal_reg() const;
  virtual const RegMask &out_RegMask() const;
  virtual void dump_spec(outputStream *st) const;
};

#endif // MULTNODE_HPP
