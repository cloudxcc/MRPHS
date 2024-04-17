//
// Copyright 2024 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

/////////////////////////////////////////////////////////////////////////////////
///	Basic include
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
      
/////////////////////////////////////////////////////////////////////////////////
///	The one and only class
/////////////////////////////////////////////////////////////////////////////////
class NODE
{
public:      
    unsigned id;
    NODE* sub;
    NODE* next;
};

/////////////////////////////////////////////////////////////////////////////////
///	Global variables
/////////////////////////////////////////////////////////////////////////////////

unsigned maxPtr;
unsigned reportLevel;
FILE *app;
NODE* dbNode;
NODE* dbClusterNode;
NODE* dbModuleNode;
NODE* dbSignalNode;
NODE* dbPackageNode;

/////////////////////////////////////////////////////////////////////////////////
///	Tool specific includes
/////////////////////////////////////////////////////////////////////////////////

using namespace std;
#include <grammar_macro.h>
#include <grammar_macro.cpp>
#include <db_macro.h>
#include <parser.cpp>
#include <writer.cpp>
#include <nodesAndTrees.cpp>
#include <mrphsBasics.cpp>
#include <solve.cpp>
#include <mrphsPDVL2DB.cpp>
#include <mrphsRouteAndUniquify.cpp>
#include <mrphsWriteSV.cpp>
#include <MRPHS_D.h>

/////////////////////////////////////////////////////////////////////////////////
///	MRPHS_D main
/////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
   NODE* sourceNode = initNode(0);
   string outputDir = "";
   string topLevelName = "";
   mrphsElaborateArguments(argc, argv, 0, sourceNode, &outputDir, &topLevelName);
     
   /////////////////////////////////
   // convert PDVL to SV
   /////////////////////////////////
   if (reportLevel > 0)
      printf("2 Converting source files into database.\n");
   NODE* topModuleNode = convertPDVL2DB(sourceNode, topLevelName, outputDir);   
      
   /////////////////////////////////
   // Route SV Modules 
   /////////////////////////////////
   if (reportLevel > 0)
      printf("3 Routing signals.\n");
   routeSignalsInModuleHierarchy(topModuleNode); 

   /////////////////////////////////
   // Write 
   /////////////////////////////////
   if (reportLevel > 0)
      printf("4 Writing SystemVerilog output.\n");
   writeSystemVerilog(topModuleNode, outputDir);
   
   if (reportLevel > 0)
      fprintf(stdout, "MRPHS finished.\n");

   return 0;
}
