/*
 * Copyright 2005-2006 Sun Microsystems, Inc.  All Rights Reserved.
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
 */

//

import java.io.*;
import java.util.*;


public class Basic {

    private static PrintStream out = System.err;

    private static <T> Set<T> setOf(Iterable<T> it) {
        Set<T> s = new HashSet<T>();
        for (T t : it)
            s.add(t);
        return s;
    }

    private static <T> void checkEquals(Set<T> s1, Set<T> s2, boolean eq) {
        if (s1.equals(s2) != eq)
            throw new RuntimeException(String.format("%b %s : %s",
                                                     eq, s1, s2));
    }

    public static void main(String[] args) {

        ServiceLoader<FooService> sl = ServiceLoader.load(FooService.class);
        out.format("%s%n", sl);

        // Providers are cached
        Set<FooService> ps = setOf(sl);
        checkEquals(ps, setOf(sl), true);

        // The cache can be flushed and reloaded
        sl.reload();
        checkEquals(ps, setOf(sl), false);

    }

}
