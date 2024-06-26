//
// Copyright 2023 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

//////////////////////////////////////////////////////////////////////////////////////
///	mrphsElaborateArguments
/////////////////////////////////////////////////////////////////////////////////
void mrphsElaborateArguments (int argc, char **argv, unsigned tool, NODE* sourceNode, string* outputDir, string* topLevelName);
/////////////////////////////////////////////////////////////////////////////////
///  Check if NODE exists on this level with the given id.
///  If it exists, return the NODE.
///  If it does not exist, a new one is inserted and returned.
/////////////////////////////////////////////////////////////////////////////////
NODE* getConstructListNode (NODE* node, 
                            unsigned dbID);
/////////////////////////////////////////////////////////////////////////////////
/// Searches for a module with the given name.
/////////////////////////////////////////////////////////////////////////////////
NODE* getModule (string &moduleName);
/////////////////////////////////////////////////////////////////////////////////
/// Returns sub-modules
/////////////////////////////////////////////////////////////////////////////////
NODE* getSubModule (NODE* targetModuleHierNode, 
                    NODE* modNode);
/////////////////////////////////////////////////////////////////////////////////
/// Copy tree of joined clusters
/////////////////////////////////////////////////////////////////////////////////
NODE* copyJoinedClusterTree (NODE* node, 
                             NODE* copiedJoinedClusterHashNode, 
                             unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Copy complete tree of a sub-module
/////////////////////////////////////////////////////////////////////////////////
NODE* copySubModuleTree (	NODE* node, 
                            bool trueModuleFalseInstance, 
              				NODE* rootModuleNameNode, 
              				NODE* ptrModuleNameNode, 
              				NODE* copiedJoinedClusterHashNode, 
              				unsigned *clCntPtr, 
              				unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Copy tree of a module
/////////////////////////////////////////////////////////////////////////////////
NODE* copyModuleTree (NODE* node, 
                      NODE* copiedJoinedClusterHashNode, 
                      unsigned *clCntPtr, 
                      unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Get all PDVL_EMIT entries in tree.
/////////////////////////////////////////////////////////////////////////////////
NODE* getLHSTree (NODE* node, 
                  NODE* lhsTree);
/////////////////////////////////////////////////////////////////////////////////
/// Return logic cone of a given RHS assignment name.
/////////////////////////////////////////////////////////////////////////////////
NODE* extractTreeLHS (string name, 
                      NODE* datapathRegTree, 
                      NODE* node);
/////////////////////////////////////////////////////////////////////////////////
/// Returns the first LIST_ENTRY NODE below the NODE with the given id.
/// If NODE with id does not exist on this level, then it is inserted.
/////////////////////////////////////////////////////////////////////////////////
NODE* getConstructListFirstNode (NODE* referenceModuleNode, 
                                 unsigned dbID);
/////////////////////////////////////////////////////////////////////////////////
/// Inserts LIST_ENTRY NODE below NODE with given id.
/// If NODE with given id does not exist on the this level, 
/// then an additional NODE is inserted as well.
/// Retruns the inserterd LIST_ENTRY NODE.
/////////////////////////////////////////////////////////////////////////////////
NODE* insertConstructListNode (NODE* referenceModuleNode, 
                               unsigned dbID);
/////////////////////////////////////////////////////////////////////////////////
/// Return all RHS entries from a given conde.
/////////////////////////////////////////////////////////////////////////////////
NODE* getRHSTree (bool postAssignment, 
                  NODE* node, 
                  NODE* rhsTree);
/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void prettyPrintCPP (string &out);
/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void prettyPrintGA (string &out);
/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void prettyPrint (string &out);
/////////////////////////////////////////////////////////////////////////////////
///	Read a PDVL file
/////////////////////////////////////////////////////////////////////////////////
void readPDVL (string &out, bool pdvl);
/////////////////////////////////////////////////////////////////////////////////
/// printError
/////////////////////////////////////////////////////////////////////////////////
void printError ();
/////////////////////////////////////////////////////////////////////////////////
/// Report unfinished command
/////////////////////////////////////////////////////////////////////////////////
bool reportUnfinishedCommands (NODE* node);
