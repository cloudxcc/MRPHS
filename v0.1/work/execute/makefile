#//
#// Copyright 2024 Tobias Strauch, Munich, Bavaria
#// Licensed under the Apache License, Version 2.0, see LICENSE for details.
#// SPDX-License-Identifier: Apache-2.0
#//

MRPHS_files = ../../source/tools/cpp/mrphsPDVL2DB.cpp \
              ../../source/tools/cpp/mrphsRouteAndUniquify.cpp \
              ../../source/tools/cpp/mrphsBasics.cpp \
              ../../source/tools/cpp/grammar_macro.cpp \
              ../../source/tools/cpp/parser.cpp \
              ../../source/tools/cpp/solve.cpp \
              ../../source/tools/cpp/nodesAndTrees.cpp \
              ../../source/tools/cpp/writer.cpp \
              ../../source/tools/include/db_macro.h \
              ../../source/tools/include/grammar_macro.h \
              ../../source/tools/include/parser.h \
              ../../source/tools/include/solve.h \
              ../../source/tools/include/writer.h

MRPHS_D_files = $(MRPHS_files) \
                ../../source/tools/cpp/MRPHS_D.cpp \
                ../../source/tools/cpp/mrphsWriteSV.cpp \
                ../../source/tools/include/MRPHS_D.h \
                ../../source/tools/include/mrphsWriteSV.h \

MRPHS_D: $(MRPHS_D_files)
	g++ -I../../source/tools/include -I../../source/tools/cpp ../../source/tools/cpp/MRPHS_D.cpp -o MRPHS_D ;\
	cp MRPHS_D.exe ../../bin ;\


