//
// Copyright 2023 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

//////////////////////////////////////////////////////////////////////////////////////
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
/// Return sub-modules
/////////////////////////////////////////////////////////////////////////////////
NODE* getSubModule (NODE* targetModuleHierNode, 
                    NODE* modNode);
/////////////////////////////////////////////////////////////////////////////////
/// Add wire to module entry
/////////////////////////////////////////////////////////////////////////////////
void addWire (string &signalName, 
              NODE* typeNode, 
              NODE* topModuleNode);
/////////////////////////////////////////////////////////////////////////////////
/// Add port, simple, level 2
/////////////////////////////////////////////////////////////////////////////////
void addPortSimpleLevel2 (string pathSignalName, 
                          string signalName, 
                          bool trueLHSfalseRHS, 
                          NODE* typeNode, 
                          NODE* modNode, 
                          unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Add port, simple, level 1, (pass hierarchy tree, skip level1 = instance name)
/////////////////////////////////////////////////////////////////////////////////
bool addPortSimpleLevel1 (string header,
                          string instantiationNameString, 
                          NODE* node, 
                          bool trueModuleFalseInstance,
                          NODE* hierPathNode, 
                          bool trueLHSfalseRHS, 
                          string signalName, 
                          NODE* typeNode, 
                          unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Add port, simple, used in user defined route
/////////////////////////////////////////////////////////////////////////////////
void addPortSimple (NODE* hierPathNode, 
                    bool trueLHSfalseRHS, 
                    string signalName, 
                    NODE* typeNode, 
                    NODE* modNode, 
                    unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Add Port to module entry
/////////////////////////////////////////////////////////////////////////////////
void addPort (NODE* node, 
              NODE* dbSubModuleNode, 
              string &signalName, 
              bool trueModuleFalseInstance, 
              bool trueLHSfalseRHS, 
              NODE* typeNode, 
              NODE* rootToTopNode, 
              NODE* rootToTopLeafNode);
/////////////////////////////////////////////////////////////////////////////////
/// Get module name and update type
/////////////////////////////////////////////////////////////////////////////////
void getModuleNameAndUpdateType (NODE* node, 
                                 NODE* dbSubModuleNode, 
                                 bool isTop, 
                                 bool trueModuleFalseInstance, 
                                 string &classString, 
                                 string signalName, 
                                 NODE* typeLHSNode);
/////////////////////////////////////////////////////////////////////////////////
/// Find signal and top-level route, step 2
/////////////////////////////////////////////////////////////////////////////////
void findSignalTopRouteStep2 (string &signalName,
                              NODE* rhsNode,
                              NODE* lhsNode,
                              bool isTop,
                              bool isTri,
                              NODE* hierarchyListRootNode,
                              NODE* hierarchyListNode,
                              NODE* topModuleNode, 
                              NODE* dbSubModuleNode);
/////////////////////////////////////////////////////////////////////////////////
/// Find signal and top-level route, step 1
/////////////////////////////////////////////////////////////////////////////////
void findSignalTopRouteStep1 (unsigned level, 
                              string &header, 
                              NODE* node,
                              string &signalName,
                              NODE* typeNode, 
                              NODE* lhsNode,
                              NODE* hierarchyListRootNode,
                              NODE* hierarchyListNode,
                              NODE* topModuleNode, 
                              NODE* dbSubModuleNode);
/////////////////////////////////////////////////////////////////////////////////
/// Place new parameter type, step 2
/////////////////////////////////////////////////////////////////////////////////
bool placeNewParameterTypeStep2 (NODE* hierPathNode,
                                 bool trueTypeFalseParameter,
                                 bool trueModuleFalseInstance,
                                 bool isTop, 
                                 NODE* hierDesignNode, 
                                 NODE* assignmentNode);
/////////////////////////////////////////////////////////////////////////////////
/// Place new parameter type, step 1
/////////////////////////////////////////////////////////////////////////////////
void placeNewParameterTypeStep1 (unsigned level, 
                                 string &header,
                                 bool trueTypeFalseParameter, 
                                 NODE* node,
                                 NODE* topModuleNode,
                                 NODE* dbParameterNode,
                                 NODE* dbFunctionNode);
////////////////////////////////////////////////////////////////////////////////
/// Route all signals in module hierarchy
/////////////////////////////////////////////////////////////////////////////////
void routeSignalsInModuleHierarchy (NODE* topModuleNode);
/////////////////////////////////////////////////////////////////////////////////
/// Write SystemVerilog sub-module
/////////////////////////////////////////////////////////////////////////////////
string writeSubModule (string &header, 
                       NODE* dbSubModuleNode, 
                       bool trueModuleFalseInstance);
/////////////////////////////////////////////////////////////////////////////////
/// Clean SystemVerilog "always" logic cone
///////////////////////////////////////////////////////////////////////////////// 
NODE* cleanSVConeAlways (NODE* tmpNode);
/////////////////////////////////////////////////////////////////////////////////
/// Clean SystemVerilog "unique" logic cone
///////////////////////////////////////////////////////////////////////////////// 
void cleanSVConeUnique (NODE* node);
/////////////////////////////////////////////////////////////////////////////////
/// Clean SystemVerilog loop index
///////////////////////////////////////////////////////////////////////////////// 
string cleanSVConeLoopIndex (NODE* tmpNode, 
                             NODE* signalTree);
/////////////////////////////////////////////////////////////////////////////////
/// Add SystemVerilog loop entry
///////////////////////////////////////////////////////////////////////////////// 
string addLoop (string signalName, 
                string loopVar);
/////////////////////////////////////////////////////////////////////////////////
/// Insert X assignment in lowest dimension
///////////////////////////////////////////////////////////////////////////////// 
string insertXAssignmentDim (string signalName,
                             NODE* dim0TypeNode,
                             unsigned loopDim,
                             NODE* nextTypeNode,
                             NODE* dbModuleTypesNode);
/////////////////////////////////////////////////////////////////////////////////
/// Insert X assignment
///////////////////////////////////////////////////////////////////////////////// 
string insertXAssignment (string signalName,
                          NODE* typeNode,
                          NODE* dbModuleTypesNode);
/////////////////////////////////////////////////////////////////////////////////
/// Clean SystemVerilog logic cone
///////////////////////////////////////////////////////////////////////////////// 
string cleanSVCone (NODE* coneNode, 
                    bool trueBlockingFalseNonBlocking, 
                    bool insertX,
                    string signalName,
                    NODE* typeNode,
                    NODE* dbModuleTypesNode,
                    NODE* signalTree);
/////////////////////////////////////////////////////////////////////////////////
/// Write SystemVerilog declaration
/////////////////////////////////////////////////////////////////////////////////
void writeDeclaration (string &out, 
                       unsigned identifier, 
                       string signalName, 
                       NODE* typeNode);
/////////////////////////////////////////////////////////////////////////////////
/// Check type dependency, 
/// gets individual SV_DATA_TYPE node, 
/// returns false if sub-type not printed yet.
///////////////////////////////////////////////////////////////////////////////// 
bool checkTypeDependency (NODE* dataTypeNode, 
                          NODE* doneSiNode);
/////////////////////////////////////////////////////////////////////////////////
/// Write SystemVerilog module
///////////////////////////////////////////////////////////////////////////////// 
string writeSystemVerilogModule (NODE* modNode);
/////////////////////////////////////////////////////////////////////////////////
/// Mark printed module
/////////////////////////////////////////////////////////////////////////////////
void markModulePrint (NODE* node, 
                      bool trueModuleFalseInstance);
/////////////////////////////////////////////////////////////////////////////////
/// Check if sub-module already printed
/////////////////////////////////////////////////////////////////////////////////
bool checkSubModulePrint (NODE* node, 
                          bool trueModuleFalseInstance);
/////////////////////////////////////////////////////////////////////////////////
/// Uniquify module to be written
/////////////////////////////////////////////////////////////////////////////////
bool uniquifyWriteModule (NODE* node, 
                          string &header, 
                          string &outputDir);
/////////////////////////////////////////////////////////////////////////////////
/// write SystemVerilog package
/////////////////////////////////////////////////////////////////////////////////
void writePackage (NODE* node, 
                   string &header, 
                   string &out);
/////////////////////////////////////////////////////////////////////////////////
/// write SystemVerilog code
/////////////////////////////////////////////////////////////////////////////////
void writeSystemVerilog (NODE* topModuleNode, 
                         string &outputDir);
