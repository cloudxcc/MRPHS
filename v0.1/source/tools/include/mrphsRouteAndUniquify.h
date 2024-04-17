//
// Copyright 2023 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

//////////////////////////////////////////////////////////////////////////////////////
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
