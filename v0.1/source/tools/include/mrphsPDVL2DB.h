//
// Copyright 2023 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

//////////////////////////////////////////////////////////////////////////////////////
/// Key function of the PDVL to SV converter tool
/////////////////////////////////////////////////////////////////////////////////
NODE* convertPDVL2DB (NODE* sourceNode, 
                      string &topLevelName, 
                      string &outputDir);
/////////////////////////////////////////////////////////////////////////////////
/// Save all individual clusters into database
/////////////////////////////////////////////////////////////////////////////////
void saveCluster (NODE* sourceNode, 
                  unsigned *clCntPtr, 
                  unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate given cluster, phase 1
/////////////////////////////////////////////////////////////////////////////////
bool clusterElaborationPhase1 (unsigned loop, 
                               NODE* node, 
                               NODE* newModulesNode, 
                               unsigned *clCntPtr, 
                               unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate given cluster, phase 2
/////////////////////////////////////////////////////////////////////////////////
bool clusterElaborationPhase2 (unsigned loop, 
                               NODE* node, 
                               NODE* targetTree, 
                               NODE* newClustersNode, 
                               unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate given cluster, phase 3
/////////////////////////////////////////////////////////////////////////////////
bool clusterElaborationPhase3 (unsigned loop, 
                               NODE* node, 
                               NODE* targetTree, 
                               NODE* newModulesNode, 
                               NODE* newClustersNode, 
                               unsigned *clCntPtr, 
                               unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Execute "place" command
/////////////////////////////////////////////////////////////////////////////////
bool executePlaceCommand (NODE* commandBodyNode, 
                          NODE* modNode, 
                          NODE* nonEmptyBuilds, 
                          NODE* newModulesNode, 
                          NODE* newClustersNode, 
                          unsigned *clCntPtr, 
                          unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Structural composition, phase 1
/////////////////////////////////////////////////////////////////////////////////
void structuralCompositionPhase1 (unsigned loop, 
                                  NODE* node, 
                                  NODE* targetTree, 
                                  NODE* nonEmptyBuilds);
/////////////////////////////////////////////////////////////////////////////////
/// Structural composition, phase 2
/////////////////////////////////////////////////////////////////////////////////
bool structuralCompositionPhase2 (unsigned loop, 
                                  NODE* node, 
                                  NODE* targetTree, 
                                  NODE* nonEmptyBuilds, 
                                  NODE* newModulesNode, 
                                  NODE* newClustersNode, 
                                  unsigned *clCntPtr, 
                                  unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Structural composition, phase3
/////////////////////////////////////////////////////////////////////////////////
bool structuralCompositionPhase3 (unsigned loop, 
                                  NODE* node, 
                                  NODE* targetTree, 
                                  NODE* nonEmptyBuilds, 
                                  NODE* newModulesNode, 
                                  NODE* newClustersNode, 
                                  unsigned *clCntPtr, 
                                  unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Elaboration of a given cluster
/////////////////////////////////////////////////////////////////////////////////
void clusterElaboration (unsigned loop, 
                         unsigned *clCntPtr, 
                         unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Structural composition
/////////////////////////////////////////////////////////////////////////////////
void structuralComposition (unsigned loop, 
                            unsigned *clCntPtr, 
                            unsigned *moCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Convert PDVL condition to Verilog process 
/////////////////////////////////////////////////////////////////////////////////
NODE* convertCond2Process (NODE* node, 
                           bool defaultFound, 
                           bool highActive, 
                           string &condName);
/////////////////////////////////////////////////////////////////////////////////
/// Add attribute tree
/////////////////////////////////////////////////////////////////////////////////
void addAttTree (NODE* attributeNode, 
                 bool driverTrue, 
                 string signalName, 
                 NODE* sourceNode, 
                 NODE* ilrAttributeTree);
/////////////////////////////////////////////////////////////////////////////////
/// Connect by attribute
/////////////////////////////////////////////////////////////////////////////////
void connectByAttribute (NODE* node, 
                         string &header);
/////////////////////////////////////////////////////////////////////////////////
/// post-process logic joining
/////////////////////////////////////////////////////////////////////////////////
void logicJoiningPostProcess (NODE* modNode, 
                              NODE* transactionTree, 
                              NODE* eventTree, 
                              NODE* condTree, 
                              NODE* datapathTree, 
                              NODE* hierRootNode);
/////////////////////////////////////////////////////////////////////////////////
/// Extract inline macros
/////////////////////////////////////////////////////////////////////////////////
void extractInlineMacro (NODE* node, 
                         string nameString, 
                         NODE* insertNode);
/////////////////////////////////////////////////////////////////////////////////
/// Join logic, phase 2
/////////////////////////////////////////////////////////////////////////////////
void logicJoiningLevel2 (NODE* node, 
                         bool trackHier, 
                         string &header, 
                         NODE* modNode, 
                         NODE* transactionTree, 
                         NODE* removeTransactionTree, 
                         NODE* datapathTree);
/////////////////////////////////////////////////////////////////////////////////
/// Extract PDVL event and PDVL condition, step 2
/////////////////////////////////////////////////////////////////////////////////
void extractEventAndCondTreeStep2 (NODE* node, 
                                   string &header, 
                                   NODE* hierRootNode, 
                                   NODE* eventTree, 
                                   NODE* condTree);
/////////////////////////////////////////////////////////////////////////////////
/// Extract PDVL event and PDVL condition, step 1
/////////////////////////////////////////////////////////////////////////////////
void extractEventAndCondTreeStep1 (NODE* node, 
                                   bool isTop, 
                                   bool trueModuleFalseInstance, 
                                   NODE* eventTree, 
                                   NODE* condTree, 
                                   NODE* hierRootNode, 
                                   NODE* hierLeafNode);
/////////////////////////////////////////////////////////////////////////////////
/// Extract PDVL event and PDVL condition
/////////////////////////////////////////////////////////////////////////////////
void extractEventAndCondTree (NODE* topModuleNode, 
                              NODE* eventTree, 
                              NODE* condTree);
/////////////////////////////////////////////////////////////////////////////////
/// Logic joining
/////////////////////////////////////////////////////////////////////////////////
void logicJoining (NODE* node, bool isTop, bool trueModuleFalseInstance, NODE* eventTree, NODE* condTree,
                   NODE* hierRootNode, NODE* hierLeafNode);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL move and route command
/////////////////////////////////////////////////////////////////////////////////
void moveRouteCommand (NODE* node, 
                       bool isTop, 
                       unsigned command, 
                       bool trueModuleFalseInstance, 
                       unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Add entries to parameter RHS tree
/////////////////////////////////////////////////////////////////////////////////
bool addToParameterRHSNode (NODE* node,
                            NODE* givenSIRootNode,
                            NODE* givenSILeafNode,
                            NODE* rootToTopNode,
                            NODE* dbParameterNode);
/////////////////////////////////////////////////////////////////////////////////
/// Add entries to parameter RHS tree, subroutine 2
/////////////////////////////////////////////////////////////////////////////////
void addToParameterRHSNode2 (NODE* node,
                             NODE* givenSIRootNode,
                             NODE* givenSILeafNode,
                             NODE* rootToTopNode,
                             NODE* dbParameterNode);
/////////////////////////////////////////////////////////////////////////////////
/// Get global signal tree, step 4, "add RHS"
/////////////////////////////////////////////////////////////////////////////////
void getGlobalSignalTreeStep4 (bool trueLHSfalseRHS, 
                               NODE* node, 
                               unsigned clId,
                               NODE* typeNode, 
                               NODE* parameterAssignmentNode, 
                               NODE* dbSignalRelNode, 
                               NODE* hierRootNode);
/////////////////////////////////////////////////////////////////////////////////
/// Get global signal tree, step 2, "pass instantiation name"
/////////////////////////////////////////////////////////////////////////////////
void getGlobalSignalTreeStep2 (NODE* node, NODE* rootNode, 
                               bool trueType, 
                               bool trueFullFalseParameterLHS, 
                               NODE* dbParameterNode, 
                               NODE* dbTypeNode, 
                               NODE* dbFunctionNode,
                               NODE* leafNode);
/////////////////////////////////////////////////////////////////////////////////
/// Add type entries to dbTypeNode
/////////////////////////////////////////////////////////////////////////////////
void addTypeToDBType (NODE* node, 
                      NODE* dbTypeNode, 
                      NODE* rootNode);
/////////////////////////////////////////////////////////////////////////////////
/// Add RHS entries to collectors
/////////////////////////////////////////////////////////////////////////////////
void addRHSToCollectors (NODE* subNode, 
                         NODE* rootNode, 
                         //bool trueFullFalseParameterLHS, 
                         NODE* dbFunctionNode, 
                         NODE* dbParameterNode);
/////////////////////////////////////////////////////////////////////////////////
/// Get global signal tree, step 1
/////////////////////////////////////////////////////////////////////////////////
void getGlobalSignalTreeStep1 (NODE* node, 
                               NODE* rootNode,
                               bool trueType, 
                               bool trueFullFalseParameterLHS, 
                               NODE* dbParameterNode, 
                               NODE* dbTypeNode,
                               NODE* dbFunctionNode, 
                               NODE* leafNode);
/////////////////////////////////////////////////////////////////////////////////
/// Get global signal tree, step 3, "pass module name"
/////////////////////////////////////////////////////////////////////////////////
void getGlobalSignalTreeStep3 (NODE* node, NODE* rootNode, 
                               bool trueType, 
                               bool trueFullFalseParameterLHS, 
                               NODE* dbParameterNode, 
                               NODE* dbTypeNode, 
                               NODE* dbFunctionNode,
                               NODE* leafNode);
/////////////////////////////////////////////////////////////////////////////////
/// Get module, "search by name"
/////////////////////////////////////////////////////////////////////////////////
NODE* getModule (NODE* node, 
                 string &header, 
                 string &topLevelName);
/////////////////////////////////////////////////////////////////////////////////
/// Replace parameters
/////////////////////////////////////////////////////////////////////////////////
bool replaceParameters (NODE* node, 
                        NODE* parameterTree);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL "if" construct
/////////////////////////////////////////////////////////////////////////////////
bool elaboratePDVLIf (NODE* tmpNode, 
                      NODE* ifNode, 
                      NODE* parameterTree);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL "case" construct
/////////////////////////////////////////////////////////////////////////////////
bool elaboratePDVLCase (NODE* tmpNode, 
                        NODE* caseNode, 
                        NODE* parameterTree);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL "foreach" construct. 
/// Checks if foreach command can be executed. 
/// Does so when parameter defined and returns true, otherwise false.
/////////////////////////////////////////////////////////////////////////////////
bool elaboratePDVLForeach (NODE* tmpNode, 
                           NODE* foreachNode, 
                           NODE* parameterTree);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL "for" construct. 
/// Checks if foreach command can be executed. 
/// Does so when parameter defined and returns true, otherwise false.
/////////////////////////////////////////////////////////////////////////////////
bool elaboratePDVLFor (NODE* tmpNode, 
                       NODE* forNode, 
                       NODE* parameterTree);
/////////////////////////////////////////////////////////////////////////////////
/// Collect states in transaction
/////////////////////////////////////////////////////////////////////////////////
void collectTransactionState (NODE* node, 
                              NODE* fsmBag, 
                              NODE* moduleNode,
                              bool *aboveEdge, 
                              NODE* eventTree);
/////////////////////////////////////////////////////////////////////////////////
///  Convert emit statements of a FSM
/////////////////////////////////////////////////////////////////////////////////
void finiteStateEmitConversion (NODE* node, 
                                NODE* fsmBag, 
                                NODE* moduleNode,
                                bool *aboveEdge, 
                                NODE* eventTree);
/////////////////////////////////////////////////////////////////////////////////
/// Convert states of FSM to parameters
/////////////////////////////////////////////////////////////////////////////////
unsigned finiteTreeToParameter (unsigned cnt, 
                                string &header, 
                                NODE* node, 
                                NODE* moduleNode);
/////////////////////////////////////////////////////////////////////////////////
/// Extract parameters of FSM
/////////////////////////////////////////////////////////////////////////////////
unsigned stateTreeToParameter (unsigned cnt, 
                               bool oneHot, 
                               string &header, 
                               NODE* node, 
                               NODE* moduleNode);
/////////////////////////////////////////////////////////////////////////////////
/// Convert new state assignments of a FSM
/////////////////////////////////////////////////////////////////////////////////
void stateEmitToStateAssignment (NODE* node, 
                                 string &transName, 
                                 NODE* stateTree, 
                                 NODE* moduleNode);
/////////////////////////////////////////////////////////////////////////////////
/// Handle propagate statement
/////////////////////////////////////////////////////////////////////////////////
void handlePropagateStatement (NODE* node, 
                               unsigned insert);
/////////////////////////////////////////////////////////////////////////////////
/// Merge transactions
/////////////////////////////////////////////////////////////////////////////////
bool mergeTransaction (NODE* node, 
                       NODE* transactionTree, 
                       NODE* mergedTransactionsTree, 
                       NODE* moduleNode);
/////////////////////////////////////////////////////////////////////////////////
/// Merge constructs
/////////////////////////////////////////////////////////////////////////////////
void mergeConstructs (NODE* node);
/////////////////////////////////////////////////////////////////////////////////
/// Add to sensitivity list
/////////////////////////////////////////////////////////////////////////////////
void addToSensList (string conditionName, 
                    bool trueEventFalseCond, 
                    NODE* eventOrCondTree, 
                    NODE* hierRootNode, 
                    string &sensList);
/////////////////////////////////////////////////////////////////////////////////
/// Repace condition name
/////////////////////////////////////////////////////////////////////////////////
string replaceConditionName (string conditionName, 
                             NODE* condTree, 
                             NODE* hierRootNode, 
                             NODE* transactionNode);
/////////////////////////////////////////////////////////////////////////////////
/// Replace condition
/////////////////////////////////////////////////////////////////////////////////
string replaceCondition (string conditionName, 
                         NODE* condTree, 
                         NODE* hierRootNode, 
                         NODE* transactionNode);
/////////////////////////////////////////////////////////////////////////////////
/// Replace map
/////////////////////////////////////////////////////////////////////////////////
void replaceMap (string &header,
                 NODE* node,
                 string &replaceString);
/////////////////////////////////////////////////////////////////////////////////
/// Convert PDVL transation into SystemVerilog process
/////////////////////////////////////////////////////////////////////////////////
NODE* convertTrans2Process (NODE* transactionNode,
                            string &sensList,
                            string &regOrItemName, 
                            bool trueRegFalseItem,
                            bool trueRegFalseLatch,
                            bool skipPreEdge, 
                            bool defaultZero, 
                            bool *aboveEdge,
                            unsigned *piped,
                            unsigned pipeThis,
                            NODE* eventTree, 
                            NODE* condTree, 
                            NODE* datapathTree, 
                            NODE* coneNode, 
                            NODE* moduleNode,
                            NODE* hierRootNode);
/////////////////////////////////////////////////////////////////////////////////
/// Check if source cluster exists
/////////////////////////////////////////////////////////////////////////////////
NODE* checkSourceCluster (NODE* topClusterNameNode, 
                          NODE* subClusterNameNode, 
                          NODE* targetTree);
/////////////////////////////////////////////////////////////////////////////////
/// Check if target cluster exists
/////////////////////////////////////////////////////////////////////////////////
bool checkTargetCluster (NODE* targetNode, 
                         bool join, /* bool incrCluserPtr, unsigned *clCntPtr, */ 
                         NODE* sourceClusterNode);
/////////////////////////////////////////////////////////////////////////////////
/// Check target module
/////////////////////////////////////////////////////////////////////////////////
NODE* checkTargetModule (NODE* targetNode, 
                         NODE* modNode);
/////////////////////////////////////////////////////////////////////////////////
/// Join cluster module
/////////////////////////////////////////////////////////////////////////////////
bool joinClusterModule (NODE* modNode, 
                        NODE* commandBodyNode, 
                        bool incrCluserPtr, 
                        unsigned clusterId, 
                        NODE* sourceClusterNode);
/////////////////////////////////////////////////////////////////////////////////
/// Function executes PDVL join command.
/// Checks if source is a join body or a reference to another cluster.
/// Then checks (by name) if target is a known cluster or a known module.
/// When target is a cluster, then source is basically copied over.
/// When target is a module ...
/////////////////////////////////////////////////////////////////////////////////
bool joinCluster (NODE* commandBodyNode, 
                  NODE* modNode, 
                  unsigned *clCntPtr, 
                  NODE* targetTree);
/////////////////////////////////////////////////////////////////////////////////
/// Join PDVL body
/////////////////////////////////////////////////////////////////////////////////
bool joinBody (NODE* commandBodyNode, 
               NODE* modNode, 
               unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
///  Checks the complete tree, if NODE with given id exists.
/////////////////////////////////////////////////////////////////////////////////
bool checkConstructTreeNode (NODE* node, 
                             unsigned dbID);
/////////////////////////////////////////////////////////////////////////////////
///  Checks all NODEs on this "next" level, if NODE with given id exists.
/////////////////////////////////////////////////////////////////////////////////
bool checkConstructListNode (NODE* node, 
                             unsigned dbID);
/////////////////////////////////////////////////////////////////////////////////
/// Join PDVL construct
/////////////////////////////////////////////////////////////////////////////////
void joinConstruct (NODE* modNode, 
                    NODE* tmpSubNode, 
                    unsigned clusterId, 
                    unsigned dbID);
/////////////////////////////////////////////////////////////////////////////////
/// Searches for cluster (getCluster) and copies it (copyTree).
/// Then calls modifyAllEntriesName to add prefix.
/////////////////////////////////////////////////////////////////////////////////
bool uniquifyCluster (NODE* commandBodyNode, 
                      NODE* targetTree, 
                      NODE* newClustersNode, 
                      unsigned* clCnt);
/////////////////////////////////////////////////////////////////////////////////
/// Searches for all NODE with specific ids within the complete tree.
/// Then adds pre and postfix to the simple identifier below.
/////////////////////////////////////////////////////////////////////////////////
void modifyAllEntriesName (NODE* node, 
                           string &prefix, 
                           string &postfix, 
                           NODE* skipTree);
/////////////////////////////////////////////////////////////////////////////////
/// Searches for all NODE with specific ids within the complete tree.
/// Then replaces a substring with a given replacement string.
/////////////////////////////////////////////////////////////////////////////////
void replaceIndexName (NODE* node, 
                       bool exact, 
                       string &indexNameString, 
                       string &indexValueString);
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
/// Elaborate route command, level 2
/////////////////////////////////////////////////////////////////////////////////
bool routeCommandLevel2 (string header, 
                         string fromString, 
                         NODE* node, 
                         bool trueModuleFalseInstance, 
                         NODE* fromNode, 
                         NODE* toNode, 
                         string signalName, 
                         unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate route command, level 1
/////////////////////////////////////////////////////////////////////////////////
bool routeCommandLevel1 (NODE* fromNode, 
                         NODE* toNode, 
                         string signalName, 
                         NODE* modNode, 
                         unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate route command
/////////////////////////////////////////////////////////////////////////////////
bool routeCommand (NODE* routeNode, 
                   NODE* modNode, 
                   unsigned *clCntPtr);
/////////////////////////////////////////////////////////////////////////////////
/// Write SystemVerilog declaration
/////////////////////////////////////////////////////////////////////////////////
void writeDeclaration (string &out, 
                       unsigned identifier, 
                       string signalName, 
                       NODE* typeNode);
/////////////////////////////////////////////////////////////////////////////////
/// Remove assignment
/////////////////////////////////////////////////////////////////////////////////
bool removeAssignment (NODE* moveNode, 
                       NODE* modNode);
/////////////////////////////////////////////////////////////////////////////////
/// replace transaction emit entry
/////////////////////////////////////////////////////////////////////////////////
void replaceTransactionEmit (NODE* thisNode, 
                             unsigned level, 
                             NODE* oldSINode, 
                             NODE* newSINode);
/////////////////////////////////////////////////////////////////////////////////
/// replace transaction 
/////////////////////////////////////////////////////////////////////////////////
bool replaceTransaction (NODE* replaceNode, 
                         NODE* modNode);
/////////////////////////////////////////////////////////////////////////////////
/// Move assignment
/////////////////////////////////////////////////////////////////////////////////
bool moveAssignment (NODE* moveNode, 
                     NODE* modNode);
/////////////////////////////////////////////////////////////////////////////////
/// Get top-level module, sub-routine
/////////////////////////////////////////////////////////////////////////////////
NODE* getTopLevelModule_sub (NODE* node, 
                             bool pickUp, 
                             bool compare, 
                             NODE* rootNode, 
                             NODE* leafNode, 
                             NODE* instanciatedModulesNode);
/////////////////////////////////////////////////////////////////////////////////
/// Get top-level module
/////////////////////////////////////////////////////////////////////////////////
NODE* getTopLevelModule ();
