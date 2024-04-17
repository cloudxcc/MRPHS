//
// Copyright 2024 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

#include <mrphsPDVL2DB.h>

/////////////////////////////////////////////////////////////////////////////////
/// Key function of the PDVL to SV converter tool
/////////////////////////////////////////////////////////////////////////////////
NODE* convertPDVL2DB (NODE* sourceNode, 
                      string &topLevelName, 
                      string &outputDir) {
   dbNode = initNode(0);
   if (sourceNode -> sub == NULL)
   	  printf("Empty source.\n");
   if (sourceNode -> sub -> sub == NULL)
      printf("Empty source.\n");
   		
   dbClusterNode = initNode(0);
   dbModuleNode = initNode(0);
   dbSignalNode = initNode(0);
   dbPackageNode = initNode(0);
   unsigned clCnt = 0;
   unsigned moCnt = 0;

   if (reportLevel > 1)
      printf("2.1 Saving cluster.\n");
   saveCluster(sourceNode, &clCnt, &moCnt);

   if (reportLevel > 1)
      printf("2.2 Cluster elaboration.\n");
   clusterElaboration(1, &clCnt, &moCnt); 

   if (reportLevel > 1)
      printf("2.3 Structural composition.\n");
   structuralComposition(1, &clCnt, &moCnt); 

   NODE* topModuleNode = NULL;
   if (topLevelName.length() == 0)
      topModuleNode = getTopLevelModule();
   else {
      string tmpHeader = "";   
      topModuleNode = getModule(dbModuleNode, tmpHeader, topLevelName);
   }
   
   if (topModuleNode == NULL) {
      printf("Top level not found!\n");
      exit(-1);
   }
   
   if (reportLevel > 1)
      printf("2.4 Clock tree propagation.\n");
   NODE* eventTree = initNode(0);
   NODE* condTree = initNode(0);
   extractEventAndCondTree(topModuleNode, eventTree, condTree);  
   
   ////////////////////
   // remove command
   ////////////////////
   if (reportLevel > 1)
      printf("2.5 Handling remove commands.\n");
   moveRouteCommand(topModuleNode, true, 0, true, &clCnt);

   ////////////////////
   // remove command
   ////////////////////
   if (reportLevel > 1)
      printf("2.6 Handling replace commands.\n");
   moveRouteCommand(topModuleNode, true, 1, true, &clCnt);

   if (reportLevel > 1)
      printf("2.7 Logic joining process started.\n"); 
   NODE* hierRootNode = initNode(0);
   NODE* hierLeafNode = hierRootNode;
   logicJoining(topModuleNode, true, true, eventTree, condTree, hierRootNode, hierLeafNode);
   
   if (reportLevel > 1)
      printf("2.8 Handling move and replace commands.\n");
   ////////////////////
   // move command
   ////////////////////
   moveRouteCommand(topModuleNode, true, 2, true, &clCnt);

   if (reportLevel > 1)
      printf("2.9 Handling route commands.\n");
   ////////////////////
   // route command
   ////////////////////
   moveRouteCommand(topModuleNode, true, 3, true, &clCnt);

   if (reportUnfinishedCommands(dbModuleNode))
      exit(-1);
   
   return topModuleNode;

}    
/////////////////////////////////////////////////////////////////////////////////
/// Save all individual clusters into database
/////////////////////////////////////////////////////////////////////////////////
void saveCluster (NODE* sourceNode, 
                  unsigned *clCntPtr, 
                  unsigned *moCntPtr) {
   NODE* pdvlGrammarNode = sourceNode -> sub;
   while (1) {
      NODE* pdvlDeclarationNode = pdvlGrammarNode -> sub;
      while (1) {
         NODE* tmpNode = pdvlDeclarationNode -> sub; 
         if (tmpNode -> id == G_PDVL_CLUSTER_DECLARATION) {
            while (1) {
               string clusterName = getSI(tmpNode -> sub);
               if (checkTree(clusterName, dbClusterNode)) {
                  printf("ERR.SAVING.CLUSTER_ALREADY_DEFINED: %s\n", clusterName.c_str());
                  exit(-1);
               }
               *clCntPtr = *clCntPtr + 1;
               if (reportLevel > 2) {
                  printf("2.1.1 Saving cluster %s (%d) into database.\n", clusterName.c_str(), *clCntPtr);
               }
               NODE* newClusterCnt = initNode(*clCntPtr);
               newClusterCnt -> sub = tmpNode -> sub;
               addSITree(tmpNode -> sub, newClusterCnt, dbClusterNode);
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
         } else {
            while (1) {
               string clusterName = getSI(tmpNode -> sub);
               if (checkTree(clusterName, dbModuleNode)) {
                  printf("ERR.SAVING.CLUSTER_ALREADY_DEFINED: %s\n", clusterName.c_str());
                  exit(-1);
               }
               *moCntPtr = *moCntPtr + 1;
               if (reportLevel > 2) {
                  string clusterName = getSI(tmpNode -> sub);
                  printf("2.1.2 Saving commands for %s (%d) into database.\n", clusterName.c_str(), *moCntPtr);
               }
               NODE* newModuleCnt = initNode(*moCntPtr);
               NODE* newModuleBuild = initNode(DB_MODULE_BUILDS);
               newModuleCnt -> sub = newModuleBuild;
               newModuleBuild -> sub = tmpNode -> sub;
               NODE* dbListEntryNode = initNode(DB_LIST_ENTRY);  // 211012
               dbListEntryNode -> sub = newModuleCnt;
               addSITree(tmpNode -> sub, dbListEntryNode, dbModuleNode);
               newModuleBuild -> next = initNode(DB_MODULE_NAME);
               newModuleBuild -> next -> sub = getNode(tmpNode -> sub, G_SI);
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
         }
         if (pdvlDeclarationNode -> next == NULL)
            break;
         pdvlDeclarationNode = pdvlDeclarationNode -> next; 
      }
      if (pdvlGrammarNode -> next == NULL)
         break;
      pdvlGrammarNode = pdvlGrammarNode -> next; }
} 
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate given cluster, phase 1
/////////////////////////////////////////////////////////////////////////////////
bool clusterElaborationPhase1 (unsigned loop, 
                               NODE* node, 
                               NODE* newModulesNode, 
                               unsigned *clCntPtr, 
                               unsigned *moCntPtr) {
   bool debug = false;
   bool redo = false;
   bool modified = false;
   bool todo = false;
   NODE* clusterNode = dbNode -> sub;
   while (true) {
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            if (clusterElaborationPhase1(loop, node -> sub, newModulesNode, clCntPtr, moCntPtr))
               redo = true;
         } else {
         if (node -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub -> sub != NULL) {
            NODE* modNode = node -> sub -> sub -> sub;
            if (debug) printTree(modNode);
            NODE* buildNode = getNode(modNode -> sub, DB_MODULE_BUILDS);
            if (buildNode != NULL) {
               if (debug) printTree(modNode);
               if (reportLevel > 2) {
                  string clusterName = getSI(buildNode -> sub);
                  printf("2.2.1 Cluster elaboration, checking command in: %s (%d)\n", clusterName.c_str(), modNode -> id);
               }
               NODE* parameterTree = initNode(0);
               NODE* referenceModuleNode = initNode(0);
               string referenceModuleName;
               NODE* tmpNode = modNode; // -> sub -> next;
               if (debug) printTree(modNode);
               ///////////////////////////////////
               // Get parameter
               ///////////////////////////////////
               while (1) {
                  if (tmpNode -> sub != NULL) {
                     if (debug) printf("a %d %d\n", tmpNode -> sub -> id, tmpNode -> sub -> sub -> id);
                     if (tmpNode -> sub -> id == G_PDVL_DECLARATION) {
                        NODE* tmpSubNode = tmpNode -> sub; 
                        if (debug) printTree(tmpNode);
                        while (1) {
                           if (debug) printf("%d\n", tmpSubNode -> sub -> id);
                           if (tmpSubNode -> sub != NULL) {
                              ///////////////////////////////////
                              // parameter
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_SV_PARAMETER_DECLARATION) {
                                 if (debug) printf("check parameter pickup.\n"); // %s\n", clusterName.c_str());
                                 if (debug) printTree(tmpSubNode -> sub);
                                 addSITree(tmpSubNode -> sub -> sub -> sub -> sub, tmpSubNode -> sub -> sub -> sub -> sub -> next, parameterTree);
                                 if (debug) printf("--------\n"); 
                              }
                           }
                           if (tmpSubNode -> next == NULL)
                              break;
                           tmpSubNode = tmpSubNode -> next;
                        }
                     }
                  }
                  if (tmpNode -> next == NULL)
                    break;
                  tmpNode = tmpNode -> next;
               }
               ///////////////////////////////////
               // Skip module id, first entry
               ///////////////////////////////////
               tmpNode = modNode -> sub;
               ///////////////////////////////////
               // Get parameter
               ///////////////////////////////////
               while (1) {
                  if (debug) printf("a %d\n", tmpNode -> id);
                  if (tmpNode -> id == DB_MODULE_BUILDS)
                  if (tmpNode -> sub != NULL) 
                  if (tmpNode -> sub -> next != NULL) {
                     if (debug) printf("b %d\n", tmpNode -> sub -> id);
                     //if (tmpNode -> sub -> id == G_PDVL_BUILD_COMMAND_BODY) {
                        NODE* refNode = NULL;
                        ///////////////////////////////////
                        // Skip module id, first entry
                        ///////////////////////////////////
                        NODE* tmpSubNode = tmpNode -> sub -> next; 
                        if (debug) printTree(tmpSubNode);
                        while (1) {
                           bool progRefNode = true;
                           if (debug) printf("%d\n", tmpSubNode -> sub -> id);
                           if (tmpSubNode -> sub != NULL) {
                              if (debug) printf("------------------------------------\n"); 
                              if (debug) printTree(tmpSubNode -> sub); 
                              ///////////////////////////////////
                              // parameter
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_SV_PARAMETER_DECLARATION) {
                                 if (debug) printf("check parameter pickup.\n"); // %s\n", clusterName.c_str());
                                 if (debug) printTree(tmpSubNode -> sub);
                                 addSITree(tmpSubNode -> sub -> sub -> sub -> sub, tmpSubNode -> sub -> sub -> sub -> sub -> next, parameterTree);
                                 if (debug) printf("--------\n"); 
                                 
                              }
                           }
                           if (tmpSubNode -> next == NULL)
                              break;
                           if (progRefNode)
                              refNode = tmpSubNode;
                           tmpSubNode = tmpSubNode -> next;
                        }
                  }
                  if (tmpNode -> next == NULL)
                    break;
                  tmpNode = tmpNode -> next;
               }
               ///////////////////////////////////
               // Skip module id, first entry
               ///////////////////////////////////
               tmpNode = modNode -> sub;
               ///////////////////////////////////
               // Foreach PDVL command, execute when possible
               ///////////////////////////////////
               while (1) {
                  if (debug) printf("a %d\n", tmpNode -> id);
                  if (tmpNode -> id == DB_MODULE_BUILDS)
                  if (tmpNode -> sub != NULL) 
                  if (tmpNode -> sub -> next != NULL) {
                     if (debug) printf("b %d\n", tmpNode -> sub -> id);
                     //if (tmpNode -> sub -> id == G_PDVL_BUILD_COMMAND_BODY) {
                        NODE* refNode = NULL;
                        ///////////////////////////////////
                        // Skip module id, first entry
                        ///////////////////////////////////
                        NODE* tmpSubNode = tmpNode -> sub -> next; 
                        while (1) {
                           if (debug) printf("------------------------------------\n"); 
                           if (debug) printTree(tmpSubNode);
                           bool progRefNode = true;
                           if (debug) printf("%d\n", tmpSubNode -> sub -> id);
                           if (tmpSubNode -> sub != NULL) {
                              if (debug) printf("------------------------------------\n"); 
                              if (debug) printTree(tmpSubNode -> sub); 
                              bool removeCommand = false;
                              ///////////////////////////////////
                              // join body
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_JOIN_BODY_COMMAND) { 
                                 if (debug) printTree(4, tmpSubNode -> sub -> sub);
                                 //exit(-1);
                                 removeCommand = joinBody(tmpSubNode -> sub -> sub -> sub, modNode, clCntPtr); //, targetTree);
                              } else
                              ///////////////////////////////////
                              // if generate (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if ( (tmpSubNode -> sub -> id == G_PDVL_IF_COMMAND) ) {
                                 removeCommand = elaboratePDVLIf(tmpSubNode, tmpSubNode -> sub, parameterTree);
                              } else
                              ///////////////////////////////////
                              // icase generate (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if ( (tmpSubNode -> sub -> id == G_PDVL_CASE_COMMAND) ) {
                                 removeCommand = elaboratePDVLCase(tmpSubNode, tmpSubNode -> sub, parameterTree);
                              } else
                              ///////////////////////////////////
                              // foreach (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_FOREACH_COMMAND) {
                                 removeCommand = elaboratePDVLForeach(tmpSubNode, tmpSubNode -> sub, parameterTree);
                              } else
                              ///////////////////////////////////
                              // for (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_FOR_COMMAND) {
                                 removeCommand = elaboratePDVLFor(tmpSubNode, tmpSubNode -> sub, parameterTree);
                              }
                              if (removeCommand) {
                                 if (debug) printf("removing command\n");
                                 modified = true;
                                 if (refNode == NULL) {
                                    // keep cluster name
                                    tmpNode -> sub -> next = tmpSubNode -> next;
                                    progRefNode = false; 
                                 } else {
                                    refNode -> next = tmpSubNode -> next; 
                                    progRefNode = false; 
                                 }
                              }
                           }
                           if (tmpSubNode -> next == NULL)
                              break;
                           if (progRefNode)
                              refNode = tmpSubNode;
                           tmpSubNode = tmpSubNode -> next;
                        }
                     }
                     if (tmpNode -> next == NULL)
                       break;
                     tmpNode = tmpNode -> next;
                  }
               }
               if (debug) printf("cont 1\n");
               if (node -> sub != NULL)
               if (node -> sub -> next != NULL)
                  if (clusterElaborationPhase1(loop, node -> sub -> next, newModulesNode, clCntPtr, moCntPtr))
                     redo = true;
            }
         } 
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
   if (debug) printf("cont 3\n");

   return modified | redo;
}
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate given cluster, phase 2
/////////////////////////////////////////////////////////////////////////////////
bool clusterElaborationPhase2 (unsigned loop, 
                               NODE* node, 
                               NODE* targetTree, 
                               NODE* newClustersNode, 
                               unsigned *clCntPtr) {
   bool debug = false;
   bool redo = false;
   bool modified = false;
   bool todo = false;
   NODE* clusterNode = dbNode -> sub;
   while (true) {
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            if (clusterElaborationPhase2(loop, node -> sub, targetTree, newClustersNode, clCntPtr))
               redo = true;
         } else {
         if (node -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub -> sub != NULL) {
            NODE* modNode = node -> sub -> sub -> sub;
            NODE* buildNode = getNode(modNode -> sub, DB_MODULE_BUILDS);
            if (buildNode != NULL) {
               if (debug) printTree(modNode);
               if (reportLevel > 2) {
                  string clusterName = getSI(buildNode -> sub);
                  printf("2.2.2 Cluster elaboration, checking command in: %s (%d)\n", clusterName.c_str(), modNode -> id);
               }
               NODE* parameterTree = initNode(0);
               NODE* referenceModuleNode = initNode(0);
               string referenceModuleName;
               NODE* tmpNode = modNode;
               if (debug) printTree(modNode);
               ///////////////////////////////////
               // Skip module id, first entry
               ///////////////////////////////////
               tmpNode = modNode -> sub;
               ///////////////////////////////////
               // Foreach PDVL command, execute when possible
               ///////////////////////////////////
               while (1) {
                  if (debug) printf("a %d\n", tmpNode -> id);
                  if (tmpNode -> id == DB_MODULE_BUILDS)
                  if (tmpNode -> sub != NULL) 
                  if (tmpNode -> sub -> next != NULL) {
                     if (debug) printf("b %d\n", tmpNode -> sub -> id);
                     //if (tmpNode -> sub -> id == G_PDVL_BUILD_COMMAND_BODY) {
                        NODE* refNode = NULL;
                        ///////////////////////////////////
                        // Skip module id, first entry
                        ///////////////////////////////////
                        NODE* tmpSubNode = tmpNode -> sub -> next; 
                        while (1) {
                           bool progRefNode = true;
                           if (debug) printf("%d\n", tmpSubNode -> sub -> id);
                           if (tmpSubNode -> sub != NULL) {
                              if (debug) printf("------------------------------------\n"); 
                              if (debug) printTree(tmpSubNode -> sub); 
                              bool removeCommand = false;
                              ///////////////////////////////////
                              // join body
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_JOIN_BODY_COMMAND) { 
                                 if (debug) printTree(4, tmpSubNode -> sub -> sub);
                                 //exit(-1);
                                 removeCommand = joinBody(tmpSubNode -> sub -> sub -> sub, modNode, clCntPtr); //, targetTree);
                              } else
                              ///////////////////////////////////
                              // uniquify
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_UNIQUIFY_COMMAND) {
                                 removeCommand = uniquifyCluster(tmpSubNode -> sub -> sub, targetTree, newClustersNode, clCntPtr);
                              }
                              if (removeCommand) {
                                 if (debug) printf("removing command\n");
                                 modified = true;
                                 if (refNode == NULL) {
                                    // keep cluster name
                                    tmpNode -> sub -> next = tmpSubNode -> next;
                                    progRefNode = false; 
                                 } else {
                                    refNode -> next = tmpSubNode -> next; 
                                    progRefNode = false; 
                                 }
                              }
                           }
                           if (tmpSubNode -> next == NULL)
                              break;
                           if (progRefNode)
                              refNode = tmpSubNode;
                           tmpSubNode = tmpSubNode -> next;
                        }
                     }
                     if (tmpNode -> next == NULL)
                       break;
                     tmpNode = tmpNode -> next;
                  }
               }
               if (debug) printf("cont 1\n");
               if (node -> sub != NULL)
               if (node -> sub -> next != NULL)
                  if (clusterElaborationPhase2(loop, node -> sub -> next, targetTree, newClustersNode, clCntPtr))
                     redo = true;
            }
         } 
      }
      if (debug) printf("cont 2\n"); 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
   if (debug) printf("cont 3\n");
   return modified | redo;
}
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate given cluster, phase 3
/////////////////////////////////////////////////////////////////////////////////
bool clusterElaborationPhase3 (unsigned loop, 
                               NODE* node, 
                               NODE* targetTree, 
                               NODE* newModulesNode, 
                               NODE* newClustersNode, 
                               unsigned *clCntPtr, 
                               unsigned *moCntPtr) {
   bool debug = false;
   bool redo = false;
   bool modified = false;
   bool todo = false;
   NODE* clusterNode = dbNode -> sub;
   while (true) {
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            if (clusterElaborationPhase3(loop, node -> sub, targetTree, newModulesNode, newClustersNode, clCntPtr, moCntPtr))
               redo = true;
         } else
         if (node -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub -> sub != NULL) {
            NODE* modNode = node -> sub -> sub;
            NODE* buildNode = getNode(modNode -> sub, G_PDVL_CLUSTER_IDENTIFIER);
            if (buildNode != NULL) {
               if (debug) printTree(modNode);
               if (reportLevel > 2) {
                  string clusterName = getSI(buildNode -> sub);
                  printf("2.2.3 Cluster elaboration, checking command in: %s (%d)\n", clusterName.c_str(), modNode -> id);
               }
               NODE* parameterTree = initNode(0);
               NODE* referenceModuleNode = initNode(0);
               string referenceModuleName;
               NODE* tmpNode = modNode -> sub; // -> next;
               if (debug) printf("----------------------------- tmpNode:\n");
               if (debug) printTree(tmpNode);
               ///////////////////////////////////
               // Get parameter
               ///////////////////////////////////
               while (1) {
                  if (tmpNode -> id == G_PDVL_CLUSTER_DECLARATION_BODY)
                  if (tmpNode -> sub != NULL) {
                     if (debug) printf("b %d\n", tmpNode -> sub -> id);
                     if (debug) printf("a %d %d\n", tmpNode -> sub -> id, tmpNode -> sub -> sub -> id);
                     //if (tmpNode -> sub -> id == G_PDVL_PDVL_DECLARATION) {
                        NODE* tmpSubNode = tmpNode;
                        if (debug) printTree(tmpNode);
                        if (tmpSubNode -> sub != NULL) {
                           ///////////////////////////////////
                           // uniquify
                           ///////////////////////////////////
                           if (tmpSubNode -> sub -> id == G_SV_PARAMETER_DECLARATION) {
                              if (debug) printf("check parameter pickup.\n"); // %s\n", clusterName.c_str());
                              if (debug) printTree(tmpSubNode -> sub);
                              addSITree(tmpSubNode -> sub -> sub -> sub -> sub, tmpSubNode -> sub -> sub -> sub -> sub -> next, parameterTree);
                              if (debug) printf("--------\n"); 
                           }
                        }
                  }
                  if (tmpNode -> next == NULL)
                    break;
                  tmpNode = tmpNode -> next;
               } 
               if (debug) printSITree(parameterTree);
               ///////////////////////////////////
               // Skip module id, first entry
               ///////////////////////////////////
               tmpNode = modNode -> sub;
               ///////////////////////////////////
               // Foreach PDVL command, execute when possible
               ///////////////////////////////////
               NODE* refNode = NULL;
               while (1) {
                  if (tmpNode -> id == G_PDVL_CLUSTER_DECLARATION_BODY)
                  if (tmpNode -> sub != NULL) {
                     bool progRefNode = true;
                     if (tmpNode -> sub != NULL) {
                        if (debug) printf("------------------------------------\n"); 
                        if (debug) printTree(tmpNode -> sub); 
                        bool removeCommand = false;
                        ///////////////////////////////////
                        // if generate (needs to be elaborated !!!)
                        ///////////////////////////////////
                        if ( (tmpNode -> sub -> id == G_PDVL_IF_DECLARATION) ) {
                           removeCommand = elaboratePDVLIf(tmpNode, tmpNode -> sub, parameterTree);
                        } else
                        ///////////////////////////////////
                        // icase generate (needs to be elaborated !!!)
                        ///////////////////////////////////
                        if ( (tmpNode -> sub -> id == G_PDVL_CASE_DECLARATION) ) {
                           removeCommand = elaboratePDVLCase(tmpNode, tmpNode -> sub, parameterTree);
                        } else
                        ///////////////////////////////////
                        // foreach (needs to be elaborated !!!)
                        ///////////////////////////////////
                        if (tmpNode -> sub -> id == G_PDVL_FOREACH_DECLARATION) {
                           removeCommand = elaboratePDVLForeach(tmpNode, tmpNode -> sub, parameterTree);
                        } else
                        ///////////////////////////////////
                        // for (needs to be elaborated !!!)
                        ///////////////////////////////////
                        if (tmpNode -> sub -> id == G_PDVL_FOR_DECLARATION) {
                           removeCommand = elaboratePDVLFor(tmpNode, tmpNode -> sub, parameterTree);
                        }
                        if (removeCommand) {
                           modified = true;
                           if (refNode == NULL) {
                              modNode -> sub -> next = tmpNode -> next;
                              progRefNode = false; 
                           } else {
                              refNode -> next = tmpNode -> next; 
                              progRefNode = false; 
                           }
                        }
                        if (progRefNode)
                           refNode = tmpNode;
                     }
                  }
                  if (tmpNode -> next == NULL)
                    break;
                  tmpNode = tmpNode -> next;
               }
               if (debug) printf("cont 1\n");
               if (node -> sub != NULL)
               if (node -> sub -> next != NULL)
                  if (clusterElaborationPhase3(loop, node -> sub -> next, targetTree, newModulesNode, newClustersNode, clCntPtr, moCntPtr))
                     redo = true;
            }
         } 
      }
      if (debug) printf("cont 2\n");
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
   if (debug) printf("cont 3\n");
   return modified | redo;
}
/////////////////////////////////////////////////////////////////////////////////
/// Execute "place" command
/////////////////////////////////////////////////////////////////////////////////
bool executePlaceCommand (NODE* commandBodyNode, 
                          NODE* modNode, 
                          NODE* nonEmptyBuilds, 
                          NODE* newModulesNode, 
                          NODE* newClustersNode, 
                          unsigned *clCntPtr, 
                          unsigned *moCntPtr) {
   bool debug = false;
   bool removeCommand = false;
   
   if (debug) printf("executePlaceCommand.\n");
   if (debug) printTree(commandBodyNode);
   if (checkSITree(commandBodyNode -> sub -> sub, nonEmptyBuilds -> sub)) {
       if (debug) printf("Skip because not empty.\n");
       return false;
   }

   if (commandBodyNode -> next != NULL)
   if (commandBodyNode -> next -> sub != NULL) {
   
      /////////////////////////////////////////////
      // Determine targetModuleHierNode
      //    If hierarchical 
      //       => go through hierarchy, 
      //          return false if path does not exist yet
      //          use lowest module as targetModuleHierNode if path exist
      /////////////////////////////////////////////
      NODE* targetModuleHierNode = commandBodyNode -> next -> sub;

      while (targetModuleHierNode -> next != NULL) {
          if (debug) printf("---------------------targetModuleHierNode executePlace: \n");
          if (debug) printTree(targetModuleHierNode);
          modNode = getSubModule(targetModuleHierNode, modNode);
          if (modNode == NULL) {
             if (debug) printf("modNode == NULL\n");
             return false;
          }
          targetModuleHierNode = targetModuleHierNode -> next;
      } 
      if (debug) printf("---------------------targetModuleHierNode (final): \n");
      if (debug) printTree(targetModuleHierNode);
      if (debug) printf("---------------------modNode (final): \n");
      if (debug) printTree(modNode);
      
      /////////////////////////////////////////////
      // generate:
      //    moduleNode (moduleCnt)
      //       copied of emtpy
      // add moduleNode (moduleCnt) to newModulesNode
      /////////////////////////////////////////////
      NODE* moduleIdentifierNode = getNode(commandBodyNode, G_SI);
      NODE* moduleNode = getSITreeNode(moduleIdentifierNode -> sub, dbModuleNode -> sub);
      string moduleIdentifiername = getSI(moduleIdentifierNode);

      /////////////////////////////////////////////
      // new module place
      /////////////////////////////////////////////
      if (moduleNode == NULL) {
         *moCntPtr = *moCntPtr + 1;
         if (debug) printf("Module not found %d.\n", *moCntPtr);
         if (debug) printTree(moduleIdentifierNode);
         moduleNode = initNode(*moCntPtr);
         NODE* dbListEntryNode = initNode(DB_LIST_ENTRY);  // 211012
         dbListEntryNode -> sub = moduleNode;
         moduleNode -> sub = initNode(DB_MODULE_NAME);
         moduleNode -> sub -> sub = moduleIdentifierNode;
         NODE* rootNode = initNode(0);
         addSITree(moduleIdentifiername, dbListEntryNode, rootNode);
         if (debug) printf("----------------------- newModulesNode\n");
         if (debug) printTree(newModulesNode);
         if (newModulesNode -> sub == NULL)
            mergeSITreesSubList(rootNode, newModulesNode);
         else
            mergeSITreesSubList(rootNode -> sub, newModulesNode -> sub);
         if (debug) printf("----------------------- newModulesNode\n");
         if (debug) printTree(8, newModulesNode);
         if (debug) printSITree(newModulesNode);
      } else {
      /////////////////////////////////////////////
      // Module exists from build command => copy
      /////////////////////////////////////////////
         *moCntPtr = *moCntPtr + 1;
         if (debug) printf("Module found %d.\n", *moCntPtr);
         if (debug) printTree(moduleNode);
         if (debug) printTree(moduleIdentifierNode -> sub);
         NODE* tmp2Node = initNode(*moCntPtr);
         NODE* copiedJoinedClusterHashNode = initNode(0);
         tmp2Node -> sub = copyModuleTree(moduleNode -> sub -> sub, copiedJoinedClusterHashNode, clCntPtr, moCntPtr);
         if (debug) printTree(copiedJoinedClusterHashNode);
         moduleNode = tmp2Node;
         NODE* dbListEntryNode = initNode(DB_LIST_ENTRY); 
         dbListEntryNode -> sub = moduleNode;
         NODE* rootNode = initNode(0);
         addSITree(moduleIdentifiername, dbListEntryNode, rootNode);
         if (debug) printf("----------------------- rootNode\n");
         if (debug) printTree(rootNode);
         mergeSITreesSubList(rootNode, newModulesNode);
         if (debug) printf("----------------------- newModulesNode\n");
         if (debug) printTree(newModulesNode);
      }
      /////////////////////////////////////////////
      // generate:
      //    interNode (0)
      //       hier_node (SI)
      //          0
      //             moduleNode
      /////////////////////////////////////////////
      NODE* interNode = initNode(0);
      if (debug) printf("----------------------- interNode\n");
      if (debug) printTree(interNode);
      addSITree(getNode(targetModuleHierNode, G_SI), moduleNode, interNode);

      if (debug) printf("-----------------------\n");
      if (debug) printTree(getNode(commandBodyNode -> next -> sub, G_SI));

      /////////////////////////////////////////////
      // generate:
      //   modNode
      //      DB_SUB_MODULES
      //         Module Name SI
      //             interNode
      /////////////////////////////////////////////
      if (modNode -> sub == NULL) {
         if (debug) printf("modNode -> sub == NULL\n");
         NODE* dbEntryNode = initSubNode(modNode, DB_SUB_MODULES);
         addSITree(getNode(commandBodyNode, G_SI), interNode -> sub, dbEntryNode);
      } else {
         NODE* dbEntryNode = modNode -> sub;
         while (true) {
            if (dbEntryNode -> id == DB_SUB_MODULES) {
               addSITree(getNode(commandBodyNode, G_SI), interNode -> sub, dbEntryNode);
               break; 
            }
            if (dbEntryNode -> next == NULL) {
               NODE* dbSubNode = initNode(DB_SUB_MODULES);
               dbEntryNode -> next = dbSubNode; 
            }
            dbEntryNode = dbEntryNode -> next;
         }
      }
      removeCommand = true;
   }

   return removeCommand;
}
/////////////////////////////////////////////////////////////////////////////////
/// Structural composition, phase 1
/////////////////////////////////////////////////////////////////////////////////
void structuralCompositionPhase1 (unsigned loop, 
                                  NODE* node, 
                                  NODE* targetTree, 
                                  NODE* nonEmptyBuilds) {
   bool debug = false;
   while (true) {
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0)
            structuralCompositionPhase1(loop, node -> sub, targetTree, nonEmptyBuilds);
         else 
         if (node -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub -> sub != NULL) {
            NODE* modNode = node -> sub -> sub -> sub;
            NODE* buildNode = getNode(modNode -> sub, DB_MODULE_BUILDS);
            if (buildNode != NULL) {
               if (reportLevel > 2) {
                  string clusterName = getSI(buildNode -> sub);
                  printf("2.3.1 Structural composition, checking command in: %s (%d)\n", clusterName.c_str(), modNode -> id);
               }
               if (debug) printTree(modNode);
               NODE* tmpNode = modNode -> sub;
               ///////////////////////////////////
               // Foreach PDVL command, execute when possible
               ///////////////////////////////////
               bool empty = true;
               while (1) {
                  if (debug) printf("a %d\n", tmpNode -> id);
                  if (tmpNode -> id == DB_MODULE_BUILDS)
                  if (tmpNode -> sub != NULL) 
                  if (tmpNode -> sub -> next != NULL) {
                     if (debug) printf("b %d\n", tmpNode -> sub -> id);
                     //if (tmpNode -> sub -> id == G_PDVL_BUILD_COMMAND_BODY) {
                        NODE* refNode = NULL;
                        ///////////////////////////////////
                        // Skip module id, first entry
                        ///////////////////////////////////
                        NODE* tmpSubNode = tmpNode -> sub -> next; 
                        while (1) {
                           bool progRefNode = true;
                           if (debug) printf("%d\n", tmpSubNode -> sub -> id);
                           if (tmpSubNode -> sub != NULL) {
                              if (debug) printf("------------------------------------\n"); 
                              if (debug) printTree(tmpSubNode -> sub); 
                              ///////////////////////////////////
                              // place
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_PLACE_COMMAND) { 
                                 empty = false;
                              } else
                              ///////////////////////////////////
                              // join cluster -> cluster
                              ///////////////////////////////////
                              if ( (tmpSubNode -> sub -> id == G_PDVL_JOIN_CLUSTER_COMMAND) ) {
                                 if (tmpSubNode -> sub -> sub != NULL)
                                 if (tmpSubNode -> sub -> sub -> next != NULL) {
                                    NODE* hierNameNode = tmpSubNode -> sub -> sub -> next -> sub;
                                    if (debug) printTree(hierNameNode);
                                    if (dbClusterNode -> sub != NULL) {
                                       NODE* targetClusterNode = getSITreeNode(hierNameNode -> sub, dbClusterNode -> sub);
                                       if (targetClusterNode != NULL) {
                                          if (debug) printf("insert\n");
                                          addSITree(targetClusterNode -> sub, NULL, targetTree); 
                                       }
                                    }
                                 } 
                                 empty = false;
                              } else
                              ///////////////////////////////////
                              // join body
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_JOIN_BODY_COMMAND) {
                                 if (tmpSubNode -> sub -> sub -> sub != NULL)
                                 if (tmpSubNode -> sub -> sub -> sub -> next != NULL) {
                                    NODE* hierNameNode = tmpSubNode -> sub -> sub -> sub -> next -> sub;
                                    if (debug) printTree(hierNameNode);
                                    if (dbClusterNode -> sub != NULL) {
                                       NODE* targetClusterNode = getSITreeNode(hierNameNode -> sub, dbClusterNode -> sub);
                                       if (targetClusterNode != NULL) {
                                          if (debug) printf("insert\n");
                                          addSITree(targetClusterNode -> sub, NULL, targetTree); 
                                       }
                                    }
                                 } 
                                 if (debug) printTree(4, tmpSubNode -> sub -> sub);
                                 empty = false;
                              } else
                              ///////////////////////////////////
                              // uniquify
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_UNIQUIFY_COMMAND) {
                                 empty = false;
                              } else
                              ///////////////////////////////////
                              // foreach (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_FOREACH_COMMAND) {
                                 empty = false;
                              }
                           }
                           if (tmpSubNode -> next == NULL)
                              break;
                           if (progRefNode)
                              refNode = tmpSubNode;
                           tmpSubNode = tmpSubNode -> next;
                        }
                  }
                  if (tmpNode -> next == NULL)
                    break;
                  tmpNode = tmpNode -> next;
               } 
               //////////////////////////////////////////////////
               // add to nonEmptyBuilds when not empty (move doesn't count)
               //////////////////////////////////////////////////
               if (!(empty)) {
                  addSITree(buildNode -> sub, NULL, nonEmptyBuilds); 
               }
            }
            if (debug) printf("cont 1\n");
            if (node -> sub -> next != NULL)
               structuralCompositionPhase1(loop, node -> sub -> next, targetTree, nonEmptyBuilds);
         } 
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   

   return;
}
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
                                  unsigned *moCntPtr) {
   bool debug = false;
   bool redo = false;
   bool modified = false;
   bool todo = false;
   NODE* clusterNode = dbNode -> sub;
   while (true) {
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            if (structuralCompositionPhase2(loop, node -> sub, targetTree, nonEmptyBuilds, newModulesNode, newClustersNode, clCntPtr, moCntPtr))
               redo = true;
         } else {
         if (node -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub -> sub != NULL) {
            NODE* modNode = node -> sub -> sub -> sub;
            NODE* buildNode = getNode(modNode -> sub, DB_MODULE_BUILDS);
            if (buildNode != NULL) {
               if (debug) printTree(modNode);
               if (reportLevel > 2) {
                  string clusterName = getSI(buildNode -> sub);
                  printf("2.3.2 Structural composition, checking command in: %s (%d)\n", clusterName.c_str(), modNode -> id);
               }
               NODE* parameterTree = initNode(0);
               NODE* referenceModuleNode = initNode(0);
               string referenceModuleName;
               NODE* tmpNode = modNode;
               if (debug) printTree(modNode);
               ///////////////////////////////////
               // Skip module id, first entry
               ///////////////////////////////////
               tmpNode = modNode -> sub;
               ///////////////////////////////////
               // Foreach PDVL command, execute when possible
               ///////////////////////////////////
               while (1) {
                  if (debug) printf("a %d\n", tmpNode -> id);
                  if (tmpNode -> id == DB_MODULE_BUILDS)
                  if (tmpNode -> sub != NULL) 
                  if (tmpNode -> sub -> next != NULL) {
                     if (debug) printf("b %d\n", tmpNode -> sub -> id);
                     //if (tmpNode -> sub -> id == G_PDVL_BUILD_COMMAND_BODY) {
                        NODE* refNode = NULL;
                        ///////////////////////////////////
                        // Skip module id, first entry
                        ///////////////////////////////////
                        NODE* tmpSubNode = tmpNode -> sub -> next; 
                        while (1) {
                           bool progRefNode = true;
                           if (debug) printf("%d\n", tmpSubNode -> sub -> id);
                           if (tmpSubNode -> sub != NULL) {
                              if (debug) printf("------------------------------------\n"); 
                              if (debug) printTree(tmpSubNode -> sub); 
                              bool removeCommand = false;
                              ///////////////////////////////////
                              // place
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_PLACE_COMMAND) {
                                 NODE* commandBodyNode = tmpSubNode -> sub -> sub;
                                 removeCommand = executePlaceCommand(commandBodyNode, modNode, nonEmptyBuilds, newModulesNode, newClustersNode, clCntPtr, moCntPtr);
                              }
                              if (removeCommand) {
                                 if (debug) printf("removing command\n");
                                 modified = true;
                                 if (refNode == NULL) {
                                    tmpNode -> sub -> next = tmpSubNode -> next;
                                    progRefNode = false; 
                                 } else {
                                    refNode -> next = tmpSubNode -> next; 
                                    progRefNode = false; 
                                 }
                              }
                           }
                           if (tmpSubNode -> next == NULL)
                              break;
                           if (progRefNode)
                              refNode = tmpSubNode;
                           tmpSubNode = tmpSubNode -> next;
                        }
                     }
                     if (tmpNode -> next == NULL)
                       break;
                     tmpNode = tmpNode -> next;
                  }
               }
               if (debug) printf("cont 1\n");
               if (node -> sub != NULL)
               if (node -> sub -> next != NULL)
                  if (structuralCompositionPhase2(loop, node -> sub -> next, targetTree, nonEmptyBuilds, newModulesNode, newClustersNode, clCntPtr, moCntPtr))
                     redo = true;
            }
         } 
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
   if (debug) printf("cont 3\n");
   return modified | redo;
}
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
                                  unsigned *moCntPtr) {
   bool debug = false;
   bool redo = false;
   bool modified = false;
   bool todo = false;
   NODE* clusterNode = dbNode -> sub;
   while (true) {
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            if (structuralCompositionPhase3(loop, node -> sub, targetTree, nonEmptyBuilds, newModulesNode, newClustersNode, clCntPtr, moCntPtr))
               redo = true;
         } else {
         if (node -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub -> sub != NULL) {
            NODE* modNode = node -> sub -> sub -> sub;
            NODE* buildNode = getNode(modNode -> sub, DB_MODULE_BUILDS);
            if (buildNode != NULL) {
               if (debug) printTree(modNode);
               if (reportLevel > 2) {
                  string clusterName = getSI(buildNode -> sub);
                  printf("2.3.3 Structural composition, checking command in: %s (%d)\n", clusterName.c_str(), modNode -> id);
               }
               NODE* parameterTree = initNode(0);
               NODE* referenceModuleNode = initNode(0);
               string referenceModuleName;
               NODE* tmpNode = modNode;
               if (debug) printTree(modNode);
               ///////////////////////////////////
               // Skip module id, first entry
               ///////////////////////////////////
               tmpNode = modNode -> sub;
               ///////////////////////////////////
               // Foreach PDVL command, execute when possible
               ///////////////////////////////////
               while (1) {
                  if (debug) printf("a %d\n", tmpNode -> id);
                  if (tmpNode -> id == DB_MODULE_BUILDS)
                  if (tmpNode -> sub != NULL) 
                  if (tmpNode -> sub -> next != NULL) {
                     if (debug) printf("b %d\n", tmpNode -> sub -> id);
                     //if (tmpNode -> sub -> id == G_PDVL_BUILD_COMMAND_BODY) {
                        NODE* refNode = NULL;
                        ///////////////////////////////////
                        // Skip module id, first entry
                        ///////////////////////////////////
                        NODE* tmpSubNode = tmpNode -> sub -> next; 
                        while (1) {
                           bool progRefNode = true;
                           if (debug) printf("%d\n", tmpSubNode -> sub -> id);
                           if (tmpSubNode -> sub != NULL) {
                              if (debug) printf("------------------------------------\n"); 
                              if (debug) printTree(tmpSubNode -> sub); 
                              bool removeCommand = false;
                              ///////////////////////////////////
                              // place
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_PLACE_COMMAND) {
                              } else
                              ///////////////////////////////////
                              // join cluster
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_JOIN_CLUSTER_COMMAND) {
                                 removeCommand = joinCluster(tmpSubNode -> sub -> sub, modNode, clCntPtr, targetTree);
                              } else
                              ///////////////////////////////////
                              // join body
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_JOIN_BODY_COMMAND) { 
                                 removeCommand = joinBody(tmpSubNode -> sub -> sub -> sub, modNode, clCntPtr); //, targetTree);
                              } else
                              ///////////////////////////////////
                              // uniquify
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_UNIQUIFY_COMMAND) {
                                 removeCommand = uniquifyCluster(tmpSubNode -> sub -> sub, targetTree, newClustersNode, clCntPtr);
                              } else
                              ///////////////////////////////////
                              // if generate (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if ( (tmpSubNode -> sub -> id == G_PDVL_IF_COMMAND)   ) {
                                 removeCommand = elaboratePDVLIf(tmpSubNode, tmpSubNode -> sub, parameterTree);
                              } else
                              ///////////////////////////////////
                              // case generate (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if ( (tmpSubNode -> sub -> id == G_PDVL_CASE_COMMAND) ) {
                                 removeCommand = elaboratePDVLCase(tmpSubNode, tmpSubNode -> sub, parameterTree);
                              } else
                              ///////////////////////////////////
                              // foreach (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_FOREACH_COMMAND) {
                                 removeCommand = elaboratePDVLForeach(tmpNode, tmpSubNode -> sub, parameterTree);
                              } else
                              ///////////////////////////////////
                              // for (needs to be elaborated !!!)
                              ///////////////////////////////////
                              if (tmpSubNode -> sub -> id == G_PDVL_FOR_COMMAND) {
                                 removeCommand = elaboratePDVLFor(tmpNode, tmpSubNode -> sub, parameterTree);
                              } else
                                 if (debug) printf("\t%d\n", tmpSubNode -> sub -> id);
                              if (removeCommand) {
                                 if (debug) printf("removing command\n");
                                 modified = true;
                                 if (refNode == NULL) {
                                    tmpNode -> sub -> next = tmpSubNode -> next;
                                    progRefNode = false; 
                                 } else {
                                    refNode -> next = tmpSubNode -> next; 
                                    progRefNode = false; 
                                 }
                              }
                           }
                           if (tmpSubNode -> next == NULL)
                              break;
                           if (progRefNode)
                              refNode = tmpSubNode;
                           tmpSubNode = tmpSubNode -> next;
                        }
                     }
                     if (tmpNode -> next == NULL)
                       break;
                     tmpNode = tmpNode -> next;
                  }
               }
               if (debug) printf("cont 1\n");
               if (node -> sub != NULL)
               if (node -> sub -> next != NULL)
                  if (structuralCompositionPhase3(loop, node -> sub -> next, targetTree, nonEmptyBuilds, newModulesNode, newClustersNode, clCntPtr, moCntPtr))
                     redo = true;
            }
         } 
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
   if (debug) printf("cont 3\n");
   return modified | redo;
}
/////////////////////////////////////////////////////////////////////////////////
/// Elaboration of a given cluster
/////////////////////////////////////////////////////////////////////////////////
void clusterElaboration (unsigned loop, 
                         unsigned *clCntPtr, 
                         unsigned *moCntPtr) {
   bool debug = false;
   //propagateClusterItems();
   ///////////////////////////////////////////
   // Step 1
   ///////////////////////////////////////////
   for (int i = 1; i <= 1; i++) {
      NODE* newModulesNode = initNode(0);
      bool redo = clusterElaborationPhase1(loop, dbModuleNode, newModulesNode, clCntPtr, moCntPtr);


      if (debug) printf("loop: %d new modules:\n", loop);
      if (debug) printSITree(newModulesNode);
      
      if (debug) printf("loop: %d all modules:\n", loop);
      if (debug) printSITree(dbModuleNode);

      if (debug) printf("step: 1 loop: %d clCnt: %d moCnt: %d redo: %d\n", i, *clCntPtr, *moCntPtr, redo);
      if (!(redo))
         break;
   }
   ///////////////////////////////////////////
   // Step 2
   ///////////////////////////////////////////
   while (1) {
      NODE* targetTree = initNode(0);
      NODE* newClustersNode = initNode(0);
      bool redo = clusterElaborationPhase2(loop, dbModuleNode, targetTree, newClustersNode, clCntPtr);

      if (debug) printf("loop: %d new cluster:\n", loop);
      if (debug) printSITree(newClustersNode);

      if (newClustersNode -> sub != NULL)
         mergeSITrees(newClustersNode -> sub, dbClusterNode -> sub);
      
      if (debug) printf("loop: %d all clusters:\n", loop);
      if (debug) printSITree(dbClusterNode);

      if (debug) printf("loop: %d all modules:\n", loop);
      if (debug) printSITree(dbModuleNode);

      if (debug) printf("step: 2 loop: %d clCnt: %d moCnt: %d redo: %d\n", loop, *clCntPtr, *moCntPtr, redo);
      if (!(redo))
         break;
   }
   ///////////////////////////////////////////
   // Step 3
   /////////////////////////////////////////// 
   while (1) {
      NODE* targetTree = initNode(0);
      NODE* newModulesNode = initNode(0);
      NODE* newClustersNode = initNode(0);
      bool redo = clusterElaborationPhase3(loop, dbClusterNode, targetTree, newModulesNode, newClustersNode, clCntPtr, moCntPtr);

      if (debug) printf("loop: %d new cluster:\n", loop);
      if (debug) printSITree(newClustersNode);

      if (newClustersNode -> sub != NULL)
         mergeSITrees(newClustersNode -> sub, dbClusterNode -> sub);
      
      if (debug) printf("loop: %d all clusters:\n", loop);
      if (debug) printSITree(dbClusterNode);

      if (debug) printf("loop: %d all modules:\n", loop);
      if (debug) printSITree(dbModuleNode);

      if (debug) printf("step: 3 loop: %d clCnt: %d moCnt: %d redo: %d\n", loop, *clCntPtr, *moCntPtr, redo);
      if (!(redo))
         break;
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Structural composition
/////////////////////////////////////////////////////////////////////////////////
void structuralComposition (unsigned loop, 
                            unsigned *clCntPtr, 
                            unsigned *moCntPtr) {
   bool debug = false;
   ///////////////////////////////////////////
   // Step 4
   ///////////////////////////////////////////
   //for (int i = 1; i <= 7; i++) {
   while (1) {
      NODE* targetTree = initNode(0);
      NODE* nonEmptyBuilds = initNode(0);
      structuralCompositionPhase1(loop, dbModuleNode, targetTree, nonEmptyBuilds);  

      if (debug) {
         printf("nonEmptyBuilds:\n");
         if (nonEmptyBuilds -> sub != NULL)
            printSITree(nonEmptyBuilds);
      }
      
      if (debug) printf("step: 4a loop: %d targetTree:\n", loop);
      if (debug) printSITree(targetTree); 

      NODE* newModulesNode = initNode(0);
      NODE* newClustersNode = initNode(0);
      bool redo = structuralCompositionPhase2(loop, dbModuleNode, targetTree, nonEmptyBuilds, newModulesNode, newClustersNode, clCntPtr, moCntPtr);

      redo |= structuralCompositionPhase3(loop, dbModuleNode, targetTree, nonEmptyBuilds, newModulesNode, newClustersNode, clCntPtr, moCntPtr);

      if (debug) printf("loop: %d new cluster:\n", loop);
      if (debug) printSITree(newClustersNode);

      if (newClustersNode -> sub != NULL)
         mergeSITrees(newClustersNode -> sub, dbClusterNode -> sub);
      
      if (debug) printf("loop: %d all clusters:\n", loop);
      if (debug) printSITree(dbClusterNode);

      if (debug) printf("loop: %d new modules:\n", loop);
      if (debug) printSITree(newModulesNode);

      if (newModulesNode -> sub != NULL) {
         if (debug) printf("-----------------\nthismerge: \n");
         if (debug) printTree(newModulesNode);
         if (debug) printf("-----------------\npremerge: \n");
         if (debug) printTree(dbModuleNode);
         mergeSITreesSubList(newModulesNode -> sub, dbModuleNode -> sub);
         if (debug) printf("-----------------\npostmerge: \n");
         if (debug) printTree(dbModuleNode);
         if (debug) printf("-----------------done\n");
      }         

      if (debug) printf("loop: %d all modules:\n", loop);
      if (debug) printSITree(dbModuleNode);

      if (debug) printf("step: 4b loop: %d clCnt: %d moCnt: %d redo: %d\n", loop, *clCntPtr, *moCntPtr, redo);
      if (!(redo))
         break;
   }
}  
/////////////////////////////////////////////////////////////////////////////////
/// Convert PDVL condition to Verilog process 
/////////////////////////////////////////////////////////////////////////////////
NODE* convertCond2Process (NODE* node, 
                           bool defaultFound, 
                           bool highActive, 
                           string &condName) {
   bool debug = false;
   if (debug) printf("calling convertCond2Process: %d\n", node -> id);
   if ( (node -> id == G_PDVL_COND_DECLARATION_LEVEL_BODY) |
        (node -> id == G_PDVL_COND_DECLARATION_BODY_PORT) |
        (node -> id == G_PDVL_COND_DECLARATION_BODY) |
        (node -> id == G_PDVL_COND_DECLARATION_SIMPLE) ) {
      NODE* subNode = initNode(0);
      NODE* portNode = getNodeSubLevel(node, G_PDVL_TF_PORT_LIST_BRACKETS);
      if (portNode == NULL) {
         string procedureString;
         procedureString.append("always_comb begin ");
         if (!(defaultFound)) {
            procedureString.append(condName);
            if (highActive)
               procedureString.append(" = 1'b0; ");
            else
               procedureString.append(" = 1'b1; ");
         }
         procedureString.append("end "); 
         if (debug) printf("%s\n", procedureString.c_str());
         maxPtr = 0;
         parser_sv_always_construct(procedureString, 0, subNode);
         if (debug) printf("%s\n", procedureString.c_str());
         if (debug) printTree(5, subNode);
         if (node -> sub != NULL)
         if (node -> sub -> next != NULL) {
            if (node -> sub -> next -> id == G_PDVL_COND_CONDITIONAL_STATEMENT) {
               NODE* seqBlockNode = getNode(subNode, G_SV_SEQ_BLOCK);
               seqBlockNode -> sub -> next = convertCond2Process(node -> sub -> next, defaultFound, highActive, condName);
            } else
            if (node -> sub -> next -> next != NULL)
            if (node -> sub -> next -> next -> next != NULL) {
               NODE* seqBlockNode = getNode(subNode, G_SV_SEQ_BLOCK);
               seqBlockNode -> sub -> next = convertCond2Process(node -> sub -> next -> next -> next, defaultFound, highActive, condName);
            }
         }
      } else {
         if (debug) printf("------------------ node:\n");
         if (debug) printTree(5, node);
         if (debug) printf("------------------ portNode:\n");
         if (debug) printTree(5, portNode);
         string functionString;
         functionString.append("function bit ");
         functionString.append(condName); 
         functionString.append("; ");
         NODE* tfPortItemNode = getNode(portNode -> sub, G_SV_FUNCTION_PORT_LIST);
         while (1) {
            functionString.append("input ");
            if (tfPortItemNode -> id == G_SV_FUNCTION_PORT_ITEM)
               writer_sv_function_port_item(functionString, tfPortItemNode -> sub); 
            else
               writer_sv_function_port_item(functionString, getNode(tfPortItemNode -> sub, G_SV_FUNCTION_PORT_ITEM) -> sub); 
            functionString.append("; ");
            if (tfPortItemNode -> next == NULL)
               break;
            tfPortItemNode = tfPortItemNode -> next; 
         }
         functionString.append("begin ");
         if (!(defaultFound)) {
            functionString.append(condName);
            if (highActive)
               functionString.append(" = 1'b0; ");
            else
               functionString.append(" = 1'b1; ");
         }
         functionString.append("end endfunction"); 
         if (debug) printf("%s\n", functionString.c_str());
         maxPtr = 0;
         parser_sv_function_declaration(functionString, 0, subNode);
         if (debug) printf("------------------ subNode: %d\n", maxPtr);
         if (debug) printTree(subNode);
         if (portNode -> next != NULL) {
            NODE* seqBlockNode = getNode(subNode, G_SV_SEQ_BLOCK);
            seqBlockNode -> sub -> next = convertCond2Process(portNode -> next, defaultFound, highActive, condName);
         }
      }
      return subNode;
   } else
   if (node -> id == G_PDVL_COND_CONDITIONAL_STATEMENT) {
      NODE* expressionNode = getNode(node -> sub, G_SV_EXPRESSION);
      if (expressionNode != NULL) {
         if (node -> sub != NULL)
         if (node -> sub -> next != NULL) {
            NODE* statementNode = convertCond2Process(node -> sub -> next, defaultFound, highActive, condName);
            if (debug) printTree(statementNode);
            if (statementNode != NULL) {
               string tmpString = "";
               tmpString.append("if ("); 
               writer_sv_expression(tmpString, expressionNode -> sub);        
               tmpString.append(" ) begin "); 
               writer_sv_statement_or_null(tmpString, statementNode -> sub);
               tmpString.append(" end "); 
               if (debug) printf("tmpString: %s\n", tmpString.c_str());
               NODE* subNode = initNode(0);
               maxPtr = 0;
               parser_sv_statement_or_null(tmpString, 0, subNode);
               return subNode;
            }
         }
      }
   } else
   if (node -> id == G_PDVL_IMPLICIT_COND_HANDLE) {
      string tmpString = "";
      tmpString.append(condName);
      if (highActive)
         tmpString.append(" = 1'b1; ");
      else
         tmpString.append(" = 1'b0; ");
      NODE* subNode = initNode(0);
      maxPtr = 0;
      parser_sv_statement_or_null(tmpString, 0, subNode);
      return subNode;  
   }
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
/// Add attribute tree
/////////////////////////////////////////////////////////////////////////////////
void addAttTree (NODE* attributeNode, 
                 bool driverTrue, 
                 string signalName, 
                 NODE* sourceNode, 
                 NODE* ilrAttributeTree) {
   bool debug = false; 
   if (debug) printTree(attributeNode -> sub);
   NODE* listNode = attributeNode -> sub;
   while (1) {
      NODE* thisNode = getNode(listNode, G_SI);
      NODE* subNode = initNode(DB_LHS);
      if (driverTrue)
         subNode -> id = DB_RHS;
      else if (thisNode -> next != NULL) { 
         string driverString = getSI(thisNode -> next);
         transform(driverString.begin(), driverString.end(), driverString.begin(), ::tolower);
         if (driverString.compare("driver") == 0)
            subNode -> id = DB_RHS;
      }
      subNode -> sub = sourceNode;

      if (debug) printf("checking\n");
      NODE* tmpNode = NULL;
      if (ilrAttributeTree -> sub != NULL) {
         if (debug) printTree(3, thisNode -> sub);
         if (debug) printf("--------\n");
         if (debug) printTree(3, ilrAttributeTree -> sub);
         tmpNode = getSITreeNode(thisNode -> sub, ilrAttributeTree -> sub);
      }
      if (tmpNode != NULL) {
         if (debug) printf("found\n");
         if (debug) printTree(5, tmpNode);
         subNode -> next = tmpNode -> next;
         tmpNode -> next = subNode;
      } else
         addSITree(thisNode, subNode, ilrAttributeTree);
      if (listNode -> next == NULL)
         break;
      listNode = listNode -> next;
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Connect by attribute
/////////////////////////////////////////////////////////////////////////////////
void connectByAttribute (NODE* node, 
                         string &header) {
   bool debug = false;
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      thisHeader.append(node2String(node));
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0) {
            connectByAttribute(node -> sub, thisHeader);
         } else {
            if (debug) printf("id: %d\n", node -> sub -> id);
            if (debug) printTree(node);
            NODE* tmpNode = node -> sub;
            if (tmpNode -> sub != NULL) {
               tmpNode = tmpNode -> sub;
               NODE* rhsNode = NULL;
               while (1) {
                  if (tmpNode -> id == DB_RHS) {
                     if (debug) printf("--------------------- DB_RHS:\n");
                     if (debug) printTree(tmpNode);
                     if (rhsNode != NULL) {
                        printf("ERR.CONNECT.MULTIPLE_DRIVERS: %s\n", thisHeader.c_str());
                        exit(-1);
                     }
                     rhsNode = tmpNode;
                  }
                  if (tmpNode -> next == NULL)
                     break;
                  tmpNode = tmpNode -> next;
               }
               if (rhsNode != NULL) {
                  tmpNode = node -> sub -> sub;
                  while (1) {
                     if (tmpNode -> id == DB_LHS) {
                        NODE* lhsNode = tmpNode;
                        if (checkTree(rhsNode -> sub -> sub, lhsNode -> sub -> sub)) { // in case of condition
                        } else {
                           string rhsString; 
                           rhsString = getSI(rhsNode -> sub);
                           string procedureString;
                           procedureString = "always_comb begin ";
                           procedureString.append(getSI(lhsNode -> sub));
                           procedureString.append(" = ");
                           procedureString.append(rhsString);
                           procedureString.append (" ; end ");
                           maxPtr = 0;
                           NODE* subNode = initNode(0);
                           parser_sv_always_construct(procedureString, 0, subNode);
                           if (debug) printf("%s\n", procedureString.c_str());
                           if (debug) printTree(5, subNode);  
                           NODE* coneNode = getConstructListFirstNode(lhsNode -> sub, DB_CONE);
                           if (debug) printTree(coneNode);
                           coneNode -> sub = subNode;
                           if (debug) printTree(5, lhsNode);  
                        }
                     }
                     if (tmpNode -> next == NULL)
                        break;
                     tmpNode = tmpNode -> next;
                  }
               }
            }
            if (node -> sub -> next != NULL)
               connectByAttribute(node -> sub -> next, thisHeader);
         } 
      }
      if (debug) printf("cont 2\n");
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
}
/////////////////////////////////////////////////////////////////////////////////
/// post-process logic joining
/////////////////////////////////////////////////////////////////////////////////
void logicJoiningPostProcess (NODE* modNode, 
                              NODE* transactionTree, 
                              NODE* eventTree, 
                              NODE* condTree, 
                              NODE* datapathTree, 
                              NODE* hierRootNode) {
   bool debug = false;
   if (debug) printf("logicJoiningPostProcess: %d\n", modNode -> id);
   if (modNode -> sub == NULL)
      return;
   NODE* dbEntryNode = modNode -> sub;
   if (debug) printTree(dbEntryNode);
   NODE* dbModuleTransactionsNode = NULL;
   NODE* mergedTransactionsTree = initNode(0);
   NODE* fsmBag = initNode(0);
   if (transactionTree -> sub != NULL) {
      while (true) {
         if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
         if (dbEntryNode -> id == DB_MODULE_TRANSACTIONS) {
            dbModuleTransactionsNode = dbEntryNode;
            NODE* clNode = dbEntryNode -> sub;
            ///////////////////////////////////
            // handle propagate statement
            ///////////////////////////////////
            if (debug) printf("Handle propagate statement.\n");
            if (debug) printTree(clNode);
            handlePropagateStatement(clNode, 0);
            ///////////////////////////////////
            // merge Transactions
            ///////////////////////////////////
            if (debug) printf("Merging transactions.\n");
            if (debug) printSITree(transactionTree);
            if (debug) printTree(clNode);
            bool foundTransaction = mergeTransaction(clNode, transactionTree, mergedTransactionsTree, modNode);
            if (debug) printf("Merged transactions:\n");
            if (debug) printSITree(mergedTransactionsTree);
            if (debug) printTree(clNode);
            ///////////////////////////////////
            // handle FSM Transactions
            ///////////////////////////////////
            while (1) {
               NODE* tmpNode = clNode -> sub;
               while (1) {
                  if (tmpNode -> sub != NULL) {
                     string transName = getSI(tmpNode);
                     if (debug) printf("Check transaction for FSM processing: %s\n", transName.c_str());  
                     NODE* transNameNode = getNode(tmpNode, G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME);
                     if (debug) printTree(transNameNode);
                     bool foundMerged = false;
                     if (mergedTransactionsTree -> sub != NULL)
                     if (checkSITree(transNameNode -> sub, mergedTransactionsTree -> sub)) {
                        foundMerged = true;
                     }
                     if (debug) printTree(tmpNode -> sub);                               
                     if (debug) printf("-------------------------- otto\n"); 
                     if (debug) printTree(tmpNode);
                     if (!(foundMerged)) {
                        string transName = getSI(transNameNode);
                        if (debug) printf("calling collectTransactionState for transaction %s\n", transName.c_str());
                        if (debug) printTree(tmpNode);
                        bool aboveEdge = true;
                        collectTransactionState(tmpNode -> sub, fsmBag, modNode, &aboveEdge, eventTree);
                        if (debug) printf("calling collectTransactionState for transaction %s done\n", transName.c_str());
                     }
                  }
                  if (tmpNode -> next == NULL)
                    break;
                  tmpNode = tmpNode -> next;
               }
               if (clNode -> next == NULL)
                 break;
               clNode = clNode -> next;
            }
         }
         if (dbEntryNode -> next == NULL)
            break;
         dbEntryNode = dbEntryNode -> next;
      }
      if (debug) printf("------------------------ logicJoiningPostProcess fsmBag mid\n");
      if (debug) printTree(fsmBag);
      dbEntryNode = modNode -> sub;
      while (true) {
         if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
         if (dbEntryNode -> id == DB_MODULE_TRANSACTIONS) {
            dbModuleTransactionsNode = dbEntryNode;
            NODE* clNode = dbEntryNode -> sub;
            ///////////////////////////////////
            // handle FSM Transactions
            ///////////////////////////////////
            while (1) {
               NODE* tmpNode = clNode -> sub;
               while (1) {
                  if (tmpNode -> sub != NULL) {
                     string transName = getSI(tmpNode);
                     if (debug) printf("Check transaction for FSM processing: %s\n", transName.c_str());  
                     NODE* transNameNode = getNode(tmpNode, G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME);
                     if (debug) printTree(transNameNode);
                     bool foundMerged = false;
                     if (mergedTransactionsTree -> sub != NULL)
                     if (checkSITree(transNameNode -> sub, mergedTransactionsTree -> sub)) {
                        foundMerged = true;
                     }
                     if (debug) printTree(tmpNode -> sub);                               
                     if (debug) printf("--------------------------\n"); 
                     if (!(foundMerged)) {
                        string transName = getSI(transNameNode);
                        if (debug) printf("calling finiteStateEmitConversion for transaction %s\n", transName.c_str());
                        if (debug) printTree(tmpNode);
                        bool aboveEdge = true;
                        finiteStateEmitConversion(tmpNode -> sub, fsmBag, modNode, &aboveEdge, eventTree);
                     }
                  }
                  if (tmpNode -> next == NULL)
                    break;
                  tmpNode = tmpNode -> next;
               }
               if (clNode -> next == NULL)
                 break;
               clNode = clNode -> next;
            }
            if (debug) printf("-------------------------- FSMs\n");
            if (debug) printTree(fsmBag);
            if (debug) printf("-------------------------- FSMs\n");
            if (debug) printSITree(fsmBag);
            if (debug) printf("-------------------------- convert\n");
            string tmpHeader = "";
            unsigned cnt = finiteTreeToParameter(0, tmpHeader, fsmBag, modNode);
         }
         if (dbEntryNode -> next == NULL)
            break;
         dbEntryNode = dbEntryNode -> next;
      }
   }
   dbEntryNode = modNode -> sub; 
   NODE* ilrAttributeTree = initNode(0);
   NODE* condAttributeTree = initNode(0);
   if (debug) printTree(dbEntryNode);
   NODE* dbModuleRegistersNode = NULL;
   NODE* dbModuleItemsNode = NULL;
   NODE* dbModuleLatchesNode = NULL;
   NODE* dbModuleEventsNode = NULL;
   NODE* dbModuleConditionsNode = NULL;
   NODE* dbModuleDatapathsNode = NULL;
   if (1) {
      while (true) {
         if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
         if (dbEntryNode -> id == DB_MODULE_REGISTERS)
            dbModuleRegistersNode = dbEntryNode;
         if (dbEntryNode -> id == DB_MODULE_LATCHES)
            dbModuleLatchesNode = dbEntryNode;
         if (dbEntryNode -> id == DB_MODULE_ITEMS)
            dbModuleItemsNode = dbEntryNode;
         if (dbEntryNode -> id == DB_MODULE_EVENTS)
            dbModuleEventsNode = dbEntryNode;
         if (dbEntryNode -> id == DB_MODULE_CONDITIONS)
            dbModuleConditionsNode = dbEntryNode;
         if (dbEntryNode -> id == DB_MODULE_DATAPATHS)
            dbModuleDatapathsNode = dbEntryNode;
         if (dbEntryNode -> next == NULL)
            break;
         dbEntryNode = dbEntryNode -> next;
      } 
      ///////////////////////////////////
      // convert item assignments to processes
      ///////////////////////////////////
      if (dbModuleItemsNode != NULL)
      if (dbModuleItemsNode -> sub != NULL) {
         NODE* tmpClItemNode = dbModuleItemsNode -> sub;
         while (1) {
            if (debug) printf("\tRegister cluster: %d\n", tmpClItemNode -> id);
            if (tmpClItemNode -> sub != NULL) {
               NODE* tmpItemNode = tmpClItemNode -> sub;
               if (debug) printf("\t\tRegister id: %d\n", tmpItemNode -> id);
               while (1) {
                  if (tmpItemNode -> sub != NULL) {
                     NODE* attributeNode = getNodeSubLevel(tmpItemNode -> sub, G_SV_ATTRIBUTE_INSTANCE);
                     string itemName = getSI(tmpItemNode);
                     if (debug) printf("--------------------------\n"); 
                     if (debug) printf("Joining to item procedure: %s\n", itemName.c_str());  
                     NODE* assignNode = getNodeSubLevel(tmpItemNode -> sub, G_SV_BLOCKING_ASSIGN_EXPRESSION);
                     if (assignNode != NULL) {
                        if (debug) printTree(tmpItemNode);
                        string procedureString;
                        procedureString = "always_comb begin ";
                        procedureString.append(getSI(tmpItemNode -> sub));
                        writer_sv_blocking_assign_expression(procedureString, assignNode -> sub);  
                        procedureString.append (" ; end ");
                        maxPtr = 0;
                        NODE* subNode = initNode(0);
                        parser_sv_always_construct(procedureString, 0, subNode);
                        if (debug) printf("%s\n", procedureString.c_str());
                        if (debug) printTree(5, subNode);  
                        if (reportLevel > 3) {
                           printf("2.7.1 Joining to item procedure: %s\n", itemName.c_str());  
                        }
                        NODE* coneNode = getConstructListFirstNode(tmpItemNode -> sub, DB_CONE);
                        if (debug) printTree(coneNode);
                        if (coneNode -> sub != NULL) {
                           NODE* tmpProcNode = initNode(DB_LIST_ENTRY);
                           while (coneNode -> next != NULL)
                              coneNode = coneNode -> next;
                           coneNode -> next = tmpProcNode;
                           tmpProcNode -> sub = subNode;
                           coneNode = tmpProcNode;
                        } else
                           coneNode -> sub = subNode;
                        if (debug) printTree(5, tmpItemNode -> sub);  
                        if (attributeNode != NULL) {
                           addAttTree(attributeNode, true, itemName, tmpItemNode -> sub, ilrAttributeTree);
                        }
                     } else
                     if (attributeNode != NULL)
                        addAttTree(attributeNode, false, itemName, tmpItemNode -> sub, ilrAttributeTree);
                  }
                  if (tmpItemNode -> next == NULL)
                     break;
                  tmpItemNode = tmpItemNode -> next;
               }
            }
            if (tmpClItemNode -> next == NULL)
               break;
            tmpClItemNode = tmpClItemNode -> next;
         }
      }
      ///////////////////////////////////
      // convert condition to processes
      /////////////////////////////////// 
      if (debug) printf("convert condition to processes\n");
      NODE* condDBConeRootNode = initNode(0);
      if (dbModuleConditionsNode != NULL)
      if (dbModuleConditionsNode -> sub != NULL) {
         NODE* tmpClItemNode = dbModuleConditionsNode -> sub;
         while (1) {
            if (debug) printf("\tRegister cluster: %d\n", tmpClItemNode -> id);
            if (tmpClItemNode -> sub != NULL) {
               NODE* tmpItemNode = tmpClItemNode -> sub;
               if (debug) printf("\t\tRegister id: %d\n", tmpItemNode -> id);
               while (1) {
                  if (tmpItemNode -> sub != NULL) {
                     NODE* attributeNode = getNodeSubLevel(tmpItemNode -> sub, G_SV_ATTRIBUTE_INSTANCE);
                     if (attributeNode != NULL) {
                        tmpItemNode -> sub -> sub = tmpItemNode -> sub -> sub -> next;
                     }
                     string condName = getSI(tmpItemNode);
                     NODE* condSignalNameNode = getNodeSubLevel(tmpItemNode -> sub, G_PDVL_COND_SIGNAL_NAME);
                     bool levelAndSignalNameDefined = false;
                     bool highActive = true;
                     if (condSignalNameNode == NULL) {
                        if (reportLevel > 3)
                           printf("2.7.1 Joining to condition procedure: %s\n", condName.c_str());  
                     } else {
                        levelAndSignalNameDefined = true;
                        if (reportLevel > 3)
                           printf("2.7.1 Joining to condition procedure: %s (", condName.c_str());  
                        condName = getSI(condSignalNameNode);
                        if (reportLevel > 3)
                           printf("%s)\n", condName.c_str());  
                        NODE* condLowLevelNode = getNode(tmpItemNode -> sub -> sub -> next, G_PDVL_LOW_LEVEL_IDENTIFIER);
                        if (condLowLevelNode != NULL) {
                           highActive = false;
                           if (debug) printTree(tmpItemNode);
                        }
                     }
                     if (debug) printTree(tmpItemNode -> sub);
                     NODE* coneNode = NULL;
                     bool found = false;
                     if (condDBConeRootNode -> sub != NULL) {
                        NODE* condNameNode = getNode(tmpItemNode -> sub, G_SI);   
                        if (condNameNode == NULL)
                           condNameNode = getNode(tmpItemNode -> sub, G_PDVL_COND_IDENTIFIER_BY_NAME);   
                        NODE* testConeNode = getSITreeNode(condNameNode -> sub, condDBConeRootNode -> sub);
                        if (testConeNode != NULL) {
                           if (debug) printf("Found entry\n");
                           coneNode = testConeNode;
                           found = true;
                           if (debug) printTree(testConeNode);
                        }
                     }
                     if (debug) printTree(tmpItemNode -> sub);                               
                     NODE* subNode = convertCond2Process(tmpItemNode -> sub, found, highActive, condName);
                     if (subNode != NULL) {
                        if (coneNode == NULL)
                           coneNode = getConstructListFirstNode(tmpItemNode -> sub, DB_CONE);
                        if (debug) printTree(coneNode);
                        if (coneNode -> sub != NULL) {
                           NODE* debugNode = coneNode;
                           NODE* tmpProcNode = initNode(DB_LIST_ENTRY);
                           while (coneNode -> next != NULL)
                              coneNode = coneNode -> next;
                           coneNode -> next = tmpProcNode;
                           tmpProcNode -> sub = subNode;
                           coneNode = tmpProcNode;
                           if (debug) printTree(debugNode);
                        } else {
                           coneNode -> sub = subNode;
                           addSITree(tmpItemNode -> sub, coneNode, condDBConeRootNode);
                           if (debug) printSITree(condDBConeRootNode);
                        }
                     }
                     if (attributeNode != NULL)
                        addAttTree(attributeNode, false, condName, tmpItemNode -> sub, condAttributeTree);
                  }
                  if (tmpItemNode -> next == NULL)
                     break;
                  tmpItemNode = tmpItemNode -> next;
               }
            }
            if (tmpClItemNode -> next == NULL)
               break;
            tmpClItemNode = tmpClItemNode -> next;
         }
      }
   }
   ///////////////////////////////////
   // convert transactions to processes
   ///////////////////////////////////
   if (debug) printf("convert transactions to processes\n");
   NODE* registerTree = initNode(0);
   dbEntryNode = modNode -> sub;
   if (dbModuleTransactionsNode != NULL) {
      NODE* clNode = dbModuleTransactionsNode -> sub;
      while (1) {
         NODE* tmpNode = clNode -> sub;
         if (debug) printTree(tmpNode);
         while (1) {
            if (tmpNode -> sub != NULL) {
               NODE* transNameNode = getNode(tmpNode, G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME);
               bool foundMerged = false;
               if (mergedTransactionsTree -> sub != NULL)
               if (checkSITree(transNameNode -> sub, mergedTransactionsTree -> sub)) {
                  foundMerged = true;
               }
               if (!(foundMerged)) {
                  string transName = getSI(tmpNode);
                  if (debug) printf("Converting transaction to register\\latch process: %s\n", transName.c_str());
                  ///////////////////////////////////////////
                  // Registers
                  ///////////////////////////////////////////
                  if (dbModuleRegistersNode != NULL)
                  if (dbModuleRegistersNode -> sub != NULL) {
                     if (debug) printTree(5, dbModuleRegistersNode);
                     NODE* tmpClRegNode = dbModuleRegistersNode -> sub;
                     while (1) {
                        if (debug) printf("\tRegister cluster: %d\n", tmpClRegNode -> id);
                        if (tmpClRegNode -> sub != NULL) {
                           NODE* tmpRegNode = tmpClRegNode -> sub;
                           if (debug) printf("\t\tRegister id: %d\n", tmpRegNode -> id);
                           while (1) {
                              if (tmpRegNode -> sub != NULL) {
                                 NODE* attributeNode = getNodeSubLevel(tmpRegNode -> sub, G_SV_ATTRIBUTE_INSTANCE);
                                 if (attributeNode != NULL) {
                                    tmpRegNode -> sub -> sub -> next = NULL;
                                    if (debug) printf("--------------------------\n"); 
                                    if (debug) printTree(tmpRegNode);
                                    if (debug) printf("--------------------------\n"); 
                                    if (debug) printTree(attributeNode);
                                 }
                                 if (debug) printf("--------------------------\n"); 
                                 if (debug) printTree(tmpRegNode);
                                 if (debug) printTree(tmpNode);
                                 string regName = getSI(tmpRegNode);
                                 if (debug) printf("Joining transaction %s to register procedure: %s\n", transName.c_str(), regName.c_str());
                                 string sensList = "";
                                 if (debug) printTree(tmpNode -> sub); 
                                 bool aboveEdge = true;
                                 unsigned piped = 0;
                                 NODE* typeNode = NULL;
                                 NODE* subNode = convertTrans2Process(tmpNode -> sub, 
                                                                      sensList, regName, 
                                                                      true, true, false, false, 
                                                                      &aboveEdge, 
                                                                      &piped, 0,
                                                                      eventTree, condTree, datapathTree, NULL, modNode, hierRootNode);
                                 if (debug) printTree(0, 4, subNode);
                                 if (debug) printf("done\n");
                                 if (subNode != NULL) {
                                    if (aboveEdge) {
                                       printf("ERR.CONVERTING.NO_EDGE_FOUND_FOR_REG: %s\n", regName.c_str());
                                       exit(-1);
                                    }
                                    if (reportLevel > 3) {
                                       printf("2.7.1 Joining transaction %s to register procedure: %s\n", transName.c_str(), regName.c_str());
                                    }
                                    if (debug) printTree(subNode);
                                    NODE* coneNode = getConstructListFirstNode(tmpRegNode -> sub, DB_CONE);
                                    if (debug) printTree(coneNode);
                                    // registers only have one entry
                                    coneNode -> sub = subNode;
                                    modifyNode(coneNode, G_SV_BLOCKING_ASSIGNMENT, G_SV_NONBLOCKING_ASSIGNMENT);
                                    modifyNode(coneNode, G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT, G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT);
                                    typeNode = getNodeSubLevel(tmpRegNode, DB_SIGNAL_TYPE);
                                    addSITree(tmpRegNode -> sub, typeNode, registerTree);
                                 }
                                 if (attributeNode != NULL) {
                                    addAttTree(attributeNode, true, regName, tmpRegNode -> sub, ilrAttributeTree);
                                 }
                                 if (piped > 0) {
                                    if (debug) printf("Found piped signal.\n");
                                    if (debug) printTree(0, 4, dbModuleRegistersNode -> sub);
                                    string regDefString = "reg ";
                                    regDefString.append(regName);
                                    regDefString.append("_pipe [");
                                    regDefString.append(to_string(piped));
                                    regDefString.append("];");
                                    NODE* newRegDefNode = initNode(0);                          
                                    maxPtr = 0;
                                    parser_pdvl_reg_declaration(regDefString, 0, newRegDefNode);
                                    if (debug) printf("regDefString: %s\n", regDefString.c_str());
                                    if (debug) printTree(newRegDefNode); 
                                    newRegDefNode -> next = tmpRegNode -> next;
                                    tmpRegNode -> next = newRegDefNode;
                                    tmpRegNode = newRegDefNode;

                                    if (debug) printf("Joining transaction %s to register procedure: %s\n", transName.c_str(), regName.c_str());
                                    sensList = "";
                                    aboveEdge = true;
                                    subNode = convertTrans2Process(tmpNode -> sub, 
                                                                      sensList, regName, 
                                                                      true, true, false, false, 
                                                                      &aboveEdge, 
                                                                      &piped, piped,
                                                                      eventTree, condTree, datapathTree, NULL, modNode, hierRootNode);
                                    if (debug) printTree(0, 4, subNode);
                                    if (subNode != NULL) {
                                       if (reportLevel > 3) {
                                          printf("2.7.1 Joining transaction %s to register procedure: %s\n", transName.c_str(), regName.c_str());
                                       }
                                       if (debug) printTree(subNode);
                                       NODE* coneNode = getConstructListFirstNode(tmpRegNode -> sub, DB_CONE);
                                       if (debug) printTree(coneNode);
                                       // registers only have one entry
                                       coneNode -> sub = subNode;
                                       modifyNode(coneNode, G_SV_BLOCKING_ASSIGNMENT, G_SV_NONBLOCKING_ASSIGNMENT);
                                       modifyNode(coneNode, G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT, G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT);
                                       NODE* newUnpackedTypeNode = getNode(newRegDefNode, G_PDVL_UNPACKED_DIMENSION_LIST);
                                       NODE* newTypeNode = initNode(DB_SIGNAL_TYPE);
                                       if (typeNode != NULL) {
                                          newTypeNode -> sub = copyTree(typeNode -> sub);
                                          NODE* newTypeSubNode = newTypeNode -> sub;
                                          while (1) {
                                             if (newTypeSubNode -> next == NULL)
                                                break;
                                             newTypeSubNode = newTypeSubNode -> next;   
                                          }
                                          newTypeSubNode -> next = newUnpackedTypeNode;
                                          if (debug) printf("--------------------------\n"); 
                                          if (debug) printTree(newTypeNode);
                                       } else {
                                          newTypeNode -> sub = newUnpackedTypeNode;
                                       }
                                       NODE* tmpNode = newRegDefNode -> sub;
                                       newTypeNode -> next = tmpNode -> next;
                                       tmpNode -> next = newTypeNode;
                                       if (debug) printTree(0, 5, newRegDefNode);
                                       addSITree(tmpRegNode -> sub, newTypeNode, registerTree);
                                    }
                                 }
                              }
                              if (tmpRegNode -> next == NULL)
                                break;
                              tmpRegNode = tmpRegNode -> next;
                           }
                        }
                        if (tmpClRegNode -> next == NULL)
                          break;
                        tmpClRegNode = tmpClRegNode -> next;
                     }
                  }
                  ///////////////////////////////////////////
                  // Latches
                  ///////////////////////////////////////////
                  if (dbModuleLatchesNode != NULL)
                  if (dbModuleLatchesNode -> sub != NULL) {
                     NODE* tmpClRegNode = dbModuleLatchesNode -> sub;
                     while (1) {
                        if (debug) printf("\tRegister cluster: %d\n", tmpClRegNode -> id);
                        if (tmpClRegNode -> sub != NULL) {
                           NODE* tmpRegNode = tmpClRegNode -> sub;
                           if (debug) printf("\t\tRegister id: %d\n", tmpRegNode -> id);
                           while (1) {
                              if (tmpRegNode -> sub != NULL) {
                                 NODE* attributeNode = getNodeSubLevel(tmpRegNode -> sub, G_SV_ATTRIBUTE_INSTANCE);
                                 if (attributeNode != NULL) {
                                    tmpRegNode -> sub -> sub -> next = NULL;
                                    if (debug) printf("--------------------------\n"); 
                                    if (debug) printTree(tmpRegNode);
                                    if (debug) printf("--------------------------\n"); 
                                    if (debug) printTree(attributeNode);
                                 }
                                 string regName = getSI(tmpRegNode);
                                 if (debug) printf("Joining transaction %s to latch procedure: %s\n", transName.c_str(), regName.c_str());
                                 string sensList = "";
                                 if (debug) printTree(tmpNode -> sub);
                                 bool aboveEdge = true;
                                 unsigned piped = 0;
                                 NODE* subNode = convertTrans2Process(tmpNode -> sub, sensList, regName, true, false, false, false, &aboveEdge, &piped, 0, eventTree, condTree, datapathTree, NULL, modNode, hierRootNode);
                                 if (subNode != NULL) {
                                    if (!aboveEdge) {
                                       printf("ERR.CONVERTING.EDGE_FOUND_FOR_LATCH: %s\n", regName.c_str());
                                       exit(-1);
                                    }
                                    if (reportLevel > 3) {
                                       printf("2.7.1 Joining transaction %s to latch procedure: %s\n", transName.c_str(), regName.c_str());
                                    }
                                    if (debug) printTree(subNode);
                                    NODE* coneNode = getConstructListFirstNode(tmpRegNode -> sub, DB_CONE);
                                    if (debug) printTree(coneNode);
                                    // registers only have one entry
                                    coneNode -> sub = subNode;
                                    modifyNode(coneNode, G_SV_BLOCKING_ASSIGNMENT, G_SV_NONBLOCKING_ASSIGNMENT);
                                    modifyNode(coneNode, G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT, G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT);
                                    NODE* typeNode = getNodeSubLevel(tmpRegNode, DB_SIGNAL_TYPE);
                                    addSITree(tmpRegNode -> sub, typeNode, registerTree);
                                 }
                                 if (attributeNode != NULL) {
                                    addAttTree(attributeNode, true, regName, tmpRegNode -> sub, ilrAttributeTree);
                                 }
                              }
                              if (tmpRegNode -> next == NULL)
                                break;
                              tmpRegNode = tmpRegNode -> next;
                           }
                        }
                        if (tmpClRegNode -> next == NULL)
                          break;
                        tmpClRegNode = tmpClRegNode -> next;
                     }
                  }
               }
            }
            if (tmpNode -> next == NULL)
               break;
            tmpNode = tmpNode -> next;
         }
         tmpNode = clNode -> sub;
         while (1) {
            if (tmpNode -> sub != NULL) {
               NODE* transNameNode = getNode(tmpNode, G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME);
               bool foundMerged = false;
               if (mergedTransactionsTree -> sub != NULL)
               if (checkSITree(transNameNode -> sub, mergedTransactionsTree -> sub)) {
                  foundMerged = true;
               }
               if (!(foundMerged)) {
                  string transName = getSI(tmpNode);
                  if (debug) printf("Converting transaction to process: %s\n", transName.c_str());
                  if (debug) printTree(6, tmpNode -> sub);
                  ///////////////////////////////////////////
                  // Items
                  ///////////////////////////////////////////
                  if (dbModuleItemsNode != NULL)
                  if (dbModuleItemsNode -> sub != NULL) {
                     NODE* tmpClItemNode = dbModuleItemsNode -> sub;
                     while (1) {
                        if (debug) printf("\tRegister cluster: %d\n", tmpClItemNode -> id);
                        if (tmpClItemNode -> sub != NULL) {
                           NODE* tmpItemNode = tmpClItemNode -> sub;
                           if (debug) printf("\t\tRegister id: %d\n", tmpItemNode -> id);
                           while (1) {
                              if (tmpItemNode -> sub != NULL) {
                                 string itemName = getSI(tmpItemNode);
                                 //////////////////////////////////////
                                 // check if item already defined as register\latch 
                                 //////////////////////////////////////
                                 if (!(checkTree(itemName, registerTree))) {
                                    if (reportLevel > 3)
                                       printf("2.7.1 Joining transaction %s to item procedure: %s\n", transName.c_str(), itemName.c_str());
                                    if (debug) printf("--------------------------\n"); 
                                    if (debug) printf("-------------------------- tmpNode -> sub\n"); 
                                    if (debug) printTree(10, tmpNode -> sub);
                                    string sensList = "";
                                    bool aboveEdge = true;
                                    unsigned piped = 0;
                                    NODE* subNode = convertTrans2Process(tmpNode -> sub, sensList, itemName, false, false, true, false, &aboveEdge, &piped, 0, eventTree, condTree, datapathTree, NULL, modNode, hierRootNode);
                                    if (debug) printf("cont\n");
                                    if (subNode != NULL) {
                                       if (debug) printf("--------------------------\n"); 
                                       if (debug) printTree(subNode);
                                       if (reportLevel > 3) {
                                          printf("2.7.1 Joining transaction %s to item procedure: %s\n", transName.c_str(), itemName.c_str());  
                                       }
                                       NODE* coneNode = getConstructListFirstNode(tmpItemNode -> sub, DB_CONE);
                                       if (coneNode -> sub != NULL) {
                                          NODE* tmpProcNode = initNode(DB_LIST_ENTRY);
                                          while (coneNode -> next != NULL)
                                             coneNode = coneNode -> next;
                                          coneNode -> next = tmpProcNode;
                                          tmpProcNode -> sub = subNode;
                                          coneNode = tmpProcNode;
                                       } else
                                          coneNode -> sub = subNode;
                                       modifyNode(coneNode, G_SV_BLOCKING_ASSIGNMENT, G_SV_NONBLOCKING_ASSIGNMENT);
                                       modifyNode(coneNode, G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT, G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT);
                                       if (debug) printf("--------------------------\n"); 
                                       if (debug) printTree(coneNode);
                                    }
                                 } else {
                                 //////////////////////////////////////
                                 // item already defined as register\latch 
                                 // check for inline assignment and same type
                                 //////////////////////////////////////
                                    NODE* coneNode = getNodeSubLevel(tmpItemNode, DB_CONE);
                                    if (coneNode != NULL)  {
                                       printf("ERR.JOINING.OVERWRITING_ITEM.DEFAULT_ASSIGNMENT_NOT_ALLOWED.\n");
                                       exit(-1);
                                    }
                                    NODE* regTypeNode = getSITreeNode(getNode(tmpItemNode -> sub, G_SI) -> sub, registerTree -> sub);
                                    NODE* itemTypeNode = getNodeSubLevel(tmpItemNode, DB_SIGNAL_TYPE);
                                    if (debug) {
                                       printf("-------------------------- registerTree:\n"); 
                                       printTree(registerTree);
                                       printf("-------------------------- tmpItemNode:\n"); 
                                       printTree(tmpItemNode);
                                       printf("-------------------------- regTypeNode:\n"); 
                                       if (regTypeNode != NULL)
                                          printTree(regTypeNode);
                                       printf("-------------------------- itemTypeNode:\n"); 
                                      if (itemTypeNode != NULL)
                                         printTree(itemTypeNode);
                                    }
                                    if (regTypeNode != NULL) {
                                       if (itemTypeNode == NULL) {
                                          printf("ERR.JOINING.OVERWRITING_ITEM.TYPES_NOT_EQUAL.\n");
                                          exit(-1);
                                       } else
                                       if (!(checkTree(regTypeNode -> sub, itemTypeNode -> sub))) {
                                          printf("ERR.JOINING.OVERWRITING_ITEM.TYPES_NOT_EQUAL.\n");
                                          exit(-1);
                                       }
                                    } else {
                                       if (itemTypeNode != NULL) {
                                          printf("ERR.JOINING.OVERWRITING_ITEM.TYPES_NOT_EQUAL.\n");
                                          exit(-1);
                                       }
                                    }
                                 }
                              }
                              if (tmpItemNode -> next == NULL)
                                break;
                              tmpItemNode = tmpItemNode -> next;
                           }
                        }
                        if (tmpClItemNode -> next == NULL)
                          break;
                        tmpClItemNode = tmpClItemNode -> next;
                     }
                  }
                  ///////////////////////////////////////////
                  // Events
                  ///////////////////////////////////////////
                  if (dbModuleEventsNode != NULL)
                  if (dbModuleEventsNode -> sub != NULL) {
                     NODE* tmpClEventsNode = dbModuleEventsNode -> sub;
                     while (1) {
                        if (debug) printf("\tRegister cluster: %d\n", tmpClEventsNode -> id);
                        if (tmpClEventsNode -> sub != NULL) {
                           NODE* tmpEventNode = tmpClEventsNode -> sub;
                           if (debug) printf("\t\tRegister id: %d\n", tmpEventNode -> id);
                           while (1) {
                              if (tmpEventNode -> sub != NULL) {
                                 string eventName = getSI(tmpEventNode);
                                 if (reportLevel > 3)
                                    printf("2.7.1 Joining transaction %s to event procedure: %s\n", transName.c_str(), eventName.c_str());  
                                 if (debug) printTree(tmpNode -> sub);                               
                                 string sensList = "";
                                 bool aboveEdge = true;
                                 unsigned piped = 0;
                                 NODE* subNode = convertTrans2Process(tmpNode -> sub, sensList, eventName, false, false, false, false, &aboveEdge, &piped, 0, eventTree, condTree, datapathTree, NULL, modNode, hierRootNode);
                                 if (subNode != NULL) {
                                    if (debug) printTree(subNode);                               
                                    if (reportLevel > 3) {
                                       printf("2.7.1 Joining transaction %s to event procedure: %s\n", transName.c_str(), eventName.c_str());  
                                    }
                                    if (debug) printf("--------------------------\n"); 
                                    if (debug) printTree(subNode);
                                    NODE* coneNode = getConstructListFirstNode(tmpEventNode -> sub, DB_CONE);
                                    if (coneNode -> sub != NULL) {
                                       NODE* tmpProcNode = initNode(DB_LIST_ENTRY);
                                       while (coneNode -> next != NULL)
                                          coneNode = coneNode -> next;
                                       coneNode -> next = tmpProcNode;
                                       tmpProcNode -> sub = subNode;
                                       coneNode = tmpProcNode;
                                    } else
                                       coneNode -> sub = subNode;
                                    if (debug) printf("--------------------------\n"); 
                                    if (debug) printTree(tmpClEventsNode);
                                 }
                              }
                              if (tmpEventNode -> next == NULL)
                                break;
                              tmpEventNode = tmpEventNode -> next;
                           }
                        }
                        if (tmpClEventsNode -> next == NULL)
                          break;
                        tmpClEventsNode = tmpClEventsNode -> next;
                     }
                  }
                  ///////////////////////////////////////////
                  // Conditions
                  ///////////////////////////////////////////
                  if (dbModuleConditionsNode != NULL)
                  if (dbModuleConditionsNode -> sub != NULL) {
                     NODE* tmpClConditionsNode = dbModuleConditionsNode -> sub;
                     while (1) {
                        if (debug) printf("\tRegister cluster: %d\n", tmpClConditionsNode -> id);
                        if (tmpClConditionsNode -> sub != NULL) {
                           NODE* tmpConditionNode = tmpClConditionsNode -> sub;
                           if (debug) printf("\t\tRegister id: %d\n", tmpConditionNode -> id);
                           while (1) {
                              if (tmpConditionNode -> sub != NULL) {
                                 string condName;
                                 condName = getSI(tmpConditionNode);
                                 if (debug) printf("Joining transaction %s to condition procedure: %s\n", transName.c_str(), condName.c_str());  
                                 string sensList = "";
                                 bool aboveEdge = true;
                                 unsigned piped = 0;
                                 bool trueRegFalseItem = false;
                                 bool trueRegFalseLatch = false;
                                 bool skipPreEdge = true;
                                 if (tmpConditionNode -> sub -> id == G_PDVL_COND_DECLARATION_REG) {
                                    trueRegFalseItem = true;
                                    trueRegFalseLatch = true;
                                    skipPreEdge = false; 
                                 }
                                 NODE* subNode = convertTrans2Process(tmpNode -> sub, sensList, condName, 
                                                     trueRegFalseItem,
                                                     trueRegFalseLatch,
                                                     skipPreEdge,
                                                     true, &aboveEdge, &piped, 0, eventTree, condTree, datapathTree, NULL, modNode, hierRootNode);
                                 if (subNode != NULL) {
                                    if (tmpConditionNode -> sub -> id == G_PDVL_COND_DECLARATION_REG) {
                                       if (debug) printf("-------------------------------\n");
                                       if (debug) printTree(16, subNode);
                                       if (subNode -> sub -> sub -> id != G_SV_ALWAYS_FF_IDENTIFIER) {
                                          printf("ERR.CONVERTING.NO_EDGE_FOUND_FOR_CONDITION_REG: %s\n", condName.c_str());
                                          exit(-1);
                                       }
                                    }
                                    if (reportLevel > 3) {
                                       printf("2.7.1 Joining transaction %s to condition procedure: %s\n", transName.c_str(), condName.c_str());  
                                    }
                                    NODE* coneNode = getConstructListFirstNode(tmpConditionNode -> sub, DB_CONE);
                                    if (coneNode -> sub != NULL) {
                                       NODE* tmpProcNode = initNode(DB_LIST_ENTRY);
                                       while (coneNode -> next != NULL)
                                          coneNode = coneNode -> next;
                                       coneNode -> next = tmpProcNode;
                                       tmpProcNode -> sub = subNode;
                                       coneNode = tmpProcNode;
                                    } else
                                       coneNode -> sub = subNode;
                                 }
                              }
                              if (tmpConditionNode -> next == NULL)
                                break;
                              tmpConditionNode = tmpConditionNode -> next;
                           }
                        }
                        if (tmpClConditionsNode -> next == NULL)
                          break;
                        tmpClConditionsNode = tmpClConditionsNode -> next;
                     }
                  }
               }
            }
            if (tmpNode -> next == NULL)
               break;
            tmpNode = tmpNode -> next;
         }
         if (clNode -> next == NULL)
            break;
         clNode = clNode -> next;
      }
   }
   if (ilrAttributeTree -> sub != NULL) {
      if (debug) printf("ilrAttributeTree (SI):\n");
      if (debug) printSITree(ilrAttributeTree);
      if (debug) printf("ilrAttributeTree:\n");
      if (debug) printTree(10, ilrAttributeTree);
      string tmpHeader = "";   
      connectByAttribute(ilrAttributeTree, tmpHeader);
   }
   if (condAttributeTree -> sub != NULL) {
      if (debug) printf("condAttributeTree (SI):\n");
      if (debug) printSITree(condAttributeTree);
      if (debug) printf("condAttributeTree:\n");
      if (debug) printTree(10, condAttributeTree);
      string tmpHeader = "";   
      connectByAttribute(condAttributeTree, tmpHeader);
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Extract inline macros
/////////////////////////////////////////////////////////////////////////////////
void extractInlineMacro (NODE* node, 
                         string nameString, 
                         NODE* insertNode) {
   bool debug = false; 
   NODE* macroNode = getNodeSubLevel(node, G_PDVL_TRANSACTION_MACRO_LIST);
   if (macroNode != NULL) {
      if (debug) printf("----------------- found macro: %s\n", nameString.c_str());
      if (debug) printTree(node);
      string transString = "tr_";
      transString.append(nameString);
      transString.append(" { ");
      bool first = true; 
      while (1) {
         macroNode = macroNode -> sub -> sub;
         string condString = getSI(macroNode);
         if (debug) printf("found cond: %s\n", condString.c_str());
         string dString = "d_";
         dString.append(nameString);
         dString.append("_");
         dString.append(condString);

         if (!(first)) {
            transString.append("else { ");
         } 
         transString.append(" @");
         transString.append(condString);
         transString.append(" { ");
         transString.append(dString);
         transString.append("; } ");
         if (!(first)) {
            transString.append(" } ");
         } 
         first = false;

         dString.append(" { ");
         macroNode = macroNode -> next;
         if (macroNode -> id == G_SV_EXPRESSION) {
            dString.append(nameString);
            dString.append(" =");
            writer_sv_expression(dString, macroNode -> sub);  
            dString.append(";");
            macroNode = macroNode -> next;
         } else 
         while (1) {
            writer_pdvl_data_declaration_body(dString, macroNode -> sub);  
            macroNode = macroNode -> next;
            if (macroNode == NULL)
               break;
            if (macroNode -> id == G_PDVL_TRANSACTION_MACRO_LIST)
               break;
         }
         dString.append(" }");
         if (debug) printf("datapath: %s\n", dString.c_str());
         NODE* dataNode = initNode(0);
         parser_pdvl_data_declaration(dString, 0, dataNode);
         if (debug) printTree(dataNode);
         NODE* dbEntryNode = initNode(G_PDVL_CLUSTER_DECLARATION_BODY);
         dbEntryNode -> sub = dataNode;
         dbEntryNode -> next = insertNode -> next;
         insertNode -> next = dbEntryNode;
         if (macroNode == NULL)
            break;
         if (macroNode -> id != G_PDVL_TRANSACTION_MACRO_LIST)
            break;
      }
      transString.append("}");
      if (debug) printf("transaction: %s\n", transString.c_str()); 
      NODE* transNode = initNode(0);
      parser_pdvl_transaction_declaration(transString, 0, transNode);
      NODE* dbEntryNode = initNode(G_PDVL_CLUSTER_DECLARATION_BODY);
      dbEntryNode -> sub = transNode;
      dbEntryNode -> next = insertNode -> next;
      insertNode -> next = dbEntryNode;
      if (debug) printTree(transNode);
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Join logic, phase 2
/////////////////////////////////////////////////////////////////////////////////
void logicJoiningLevel2 (NODE* node, 
                         bool trackHier, 
                         string &header, 
                         NODE* modNode, 
                         NODE* transactionTree, 
                         NODE* removeTransactionTree, 
                         NODE* datapathTree) {
   bool debug = false; 
   if (debug) printf("logicJoiningLevel2: %d\n", node -> id);
   NODE* paramTree = initNode(0); 
   NODE* typeTree = initNode(0); 
   NODE* functionTree = initNode(0); 
   NODE* sigTree = initNode(0); 
   NODE* conditionTree = initNode(0); 
   NODE* eventTree = initNode(0);
   NODE* signalTree = initNode(0);
   NODE* theoremTree = initNode(0);
   while (true) {
      string thisHeader = "";
      if (trackHier) {
         thisHeader.append(header);
         thisHeader.append(node2String(node));
      }                              
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            logicJoiningLevel2(node -> sub, trackHier, thisHeader, modNode, transactionTree, removeTransactionTree, datapathTree);
         } else {
            if (debug) printf("------------------- %s check\n", thisHeader.c_str());
            if (node -> sub -> sub != NULL) 
            if (node -> sub -> sub -> sub != NULL) { 
               NODE* clusterIdNode = node -> sub -> sub;
               if (clusterIdNode != NULL) {
                  if (debug) printf("------------------- %s (%d)\n", thisHeader.c_str(), clusterIdNode -> id);
                  if (debug) printTree(clusterIdNode);
                  NODE* dbEntryNode = clusterIdNode -> sub;
                  dbEntryNode = clusterIdNode -> sub;
                  while (true) {
                     if (debug) printf("subNode: %d\n", dbEntryNode -> id);
                     if (dbEntryNode -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
                        if (debug) printTree(dbEntryNode -> sub);
                        NODE* tmpSubNode = dbEntryNode -> sub;                 
                        ///////////////////////////////////
                        // parameter
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_SV_PARAMETER_DECLARATION) {
                           if (debug) printTree(tmpSubNode);
                           NODE* paramNameNode = getNode(tmpSubNode -> sub, G_SV_PARAM_ASSIGNMENT);
                           bool add = true;
                           if (paramTree -> sub != NULL) {
                              NODE* subNode = getSITreeNode(paramNameNode -> sub -> sub, paramTree -> sub);
                              if (subNode != NULL) {
                                 if (!(checkTree(tmpSubNode -> sub, subNode))) {
                                    string paramName = getSI(paramNameNode -> sub);
                                    printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.PARAMETER: %s\n", paramName.c_str());
                                    exit(-1);
                                 } else
                                    add = false;
                              }
                           }
                           if (add) {
                              if (reportLevel > 3) {
                                 string paramName = getSI(paramNameNode -> sub);
                                 printf("2.7.1 Joining parameter: %s\n", paramName.c_str()); 
                              }
                              addSITree(paramNameNode, copyTree(tmpSubNode -> sub), paramTree);
                              joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_PARAMETER);
                           }
                        } else               
                        ///////////////////////////////////
                        // typedefs
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_SV_TYPE_DECLARATION) {
                           if (debug) printf("-------------------------- tmpSubNode:\n");
                           if (debug) printTree(15, tmpSubNode);
                           NODE* typeIdentifierNode = getNode(tmpSubNode -> sub -> next, G_SV_TYPE_IDENTIFIER);
                           bool add = true;
                           if (typeTree -> sub != NULL) {
                              NODE* subNode = getSITreeNode(typeIdentifierNode -> sub -> sub, typeTree -> sub);
                              if (subNode != NULL) {
                                 if (!(checkTree(tmpSubNode -> sub, subNode))) {
                                    string typeName = getSI(typeIdentifierNode);
                                    printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.TYPE: %s\n", typeName.c_str());
                                    exit(-1);
                                 } else
                                    add = false;
                              }
                           }
                           if (add) {
                              if (reportLevel > 3) {
                                 string typeName = getSI(typeIdentifierNode);
                                 printf("2.7.1 Joining type definition: %s\n", typeName.c_str()); 
                              }
                              addSITree(typeIdentifierNode, copyTree(tmpSubNode -> sub), typeTree);
                              joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_TYPES);
                           }
                        } else
                        ///////////////////////////////////
                        // functions
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_SV_FUNCTION_DECLARATION) {
                           NODE* functionIdentifierNode = getNode(tmpSubNode -> sub, G_SV_TF_IDENTIFIER);
                           bool add = true;
                           if (functionTree -> sub != NULL) {
                              NODE* subNode = getSITreeNode(functionIdentifierNode -> sub -> sub, functionTree -> sub);
                              if (subNode != NULL) {
                                 if (!(checkTree(tmpSubNode -> sub, subNode))) {
                                    string functionName = getSI(functionIdentifierNode);
                                    printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.FUNCTION: %s\n", functionName.c_str());
                                    exit(-1);
                                 } else
                                    add = false;
                              }
                           }
                           if (add) {
                              if (reportLevel > 3) {
                                 string functionName = getSI(functionIdentifierNode);
                                 printf("2.7.1 Joining function definition: %s\n", functionName.c_str()); 
                              }
                              addSITree(functionIdentifierNode, copyTree(tmpSubNode -> sub), functionTree);
                              joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_FUNCTIONS);
                           }
                        } else
                        ///////////////////////////////////
                        // Registers, items and latches
                        ///////////////////////////////////
                        if ( (tmpSubNode -> id == G_PDVL_REG_DECLARATION)   |
                             (tmpSubNode -> id == G_PDVL_ITEM_DECLARATION)  |
                             (tmpSubNode -> id == G_PDVL_LATCH_DECLARATION) ) {
                           if (debug) printf("--------------------\n");
                           if (debug) printTree(tmpSubNode);      
                           NODE* identifierTypeNode = getNodeSubLevel(tmpSubNode, G_PDVL_IDENTIFIER_TYPE);
                           ///////////////////////////////////////////
                           // extract and remove identifier list node
                           // convert C-style packed range
                           ///////////////////////////////////////////
                           NODE* identifierListNode = NULL;
                           NODE* ptrNode = identifierTypeNode -> sub -> sub;
                           NODE* lastPtr = ptrNode;
                           while (1) {
                               if (ptrNode -> id == G_PDVL_IDENTIFIER_LIST) {
                                  identifierListNode = ptrNode;
                                  if (lastPtr == ptrNode)
                                     identifierTypeNode -> sub -> sub = ptrNode -> next;
                                  else
                                     lastPtr -> next = ptrNode -> next;
                               } else {
                                  lastPtr = ptrNode;
                                  if (ptrNode -> sub != NULL)
                                  if (ptrNode -> sub -> sub != NULL) 
                                  if (ptrNode -> sub -> sub -> id == G_PDVL_C_STYLE_DIMENSION) {
                                     NODE* subNode = ptrNode -> sub;
                                     if (debug) printTree(tmpSubNode); 
                                     while (1) {
                                        if (subNode -> sub -> id == G_PDVL_C_STYLE_DIMENSION) {
                                           string tmpOut = " [ "; 
                                           writer_sv_constant_expression(tmpOut, subNode -> sub -> sub -> sub);
                                           tmpOut.append(" - 1 : 0 ] ");
                                           if (debug) printf("%s\n", tmpOut.c_str());
                                           NODE* selectDeclarationNode = initNode(0);
                                           parser_sv_packed_dimension(tmpOut, 0, selectDeclarationNode);
                                           if (debug) printTree(selectDeclarationNode); 
                                           deleteTree(subNode -> sub);
                                           subNode -> sub = selectDeclarationNode;
                                           if (debug) printTree(tmpSubNode); 
                                        }
                                        if (subNode -> next ==  NULL)
                                           break;
                                        subNode = subNode -> next -> sub;
                                     }
                                  }
                               }
                               if (ptrNode -> next == NULL)
                                  break;
                               ptrNode = ptrNode -> next;
                           }
                           if (debug) printf("-------------------- identifierTypeNode:\n");
                           if (debug) printTree(identifierTypeNode);      
                           if (debug) printf("-------------------- identifierListNode:\n");
                           if (debug) printTree(identifierListNode);      
                           NODE* nextIdentifierListNode = identifierListNode -> sub -> next;
                           identifierListNode -> sub -> next = NULL;
                           NODE* newNode = initNode(G_PDVL_IDENTIFIER_LIST); 
                           newNode -> sub = identifierListNode;
                           newNode -> sub -> next = tmpSubNode -> sub;
                           tmpSubNode -> sub = newNode;
                           if (identifierTypeNode -> sub -> sub != NULL) {
                              tmpSubNode -> sub -> next = initNode(DB_SIGNAL_TYPE);
                              tmpSubNode -> sub -> next -> sub = identifierTypeNode -> sub -> sub;
                           }
                           while (1) {
                              string registerName = getSI(identifierListNode -> sub);
                              if (tmpSubNode -> id != G_PDVL_ITEM_DECLARATION) {
                                 extractInlineMacro(tmpSubNode -> sub, registerName, dbEntryNode);
                                 if (debug) printf("-------------------- 3\n");
                                 if (debug) printTree(tmpSubNode);
                              }
                              NODE* signalNameNode = getNode(tmpSubNode, G_SI);
                              if (debug) printf("-------------------- 3\n");
                              if (debug) printTree(tmpSubNode);
                              if (debug) printf("-------------------- 3\n");
                              if (debug) printTree(signalNameNode);
                              bool add = true; 
                              if (signalTree -> sub != NULL) {
                                 NODE* subNode = getSITreeNode(signalNameNode -> sub, signalTree -> sub);
                                 if (subNode != NULL) {
                                    if (!(checkTree(tmpSubNode -> sub, subNode))) {
                                       printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.SIGNAL: %s\n", registerName.c_str());
                                       exit(-1);
                                    } 
                                 }
                              }
                              if (add) {
                                 if (reportLevel > 3) {
                                    if (tmpSubNode -> id == G_PDVL_ITEM_DECLARATION)
                                       printf("2.7.1 Joining item: %s\n", registerName.c_str()); 
                                    else if (tmpSubNode -> id == G_PDVL_REG_DECLARATION)
                                       printf("2.7.1 Joining register: %s\n", registerName.c_str()); 
                                    else
                                       printf("2.7.1 Joining latch: %s\n", registerName.c_str()); 
                                 }
                                 addSITree(signalNameNode, copyTree(tmpSubNode -> sub), signalTree);
                                 if (debug) printf("Inserted\n"); 
                                 if (debug) printTree(tmpSubNode);      
                                 if (tmpSubNode -> id == G_PDVL_ITEM_DECLARATION)
                                    joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_ITEMS);
                                 else if (tmpSubNode -> id == G_PDVL_REG_DECLARATION)
                                    joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_REGISTERS);
                                 else
                                    joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_LATCHES);
                              }
                              if (nextIdentifierListNode == NULL)
                                 break;
                              identifierListNode = nextIdentifierListNode;
                              nextIdentifierListNode = identifierListNode -> sub -> next;
                              identifierListNode -> sub -> next = NULL;
                              NODE* newSubNode = copyTreeNoNext(tmpSubNode);
                              tmpSubNode = newSubNode;
                              tmpSubNode -> sub -> sub -> sub = identifierListNode;
                              if (debug) printf("-------------------- 4\n");
                              if (debug) printTree(tmpSubNode);      
                           } 
                        } else                
                        ///////////////////////////////////
                        // event
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_PDVL_EVENT_DECLARATION) {
                           NODE* eventNameNode = getNode(tmpSubNode -> sub, G_PDVL_EVENT_SIGNAL_NAME);
                           bool add = true;
                           if (eventTree -> sub != NULL) {
                              NODE* subNode = getSITreeNode(eventNameNode -> sub -> sub, eventTree -> sub);
                              if (subNode != NULL) {
                                 if (!(checkTree(tmpSubNode -> sub, subNode))) {
                                    string eventName = getSI(eventNameNode -> sub);
                                    printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.EVENT: %s\n", eventName.c_str());
                                    exit(-1);
                                 } else
                                    add = false;
                              }
                           }
                           if (add) {
                              if (reportLevel > 3) {
                                 string eventName = getSI(tmpSubNode -> sub);
                                 printf("2.7.1 Joining event: %s\n", eventName.c_str()); 
                              }
                              addSITree(eventNameNode, copyTree(tmpSubNode -> sub), eventTree);
                              joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_EVENTS);
                           }
                        } else                
                        ///////////////////////////////////
                        // condition
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_PDVL_COND_DECLARATION) {
                           string conditionName;
                           if (tmpSubNode -> sub -> sub -> id == G_SV_ATTRIBUTE_INSTANCE)
                              conditionName = getSI(tmpSubNode -> sub -> sub -> next);
                           else
                              conditionName = getSI(tmpSubNode -> sub);
                           if (debug) printTree(tmpSubNode);
                           if (checkTree(conditionName, conditionTree)) {
                              printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.CONDITION: %s\n", conditionName.c_str());
                              exit(-1);
                           }
                           if (reportLevel > 3) {
                              printf("2.7.1 Joining condition: %s\n", conditionName.c_str()); 
                           }
                           addSITree(tmpSubNode, NULL, conditionTree);
                           joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_CONDITIONS);
                        } else                
                        ///////////////////////////////////
                        // data
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_PDVL_DATA_DECLARATION) { 
                           string dataName = getSI(tmpSubNode -> sub);
                           if (tmpSubNode -> sub -> sub -> id == G_PDVL_TRANSACTION_AND_DATA_IDENTIFIER_BY_NAME)
                           {
                              string transString = dataName;
                              transString.append(" { ");
                              dataName = dataName.substr(3); 
                              transString.append(dataName);
                              transString.append(" ; } ");
                              if (debug) printf("%s\n", transString.c_str());
                              NODE* transNode = initNode(0);
                              parser_pdvl_cluster_declaration_body(transString, 0, transNode);
                              if (debug) printTree(transNode);
                              transNode -> next = dbEntryNode -> next;
                              dbEntryNode -> next = transNode;
                              NODE* newIdentifierNode = initNode(0);
                              parser_pdvl_data_identifier(dataName, 0, newIdentifierNode);
                              tmpSubNode -> sub -> sub = newIdentifierNode -> sub;
                              if (debug) printTree(6, tmpSubNode);
                           }
                           if (debug) printf("------------------------------ %d\n", tmpSubNode -> sub -> sub -> id);
                           if (debug) printTree(tmpSubNode);
                           if (checkTree(dataName, datapathTree)) {
                              printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.DATAPATH: %s\n", dataName.c_str());
                              exit(-1);
                           }
                           if (reportLevel > 3) {
                              printf("2.7.1 Joining datapath: %s\n", dataName.c_str()); 
                           }
                           NODE* tmpCopyNode = initNode(G_PDVL_DATA_DECLARATION);
                           tmpCopyNode -> sub = tmpSubNode -> sub;
                           addSITree(tmpSubNode, tmpCopyNode, datapathTree);
                           if (debug) printf("------------------------------\n");
                           if (debug) printSITree(datapathTree);
                           if (debug) printf("------------------------------\n");
                           if (debug) printTree(4, datapathTree);
                           joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_DATAPATHS);
                           if (debug) printf("done\n");
                        } else                
                        ///////////////////////////////////
                        // transaction
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_PDVL_TRANSACTION_DECLARATION) { 
                           if (debug) printTree(0, 5, tmpSubNode);
                           NODE* transNameNode = getNode(tmpSubNode, G_PDVL_TRANSACTION_IDENTIFIER);
                           if (transNameNode == NULL)
                              exit(-1);
                           if (transNameNode -> sub -> id == G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME)
                              transNameNode = transNameNode -> sub;
                           else
                              transNameNode = transNameNode -> sub -> sub;
                           if (transNameNode == NULL)
                              exit(-1);
                           bool cont = true;
                           if (removeTransactionTree != NULL)
                           if (checkSITree(transNameNode -> sub, removeTransactionTree -> sub)) {
                              string transactionName = getSI(tmpSubNode -> sub);
                              if (reportLevel >= 2)
                                 printf("Removing transaction: %s\n", transactionName.c_str());
                              cont = false;
                           }
                           if (cont) {
                              string transactionName = getSI(tmpSubNode -> sub);
                              if (checkTree(transactionName, transactionTree)) {
                                 printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.TRANSACTION: %s\n", transactionName.c_str());
                                 exit(-1);
                              }
                              if (reportLevel > 3) {
                                 printf("2.7.1 Joining transaction: %s\n", transactionName.c_str());
                              }
                              if (tmpSubNode -> sub -> sub -> next == NULL) {
                                 tmpSubNode -> sub -> sub -> next = initNode(G_SV_NULL_STATEMENT);
                              }
                              addSITree(transNameNode, tmpSubNode -> sub -> sub -> next, transactionTree);
                              joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_TRANSACTIONS);
                           }
                        } else                
                        ///////////////////////////////////
                        // theorem
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_PDVL_THEOREM_DECLARATION) { 
                           if (debug) printTree(0, 5, tmpSubNode);
                           NODE* theoremNameNode = getNode(tmpSubNode, G_PDVL_THEOREM_IDENTIFIER);
                           if (theoremNameNode == NULL)
                              exit(-1);
                           if (theoremNameNode -> sub -> id == G_PDVL_THEOREM_IDENTIFIER_BY_NAME)
                              theoremNameNode = theoremNameNode -> sub;
                           else
                              theoremNameNode = theoremNameNode -> sub -> sub;
                           if (theoremNameNode == NULL)
                              exit(-1);
                           string theoremName = getSI(tmpSubNode -> sub);
                           if (checkTree(theoremName, theoremTree)) {
                              printf("ERR.JOINING.MULTIPLE.DEFINTIIONS.THEOREMS: %s\n", theoremName.c_str());
                              exit(-1);
                           }
                           if (reportLevel > 3) {
                              printf("2.7.1 Joining theorem: %s\n", theoremName.c_str());
                           }
                           if (tmpSubNode -> sub -> sub -> next == NULL) {
                              tmpSubNode -> sub -> sub -> next = initNode(G_SV_NULL_STATEMENT);
                           }
                           addSITree(theoremNameNode, tmpSubNode -> sub -> sub -> next, theoremTree);
                           joinConstruct(modNode, tmpSubNode, clusterIdNode -> id, DB_MODULE_THEOREMS);
                        }
                     }
                     if (dbEntryNode -> next == NULL)
                        break;
                     dbEntryNode = dbEntryNode -> next;
                  }
               }
            }
            if (node -> sub != NULL)
            if (node -> sub -> next != NULL)
               logicJoiningLevel2(node -> sub -> next, trackHier, thisHeader, modNode, transactionTree, removeTransactionTree, datapathTree);
         } 
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Extract PDVL event and PDVL condition, step 2
/////////////////////////////////////////////////////////////////////////////////
void extractEventAndCondTreeStep2 (NODE* node, 
                                   string &header, 
                                   NODE* hierRootNode, 
                                   NODE* eventTree, 
                                   NODE* condTree) {
   bool debug = false; 
   if (debug) printf("extractEventAndCondTreeStep2: %d\n", node -> id);
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      thisHeader.append(node2String(node));
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            extractEventAndCondTreeStep2(node -> sub, thisHeader, hierRootNode, eventTree, condTree);
         } else {
            if (debug) printf("------------------- %s check\n", thisHeader.c_str());
            if (node -> sub -> sub != NULL) 
            if (node -> sub -> sub -> sub != NULL) { 
               NODE* clusterIdNode = node -> sub -> sub;
               if (clusterIdNode != NULL) {
                  if (debug) printf("------------------- %s (%d)\n", thisHeader.c_str(), clusterIdNode -> id);
                  if (debug) printTree(clusterIdNode);
                  NODE* dbEntryNode = clusterIdNode -> sub;
                  while (true) {
                     if (debug) printf("subNode: %d\n", dbEntryNode -> id);
                     if (dbEntryNode -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
                        if (debug) printTree(dbEntryNode -> sub);
                        NODE* tmpSubNode = dbEntryNode -> sub;                 
                        ///////////////////////////////////
                        // event
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_PDVL_EVENT_DECLARATION) {
                           string eventName = getSI(tmpSubNode -> sub);
                           if (debug) 
                           if (reportLevel > 3) {
                              printf("2.7.1 Joining event: %s\n", eventName.c_str()); 
                           }
                           if (debug) printTree(tmpSubNode);      
                           string tmpHeader = "";
                           NODE* subNode = getTree(tmpHeader, eventName, eventTree);
                           NODE* dbEDNode = NULL;
                           if (subNode == NULL) {
                              subNode = initNode(DB_LIST_ENTRY);
                              addSITree(eventName, subNode, eventTree);
                              dbEDNode = initSubNode(subNode, DB_DEFINES);
                           } else {
                              if (debug) printf("eventTree:\n");
                              if (debug) printTree(eventTree);
                              if (debug) printf("subNode:\n");
                              if (debug) printTree(subNode);
                              if (subNode -> sub != NULL)
                              if (subNode -> sub -> id == DB_DEFINES)
                                 dbEDNode = subNode -> sub;
                              if (dbEDNode == NULL)
                              if (subNode -> next != NULL)
                              if (subNode -> next -> sub != NULL)
                              if (subNode -> next -> sub -> id == DB_DEFINES)
                                 dbEDNode = subNode -> sub -> next;
                           } 
                           if (dbEDNode == NULL) {
                              dbEDNode = initNode(DB_DEFINES);
                              dbEDNode -> next = subNode -> sub;
                              subNode -> sub = dbEDNode;
                           }
                            
                           if (dbEDNode -> sub == NULL) {
                              subNode = initSubNode(dbEDNode, DB_LIST_ENTRY);
                              subNode -> sub = copyTree(hierRootNode);
                              subNode -> next = initNode(DB_LIST_ENTRY);
                              subNode = subNode -> next;
                              subNode -> sub = tmpSubNode -> sub;
                           } else {
                              subNode = dbEDNode -> sub;
                              if (debug) printf("subNode:\n");
                              if (debug) printTree(subNode);
                              while (1) {
                                 if (subNode -> next == NULL)
                                    break;
                                 if (subNode -> next -> next == NULL) {
                                    subNode -> next -> next = initNode(DB_LIST_ENTRY);
                                    subNode = subNode -> next -> next;
                                    subNode -> sub = copyTree(hierRootNode);
                                    subNode -> next = initNode(DB_LIST_ENTRY);
                                    subNode = subNode -> next;
                                    subNode -> sub = tmpSubNode -> sub;
                                    break;
                                 }
                                 subNode = subNode -> next -> next;
                              }
                              if (debug) printf("eventTree:\n");
                              if (debug) printTree(eventTree);
                           }
                        } else
                        ///////////////////////////////////
                        // condition
                        ///////////////////////////////////
                        if (tmpSubNode -> id == G_PDVL_COND_DECLARATION) {
                           NODE* condSignalNameNode = getNode(tmpSubNode -> sub, G_PDVL_COND_SIGNAL_NAME);
                           string condName = getSI(tmpSubNode -> sub);
                           if (condSignalNameNode != NULL) {
                              if (debug) printTree(tmpSubNode);      
                              if (debug) 
                              if (reportLevel > 3) {
                                 printf("2.7.1 Joining condition: %s\n", condName.c_str()); 
                              }
                              string tmpHeader = "";
                              NODE* subNode = getTree(tmpHeader, condName, condTree);
                              NODE* dbEDNode = NULL;
                              if (subNode == NULL) {
                                 subNode = initNode(DB_LIST_ENTRY);
                                 addSITree(condName, subNode, condTree);
                                 dbEDNode = initSubNode(subNode, DB_DEFINES);
                              } else {
                                 if (debug) printf("condTree:\n");
                                 if (debug) printTree(condTree);
                                 if (debug) printf("subNode:\n");
                                 if (debug) printTree(subNode);
                                 if (subNode -> sub != NULL)
                                 if (subNode -> sub -> id == DB_DEFINES)
                                    dbEDNode = subNode -> sub;
                                 if (dbEDNode == NULL)
                                 if (subNode -> next != NULL)
                                 if (subNode -> next -> sub != NULL)
                                 if (subNode -> next -> sub -> id == DB_DEFINES)
                                    dbEDNode = subNode -> sub -> next;
                              } 
                              if (dbEDNode == NULL) {
                                 dbEDNode = initNode(DB_DEFINES);
                                 dbEDNode -> next = subNode -> sub;
                                 subNode -> sub = dbEDNode;
                              }
                            
                              if (dbEDNode -> sub == NULL) {
                                 subNode = initSubNode(dbEDNode, DB_LIST_ENTRY);
                                 subNode -> sub = copyTree(hierRootNode);
                                 subNode -> next = initNode(DB_LIST_ENTRY);
                                 subNode = subNode -> next;
                                 subNode -> sub = tmpSubNode -> sub;
                              } else {
                                 subNode = dbEDNode -> sub;
                                 if (debug) printf("subNode:\n");
                                 if (debug) printTree(subNode);
                                 while (1) {
                                    if (subNode -> next == NULL)
                                       break;
                                    if (subNode -> next -> next == NULL) {
                                       subNode -> next -> next = initNode(DB_LIST_ENTRY);
                                       subNode = subNode -> next -> next;
                                       subNode -> sub = copyTree(hierRootNode);
                                       subNode -> next = initNode(DB_LIST_ENTRY);
                                       subNode = subNode -> next;
                                       subNode -> sub = tmpSubNode -> sub;
                                       break;
                                    }
                                    subNode = subNode -> next -> next;
                                 }
                                 if (debug) printf("condTree:\n");
                                 if (debug) printTree(condTree);
                              }
                              if (debug) printf("condTree:\n");
                              if (debug) printTree(condTree);
                           } else {
                              condSignalNameNode = getNode(tmpSubNode -> sub, G_PDVL_LIST_OF_COND_IDENTIFIERS);
                              if (condSignalNameNode != NULL) {
                                 condSignalNameNode = condSignalNameNode -> sub;
                                 while (1) {
                                    condName = getSI(condSignalNameNode -> sub);
                                    addSITree(condName, NULL, condTree);
                                    if (debug) printTree(tmpSubNode);      
                                    if (condSignalNameNode -> sub -> next == NULL)
                                       break;
                                    condSignalNameNode = condSignalNameNode -> sub -> next;
                                 }
                              } else
                                 addSITree(condName, NULL, condTree);
                           }
                        }
                     }
                     if (dbEntryNode -> next == NULL)
                        break;
                     dbEntryNode = dbEntryNode -> next;
                  }
               }
            }
            if (node -> sub != NULL)
            if (node -> sub -> next != NULL)
               extractEventAndCondTreeStep2(node -> sub -> next, thisHeader, hierRootNode, eventTree, condTree);
         } 
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
}
/////////////////////////////////////////////////////////////////////////////////
/// Extract PDVL event and PDVL condition, step 1
/////////////////////////////////////////////////////////////////////////////////
void extractEventAndCondTreeStep1 (NODE* node, 
                                   bool isTop, 
                                   bool trueModuleFalseInstance, 
                                   NODE* eventTree, 
                                   NODE* condTree, 
                                   NODE* hierRootNode, 
                                   NODE* hierLeafNode) {
   bool debug = false;
   /////////////////////////////////////////////////////////
   // top or leave found
   /////////////////////////////////////////////////////////
   if ( (isTop)                         |
        ( (node -> id == 0)         &
          (!trueModuleFalseInstance) ) ) {
      if (node -> sub != NULL) {
         NODE* modNode = node;
         if (!(isTop))
         if (modNode -> sub != NULL) { 
            modNode = modNode -> sub; 
         }
         if (debug) printf("extractEventAndCondTreeStep1 check: %d\n", modNode -> id); 
         if (debug) printTree(2, modNode);
         if (modNode -> sub != NULL) {
            NODE* subHierLeafNode = initSubNode(hierLeafNode, 0);
            NODE* dbEntryNode = modNode -> sub;
            ///////////////////////////////////
            // 
            ///////////////////////////////////
            while (true) {
               if (debug) printf("subNode: %d\n", dbEntryNode -> id);
               if (dbEntryNode -> id == DB_SUB_MODULES) {
                  extractEventAndCondTreeStep1(dbEntryNode -> sub, false, true, eventTree, condTree, hierRootNode, subHierLeafNode);
               } else
               if (dbEntryNode -> id == DB_JOINED_CLUSTERS) {
                  if (debug) printSITree(dbEntryNode -> sub);
                  if (debug) printTree(dbEntryNode -> sub);
                  if (debug) printf("hierRootNode:\n");
                  if (debug) printTree(hierRootNode);
                  string newHeader = "";
                  extractEventAndCondTreeStep2(dbEntryNode -> sub, newHeader, hierRootNode, eventTree, condTree);
               }
               if (dbEntryNode -> next == NULL)
                  break;
               dbEntryNode = dbEntryNode -> next;
            }
         }
      }
   /////////////////////////////////////////////////////////
   // module to instance crossing found
   /////////////////////////////////////////////////////////
   } else 
   if (node -> id == 0) {
      NODE* subHierLeafNode = initSubNode(hierLeafNode, 0);
      extractEventAndCondTreeStep1(node -> sub, false, false, eventTree, condTree, hierRootNode, subHierLeafNode);
   } else 
   if (node -> sub != NULL) {
      NODE* subHierLeafNode = initSubNode(hierLeafNode, node -> id);
      extractEventAndCondTreeStep1(node -> sub, false, trueModuleFalseInstance, eventTree, condTree, hierRootNode, subHierLeafNode);
   }
   if (node -> next != NULL)
      extractEventAndCondTreeStep1(node -> next, false, trueModuleFalseInstance, eventTree, condTree, hierRootNode, hierLeafNode);
}
/////////////////////////////////////////////////////////////////////////////////
/// Extract PDVL event and PDVL condition
/////////////////////////////////////////////////////////////////////////////////
void extractEventAndCondTree (NODE* topModuleNode, 
                              NODE* eventTree, 
                              NODE* condTree) {
   NODE* rootNode = initNode(0);
   NODE* leafNode = rootNode; 
   NODE* leafSubNode = initSubNode(leafNode, 0);
   extractEventAndCondTreeStep1(topModuleNode, true, true, eventTree, condTree, rootNode, leafNode);
}
/////////////////////////////////////////////////////////////////////////////////
/// Logic joining
/////////////////////////////////////////////////////////////////////////////////
void logicJoining (NODE* node, bool isTop, bool trueModuleFalseInstance, NODE* eventTree, NODE* condTree,
                   NODE* hierRootNode, NODE* hierLeafNode) {
   bool debug = false;
   /////////////////////////////////////////////////////////
   // top or leave found
   /////////////////////////////////////////////////////////
   if ( (isTop)                        |
        ( (node -> id == 0)          &
          (!trueModuleFalseInstance) ) ) {
      if (node -> sub != NULL) {
         NODE* modNode = node;
         if (!(isTop))
         if (modNode -> sub != NULL) { 
            modNode = modNode -> sub; 
         }
         if (debug) printf("logicJoining check: %d\n", modNode -> id); 
         if (debug) printTree(4, modNode);
         if (modNode -> sub != NULL) {
            NODE* dbEntryNode = modNode -> sub;
            NODE* removeTransactionTree = getNodeSubLevel(modNode, DB_MODULE_TRANSACTIONS_REMOVED);
            if (reportLevel > 2) {
               NODE* moduleNameNode = getNodeSubLevel(modNode, DB_MODULE_NAME);
               if (debug) printTree(4, moduleNameNode);
               if (moduleNameNode != NULL) {
                  string moduleName = getSI(moduleNameNode -> sub);
                  printf("2.7.1 Logic joining: %s (%d)\n", moduleName.c_str(), modNode -> id); 
               }
            }
            ///////////////////////////////////
            // 
            ///////////////////////////////////
            while (true) {
               if (debug) printf("subNode: %d\n", dbEntryNode -> id);
               NODE* savedHierLeafNode = hierLeafNode;
               hierLeafNode = initSubNode(hierLeafNode, 0);
               if (dbEntryNode -> id == DB_SUB_MODULES) {
                  logicJoining(dbEntryNode -> sub, false, true, eventTree, condTree, hierRootNode, hierLeafNode);
               } else
               if (dbEntryNode -> id == DB_JOINED_CLUSTERS) {
                  if (debug) printSITree(dbEntryNode -> sub);
                  if (debug) printTree(dbEntryNode -> sub);
                  string newHeader = "";
                  NODE* transactionTree = initNode(0);
                  NODE* datapathTree = initNode(0);
                  if (debug) printf("Call logicJoiningLevel2\n");
                  logicJoiningLevel2(dbEntryNode -> sub, false, newHeader, modNode, transactionTree, removeTransactionTree, datapathTree);
                  if (debug) printf("Done logicJoiningLevel2\n");
                  if (transactionTree -> sub != NULL) {
                     if (debug) printf("transactionTree:\n"); 
                     if (debug) printSITree(transactionTree);
                  }
                  if (debug) printf("Call logicJoiningPostProcess\n");
                  logicJoiningPostProcess(modNode, transactionTree, eventTree, condTree, datapathTree, hierRootNode);
                  if (debug) printf("Done logicJoiningPostProcess\n");
                  if (debug) printf("Cont logicJoining\n");
               }
               hierLeafNode = savedHierLeafNode;
               if (dbEntryNode -> next == NULL)
                  break;
               dbEntryNode = dbEntryNode -> next;
            }
         }
      }
      if (debug) printf("done a.\n");
   /////////////////////////////////////////////////////////
   // module to instance crossing found
   /////////////////////////////////////////////////////////
   } else 
   if (node -> id == 0) {
      NODE* savedHierLeafNode = hierLeafNode;
      hierLeafNode = initSubNode(hierLeafNode, 0);
      logicJoining(node -> sub, false, false, eventTree, condTree, hierRootNode, hierLeafNode);
      hierLeafNode = savedHierLeafNode;
   } else 
   if (node -> sub != NULL) {
      NODE* savedHierLeafNode = hierLeafNode;
      hierLeafNode = initSubNode(hierLeafNode, node -> id);
      logicJoining(node -> sub, false, trueModuleFalseInstance, eventTree, condTree, hierRootNode, hierLeafNode);
      hierLeafNode = savedHierLeafNode;
   }
   if (node -> next != NULL) {
      logicJoining(node -> next, false, trueModuleFalseInstance, eventTree, condTree, hierRootNode, hierLeafNode);
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL move and route command
/////////////////////////////////////////////////////////////////////////////////
void moveRouteCommand (NODE* node, 
                       bool isTop, 
                       unsigned command, 
                       bool trueModuleFalseInstance, 
                       unsigned *clCntPtr) {
   bool debug = false;
   /////////////////////////////////////////////////////////
   // top or leave found
   /////////////////////////////////////////////////////////
   if ( (isTop)                         |
        ( (node -> id == 0)         &
          (!trueModuleFalseInstance) ) ) {
      if (node -> sub != NULL) {
         NODE* modNode = node;
         NODE* tmpNode = node -> sub;
         if (!(isTop))
            modNode = tmpNode;
         if (debug) printf("moveRouteCommand check: %d\n", modNode -> id); 
         if (debug) printTree(2, modNode);
         if (!(isTop))
         if (tmpNode -> sub != NULL) 
            tmpNode = tmpNode -> sub; 
         ///////////////////////////////////
         // Foreach PDVL command, execute when possible
         ///////////////////////////////////
         while (1) {
            if (debug) printf("%d\n", tmpNode -> id);
            if (tmpNode -> id == DB_SUB_MODULES) {
               moveRouteCommand(tmpNode -> sub, false, command, true, clCntPtr);
            }
            if (tmpNode -> id == DB_MODULE_BUILDS)
            if (tmpNode -> sub != NULL) 
            if (tmpNode -> sub -> next != NULL) {
               NODE* refNode = NULL;
               ///////////////////////////////////
               // Skip module id, first entry
               ///////////////////////////////////
               NODE* tmpSubNode = tmpNode -> sub -> next; 
               while (1) {
                  bool progRefNode = true;
                  if (debug) printf("%d\n", tmpSubNode -> sub -> id);
                  if (tmpSubNode -> sub != NULL) {
                     if (debug) printf("------------------------------------ tmpSubNode -> sub:\n"); 
                     if (debug) printTree(tmpSubNode -> sub); 
                     bool removeCommand = false;
                     if ( (command == 0)                        &
                          (tmpSubNode -> sub -> id == G_PDVL_REMOVE_COMMAND) ) {
                        NODE* moveNode = tmpSubNode -> sub;
                        removeCommand = removeAssignment(moveNode, modNode);
                     } else
                     if ( (command == 1)                        &
                          (tmpSubNode -> sub -> id == G_PDVL_REPLACE_COMMAND) ) {
                        NODE* replaceNode = tmpSubNode -> sub;
                        removeCommand = replaceTransaction(replaceNode, modNode);
                     } else
                     if ( (command == 2)                        &
                          (tmpSubNode -> sub -> id == G_PDVL_MOVE_COMMAND) ) {
                        NODE* moveNode = tmpSubNode -> sub;
                        removeCommand = moveAssignment(moveNode, modNode);
                     } else
                     if ( (command == 3)                        &
                          (tmpSubNode -> sub -> id == G_PDVL_ROUTE_COMMAND) ) {
                        NODE* moveNode = tmpSubNode -> sub;
                        removeCommand = routeCommand(moveNode, modNode, clCntPtr);
                     } else
                     if (debug) 
                        printf("\t%d\n", tmpSubNode -> sub -> id);
                     if (removeCommand) {
                        if (debug) printf("removing command\n");
                        if (refNode == NULL) {
                           tmpNode -> sub -> next = tmpSubNode -> next;
                           progRefNode = false; 
                        } else {
                           refNode -> next = tmpSubNode -> next; 
                           progRefNode = false; 
                        }
                     }
                  }
                  if (tmpSubNode -> next == NULL)
                     break;
                  if (progRefNode)
                     refNode = tmpSubNode;
                  tmpSubNode = tmpSubNode -> next;
               }
               if (debug) printf("cont");
            }
            if (tmpNode -> next == NULL)
               break;
            tmpNode = tmpNode -> next;
         }
      }
   /////////////////////////////////////////////////////////
   // module to instance crossing found
   /////////////////////////////////////////////////////////
   } else 
   if (node -> id == 0) {
      moveRouteCommand(node -> sub, false, command, false, clCntPtr);
   } else 
   if (node -> sub != NULL)
      moveRouteCommand(node -> sub, false, command, trueModuleFalseInstance, clCntPtr);
   if (node -> next != NULL)
      moveRouteCommand(node -> next, false, command, trueModuleFalseInstance, clCntPtr);
}
/////////////////////////////////////////////////////////////////////////////////
/// Add entries to parameter RHS tree
/////////////////////////////////////////////////////////////////////////////////
bool addToParameterRHSNode (NODE* node,
                            NODE* givenSIRootNode,
                            NODE* givenSILeafNode,
                            NODE* rootToTopNode,
                            NODE* dbParameterNode) {
   bool debug = false;
   bool returnBool = false;
   if (debug) printf("addToParameterRHSNode: %d\n", node -> id);
   /////////////////////////////////
   // sub is leave
   /////////////////////////////////
   if (node -> id == 0) {
      if (debug) printf("dbParameterNode:\n");
      if (debug) printTree(dbParameterNode);
      if (debug) printf("givenSIRootNode:\n");
      if (debug) printTree(givenSIRootNode);
      string parameterName = getSI(givenSIRootNode);
      if (debug) printf("parameterName: %s\n", parameterName.c_str());
      string header = "";
      NODE* subNode = getTree(header, parameterName, dbParameterNode);
      ///////////////////////////////
      // entry not identified as parameter
      ///////////////////////////////
      if (subNode == NULL) {
      ///////////////////////////////
      // entry is parameter
      ///////////////////////////////
      } else {
         if (debug) printf("subNode:\n");
         if (debug) printTree(subNode);
         NODE* dbRHSNode = NULL;
         if (subNode -> sub -> id == DB_RHS) {
            dbRHSNode = subNode -> sub;
         } else {
            dbRHSNode = initNode(DB_RHS);
            dbRHSNode -> next = subNode -> sub;
            subNode -> sub = dbRHSNode;
         } 
         if (dbRHSNode -> sub == NULL) {
            subNode = initSubNode(dbRHSNode, DB_LIST_ENTRY);
            returnBool = true;
            if (rootToTopNode -> sub != NULL)
                 subNode -> sub = rootToTopNode -> sub;
         } else {
               subNode = dbRHSNode -> sub;
            while (1) {
               if ( (subNode -> sub == NULL)       &
                    (rootToTopNode -> sub == NULL) ) {
                  break;
               }
               if ( (subNode -> sub != NULL)       &
                    (rootToTopNode -> sub != NULL) ) {
                  if (checkTree(subNode -> sub, rootToTopNode -> sub))
                     break;
               }
               if (subNode -> next == NULL) {
                  subNode -> next = initNode(DB_LIST_ENTRY);
                  returnBool = true;
                  if (rootToTopNode -> sub != NULL)
                     subNode -> next -> sub = rootToTopNode -> sub;
                  break;
               }
               subNode = subNode -> next;
            }
         }
         if (debug) printf("dbParameterNode:\n");
         if (debug) printTree(dbParameterNode);
      }
   } else
   /////////////////////////////////
   // sub continue
   /////////////////////////////////
   if (node -> sub != NULL)
   {  
      NODE* newNode = initNode(node -> id);
      bool top = false;
      if (givenSILeafNode -> id == G_SI) {
         givenSILeafNode -> sub = newNode; 
      } else
         givenSILeafNode -> next = newNode; 
      NODE* savedGivenSILeafNode = givenSILeafNode;
      givenSILeafNode = newNode;
      if (addToParameterRHSNode(node -> sub,
                               givenSIRootNode,
                               givenSILeafNode,
                               rootToTopNode,
                               dbParameterNode))
         returnBool = true;
      givenSILeafNode = savedGivenSILeafNode;
      givenSILeafNode -> sub = NULL;
      givenSILeafNode -> next = NULL;
   }
   /////////////////////////////////
   // sub next continue
   /////////////////////////////////
   if (node -> next != NULL) {
      if (addToParameterRHSNode(node -> next,
                               givenSIRootNode,
                               givenSILeafNode,
                               rootToTopNode,
                               dbParameterNode))
         returnBool = true;
   }
   return returnBool;
}
/////////////////////////////////////////////////////////////////////////////////
/// Add entries to parameter RHS tree, subroutine 2
/////////////////////////////////////////////////////////////////////////////////
void addToParameterRHSNode2 (NODE* node,
                             NODE* givenSIRootNode,
                             NODE* givenSILeafNode,
                             NODE* rootToTopNode,
                             NODE* dbParameterNode) {
   bool debug = false;
   if (node -> sub == NULL) {
      return;
   }
   /////////////////////////////////
   // sub is leave
   /////////////////////////////////
   if (node -> sub -> id == 0) {
      if (debug) printf("givenSIRootNode:\n");
      if (debug) printTree(givenSIRootNode);
      if (debug) printSITree(givenSIRootNode -> sub);
      string parameterName = getSI(givenSIRootNode);
      if (debug) printf("parameterName: %s\n", parameterName.c_str());
      if (debug) printf("givenSIRootNode:\n");
      if (debug) printTree(givenSIRootNode -> sub);
      string header = "";
      NODE* subNode = getTree(header, parameterName, dbParameterNode);
      if (subNode == NULL) {
         subNode = initNode(DB_LIST_ENTRY);
         addSITree(parameterName, subNode, dbParameterNode);
         subNode = initSubNode(subNode, DB_RHS);
         subNode = initSubNode(subNode, DB_LIST_ENTRY);
         if (rootToTopNode -> sub != NULL)
            subNode -> sub = rootToTopNode -> sub;
      } else {
         if (debug) printf("dbParameterNode:\n");
         if (debug) printTree(5, dbParameterNode);
         if (debug) printf("subNode:\n");
         if (debug) printTree(5, subNode);
         subNode = subNode -> sub;
         subNode = subNode -> sub;
         while (1) {
            if ( (subNode -> sub == NULL)       &
                 (rootToTopNode -> sub == NULL) ) {
               break;
            }
            if ( (subNode -> sub != NULL)       &
                 (rootToTopNode -> sub != NULL) ) {
               if (checkTree(subNode -> sub, rootToTopNode -> sub))
                  break;
            }
            if (subNode -> next == NULL) {
               subNode -> next = initNode(DB_LIST_ENTRY);
               if (rootToTopNode -> sub != NULL)
                  subNode -> next -> sub = rootToTopNode -> sub;
               break;
            }
            subNode = subNode -> next;
         }
         if (debug) printf("dbParameterNode:\n");
         if (debug) printTree(5, dbParameterNode);
      }
      if (debug) printf("dbParameterNode:\n");
      if (debug) printTree(5, dbParameterNode);
   } else
   /////////////////////////////////
   // sub continue
   /////////////////////////////////
   {  
      NODE* newNode = initNode(node -> sub -> id);
      if (givenSILeafNode -> id == G_SI)
         givenSILeafNode -> sub = newNode; 
      else
         givenSILeafNode -> next = newNode; 
      NODE* savedGivenSILeafNode = givenSILeafNode;
      givenSILeafNode = newNode;
      addToParameterRHSNode(node -> sub,
                            givenSIRootNode,
                            givenSILeafNode,
                            rootToTopNode,
                            dbParameterNode);
      givenSILeafNode = savedGivenSILeafNode;
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Get global signal tree, step 4, "add RHS"
/////////////////////////////////////////////////////////////////////////////////
void getGlobalSignalTreeStep4 (bool trueLHSfalseRHS, 
                               NODE* node, 
                               unsigned clId,
                               NODE* typeNode, 
                               NODE* parameterAssignmentNode, 
                               NODE* dbSignalRelNode, 
                               NODE* hierRootNode) {
   bool debug = false;
   if (debug) printf("Calling getGlobalSignalTreeStep4 %d\n", trueLHSfalseRHS);
   if (debug) printTree(node);
   while (true) {
      /////////////////////////////////////////
      // find\generate relevant entry in dbSignalTree
      /////////////////////////////////////////
      NODE* subNode = NULL;
      if ((trueLHSfalseRHS)     |
          (node -> sub != NULL) ) {
         NODE* compareNode = node;
         if (dbSignalRelNode -> sub == NULL) {
            if (debug) printf("getGlobalSignalTreeStep4 auto %d\n", compareNode -> id);
            subNode = initNode(compareNode -> id);
            dbSignalRelNode -> sub = subNode; 
         } else
            subNode = dbSignalRelNode -> sub;
         NODE* refNode;
         while (1) {
            if (compareNode -> id == subNode -> id) {
               if (debug) printf("getGlobalSignalTreeStep4 match %d %d\n", compareNode -> id, subNode -> id);
               break;
            }
            /////////////////////////////////////////
            // insert new branch before subnode
            /////////////////////////////////////////
            if (compareNode -> id < subNode -> id) {
               if (debug) printf("getGlobalSignalTreeStep4 insert %d %d\n", compareNode -> id, subNode -> id);
               NODE* newEntryNode = initNode(compareNode -> id);
               newEntryNode -> next = subNode;
               if (subNode == dbSignalRelNode -> sub)
                   dbSignalRelNode -> sub = newEntryNode;
               else 
                   refNode -> next = newEntryNode; 
               subNode = newEntryNode;
               break;
            }
            /////////////////////////////////////////
            // append new branch
            /////////////////////////////////////////
            if (subNode -> next == NULL) {
               if (debug) printf("getGlobalSignalTreeStep4 append %d %d\n", compareNode -> id, subNode -> id);
               NODE* newEntryNode = initNode(compareNode -> id);
               subNode -> next = newEntryNode; 
               subNode = newEntryNode;
               break;
            }
            refNode = subNode;
            subNode = subNode -> next;
         }
      }
      if (debug) printf("test if end of list or tree reached.\n");
      /////////////////////////////////////////
      // test if end of list\tree reached
      /////////////////////////////////////////
      bool next = false;
      if (trueLHSfalseRHS) {
         if (node -> next != NULL)
            next = true;
      } else
      if (node -> sub -> id != 0)
         next = true;
      if (next) {
         if (trueLHSfalseRHS)
            getGlobalSignalTreeStep4(trueLHSfalseRHS, node -> next, clId, typeNode, parameterAssignmentNode, subNode, hierRootNode);
         else
            getGlobalSignalTreeStep4(trueLHSfalseRHS, node -> sub, clId, typeNode, parameterAssignmentNode, subNode, hierRootNode);
      /////////////////////////////////////////
      // finish, check for existing tree and insert
      /////////////////////////////////////////
      } else {
         if (debug) printf("found step4\n");
         if (debug) printTree(subNode);
         /////////////////////////////////////////
         // finish
         /////////////////////////////////////////
         bool insert = true;
         if (subNode -> sub == NULL) {
            if (debug) printf("getGlobalSignalTreeStep4 finish %d\n", node -> id);
            subNode -> sub = initNode(0); 
         /////////////////////////////////////////
         // check for existing tree
         /////////////////////////////////////////
         } else
         if (hierRootNode -> sub -> sub != NULL)
         if (subNode -> sub -> sub != NULL) {
            NODE* subSubNode = subNode -> sub -> sub;
            while (true) {
               if ( ( (trueLHSfalseRHS)            &
                      (subSubNode -> id == DB_LHS) ) |
                    ( (!trueLHSfalseRHS)           &
                      (subSubNode -> id == DB_RHS) ) ) {
                  NODE* tmpNode = subSubNode -> sub;
                  while (true) {
                     if (tmpNode -> id == clId)
                     if (tmpNode  -> sub != NULL) {
                        if (checkTree(tmpNode -> sub, hierRootNode -> sub -> sub)) {
                           insert = false;
                           break;
                        }
                     }
                     if (trueLHSfalseRHS)
                        tmpNode = tmpNode -> next;
                     if (tmpNode -> next == NULL)
                        break;
                     tmpNode = tmpNode -> next;
                  }
                  if (!insert)
                     break;
               }
               if (subSubNode -> next == NULL)
                  break;
               subSubNode = subSubNode -> next;
            }
         }
         /////////////////////////////////////////
         // insert
         /////////////////////////////////////////
         if (insert) {
            if (debug) printf("insert\n");
            NODE* lhsrhsNode = NULL;
            if (subNode -> sub -> sub == NULL) {
               lhsrhsNode = initNode(DB_RHS);
               if (trueLHSfalseRHS)
                  lhsrhsNode -> id = DB_LHS;
               subNode -> sub -> sub = lhsrhsNode;
            } else {
               if (debug) printf("----------- check :\n");
               if (debug) printTree(subNode);
               NODE* tmpNode = subNode -> sub -> sub;
               while (1) {
                  if ( (trueLHSfalseRHS)   &
                       (tmpNode -> id == DB_LHS) ) {
                     lhsrhsNode = tmpNode;
                     break;
                  } else
                  if ( (!trueLHSfalseRHS)   &
                       (tmpNode -> id == DB_RHS) ) {
                     lhsrhsNode = tmpNode;
                     break;
                  }
                  if (tmpNode -> next == NULL) {
                     lhsrhsNode = initNode(DB_RHS);
                     if (trueLHSfalseRHS)
                        lhsrhsNode -> id = DB_LHS;
                     tmpNode -> next = lhsrhsNode;
                     break;
                  }
                  tmpNode = tmpNode -> next;
               }
            }
            if (debug) printf("insert continue lhsrhsNode: %d\n", trueLHSfalseRHS);
            if (debug) printTree(lhsrhsNode);
            NODE* thisClNode = initNode(clId);
            if (hierRootNode -> sub != NULL)
            if (hierRootNode -> sub -> sub != NULL) {
               thisClNode -> sub = copyTree(hierRootNode -> sub -> sub);
            }
            // helper for top level
            if (thisClNode -> sub == NULL) {
               thisClNode -> sub = initNode(0);
            }
            ////////////////////////////////////////////////
            // empty RHS or LHS node => insert
            ////////////////////////////////////////////////
            if (lhsrhsNode -> sub == NULL) {
               if (trueLHSfalseRHS) {
                  if (typeNode == NULL)
                     thisClNode -> next = initNode(1);
                  else {
                     thisClNode -> next = initNode(1);
                     thisClNode -> next -> sub = copyTree(typeNode);
                  }
               }
               lhsrhsNode -> sub = thisClNode;
               if (debug) printf("inserted:\n");
               if (debug) printTree(lhsrhsNode);
            } else {
            ////////////////////////////////////////////////
            // check for cluster same cluster id
            ////////////////////////////////////////////////
               NODE* tmpNode = lhsrhsNode -> sub;
               while (1) {
                  ////////////////////////////////////////////////
                  // same cluster id found => merge
                  ////////////////////////////////////////////////
                  if (tmpNode -> id == clId) {
                     if (debug) printf("------------- before merge:\n");
                     if (debug) printTree(tmpNode);
                     if (debug) printf("------------- merge:\n");
                     if (debug) printTree(thisClNode);
                     mergeTrees(true, thisClNode, tmpNode);
                     if (debug) printf("------------- after merge:\n");
                     if (debug) printTree(tmpNode);
                     break;
                  }
                  ////////////////////////////////////////////////
                  // same cluster id NOT found -> insert
                  ////////////////////////////////////////////////
                  if (tmpNode -> next == NULL) {
                     if (trueLHSfalseRHS) {
                        if (typeNode == NULL)
                           thisClNode -> next = initNode(1);
                        else {
                           thisClNode -> next = initNode(1);
                           thisClNode -> next -> sub = copyTree(typeNode);
                        }
                        thisClNode -> next -> next = lhsrhsNode -> sub;
                     } else
                        thisClNode -> next = lhsrhsNode -> sub;
                     lhsrhsNode -> sub = thisClNode;
                     break;
                  }
                  tmpNode = tmpNode -> next;
               }
            }
         }         
         if (debug) printf("----------- final:\n");
         if (debug) printTree(dbSignalNode);
         if (parameterAssignmentNode != NULL) {
            if (debug) printf("----------- cont 1\n");
            if (debug) printTree(subNode -> sub);
            NODE* dbPASNode = initNode(DB_PAS);
            dbPASNode -> next = subNode -> sub -> sub;
            subNode -> sub -> sub = dbPASNode;
            dbPASNode -> sub = initNode(G_SV_PARAMETER_DECLARATION);
            dbPASNode -> sub -> sub = copyTree(parameterAssignmentNode);
            if (debug) printf("----------- cont 2\n");
            if (debug) printTree(subNode -> sub);
         }
      }
      if ((trueLHSfalseRHS)      |
          (node -> next == NULL) )
         break;    
      node = node -> next; 
   }   
}
/////////////////////////////////////////////////////////////////////////////////
/// Get global signal tree, step 2, "pass instantiation name"
/////////////////////////////////////////////////////////////////////////////////
void getGlobalSignalTreeStep2 (NODE* node, NODE* rootNode, 
                               bool trueType, 
                               bool trueFullFalseParameterLHS, 
                               NODE* dbParameterNode, 
                               NODE* dbTypeNode, 
                               NODE* dbFunctionNode,
                               NODE* leafNode) {
   bool debug = false;
   if (debug) printf("getGlobalSignalTreeStep2 call: %d\n", node -> id);
   while (true) {
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if ( (node -> sub -> id != 0) ) {
            NODE* tmpLeafNode = initNode(node  -> id);
            leafNode -> sub = tmpLeafNode;
            getGlobalSignalTreeStep2(node -> sub, rootNode, trueType, trueFullFalseParameterLHS, dbParameterNode, dbTypeNode, dbFunctionNode, tmpLeafNode);
            delete tmpLeafNode;
         } else {
            if (debug) printf("getGlobalSignalTreeStep2: extract info\n");
            if (debug) printTree(rootNode);
            if (debug) printf("found step3\n");
            if (debug) printTree(node -> sub);
            if (debug) printf("id: %d\n", node -> sub -> sub -> id);
            if (node -> sub -> sub != NULL) 
            if (node -> sub -> sub -> sub != NULL) { 
               NODE* thisLeafNode = initNode(node -> id);
               leafNode -> sub = thisLeafNode;
               NODE* tmpLeafNode = initNode(0);
               thisLeafNode -> sub = tmpLeafNode;
               
               getGlobalSignalTreeStep1(node -> sub -> sub, rootNode, trueType, trueFullFalseParameterLHS, dbParameterNode, dbTypeNode, dbFunctionNode, leafNode);
               
               leafNode -> sub = NULL;
               delete tmpLeafNode;
            }
            if (debug) printSITree(node -> sub -> sub);
            if (debug) printf("cont 1\n");
            if (node -> sub != NULL)
            if (node -> sub -> next != NULL) {
               NODE* tmpLeafNode = initNode(node -> sub -> next -> id);
               leafNode -> sub = tmpLeafNode;
               getGlobalSignalTreeStep2(node -> sub -> next, rootNode, trueType, trueFullFalseParameterLHS, dbParameterNode, dbTypeNode, dbFunctionNode, tmpLeafNode);
               leafNode -> sub = NULL;
               delete tmpLeafNode;
            }
         } 
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
}
/////////////////////////////////////////////////////////////////////////////////
/// Add type entries to dbTypeNode
/////////////////////////////////////////////////////////////////////////////////
void addTypeToDBType (NODE* node, 
                      NODE* dbTypeNode, 
                      NODE* rootNode) {
   bool debug = false;
   NODE* tmpNode = node;
   NODE* subNode = tmpNode -> sub;
   while (true) {
      if (debug) printf("subNode: %d\n", subNode -> id);
      if (subNode -> id == DB_SIGNAL_TYPE) {
         if (debug) printTree(5, subNode -> sub);
         NODE* typeIdentifierNode = getNode(tmpNode -> sub, G_SV_TYPE_IDENTIFIER);
         if (typeIdentifierNode != NULL) {
            string typeName = getSI(typeIdentifierNode);
            if (debug) printf("found typedef: %s\n", typeName.c_str()); 
            string header = "";
            NODE* entryNode = getTree(header, typeName, dbTypeNode);
            ///////////////////////////////
            // entry not identified as tpye entry
            ///////////////////////////////
            if (entryNode == NULL) {
               if (debug) printf("empty entryNode\n");
               NODE* subNode = initNode(DB_LIST_ENTRY);
               addSITree(typeName, subNode, dbTypeNode);
               subNode = initSubNode(subNode, DB_RHS);
               subNode -> sub = initNode(DB_LIST_ENTRY);
               if (rootNode -> sub != NULL)
               if (rootNode -> sub -> sub != NULL) {
                  NODE* rootToTopNode = copyTree(rootNode -> sub);
                  subNode -> sub -> sub = rootToTopNode -> sub;
               }
            } else {
            ///////////////////////////////
            // entry is type
            ///////////////////////////////
               NODE* rootToTopNode = copyTree(rootNode -> sub);
               NODE* dbRHSNode = NULL;
               if (entryNode -> sub -> id == DB_RHS) {
                  dbRHSNode = entryNode -> sub;
               } else {
                  dbRHSNode = initNode(DB_RHS);
                  dbRHSNode -> next = entryNode -> sub;
                  entryNode -> sub = dbRHSNode;
               } 
               if (dbRHSNode -> sub == NULL) {
                  NODE* entrySubNode = initSubNode(dbRHSNode, DB_LIST_ENTRY);
                  if (rootToTopNode -> sub != NULL)
                     entrySubNode -> sub = rootToTopNode -> sub;
               } else {
                  NODE* entrySubNode = dbRHSNode -> sub;
                  while (1) {
                     if ( (entrySubNode -> sub == NULL)       &
                          (rootToTopNode -> sub == NULL) ) {
                        break;
                     }
                     if ( (entrySubNode -> sub != NULL)       &
                          (rootToTopNode -> sub != NULL) ) {
                        if (checkTree(entrySubNode -> sub, rootToTopNode -> sub))
                           break;
                     }
                     if (entrySubNode -> next == NULL) {
                        entrySubNode -> next = initNode(DB_LIST_ENTRY);
                        if (rootToTopNode -> sub != NULL)
                           entrySubNode -> next -> sub = rootToTopNode -> sub;
                        break;
                     }
                     entrySubNode = entrySubNode -> next;
                  }
               }
               if (debug) printf("entryNode:\n");
               if (debug) printTree(entryNode);
            }
         }
      } 
      if (subNode -> next == NULL)
         break;
      subNode = subNode -> next;
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Add RHS entries to collectors
/////////////////////////////////////////////////////////////////////////////////
void addRHSToCollectors (NODE* subNode, 
                         NODE* rootNode, 
                         //bool trueFullFalseParameterLHS, 
                         NODE* dbFunctionNode, 
                         NODE* dbParameterNode) {
   bool debug = false;
   NODE* rhsTree = initNode(0);
   getRHSTree(true, subNode -> sub, rhsTree);
   if (debug) printf("rhsTree:\n");
   if (debug) printTree(rhsTree);
   if (rhsTree -> sub != NULL) { 
      if (dbFunctionNode -> sub != NULL) {
         NODE* givenSIRootNode = initNode(G_SI);
         NODE* thisRootToTopNode = copyTree(rootNode -> sub);
         addToParameterRHSNode(rhsTree -> sub, 
                               givenSIRootNode,
                               givenSIRootNode,
                               thisRootToTopNode,
                               dbFunctionNode);
      }
      if (dbParameterNode -> sub != NULL) {
         NODE* givenSIRootNode = initNode(G_SI);
         NODE* thisRootToTopNode = copyTree(rootNode -> sub);
         addToParameterRHSNode(rhsTree -> sub, 
                               givenSIRootNode,
                               givenSIRootNode,
                               thisRootToTopNode,
                               dbParameterNode);
      }
   }
}
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
                               NODE* leafNode) {
   bool debug = false;
   NODE* clNode = node;
   NODE* dbEntryNode = clNode -> sub;
   while (1) {
      ////////////////////////////////////////////
      //	Typedefs
      ////////////////////////////////////////////
      if (debug) printf("getGlobalSignalTreeStep1: %d\n", dbEntryNode -> id);
      if ( (dbEntryNode -> id == DB_MODULE_TYPES) ) {
         NODE* tmpClNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("--------------------------\n"); 
            if (debug) printTree(tmpClNode -> sub);
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (tmpNode -> sub != NULL) {
                  NODE* typeIdentifierNode = getNode(tmpNode -> sub, G_SV_TYPE_IDENTIFIER);
                  string typeName = getSI(typeIdentifierNode);
                  if (debug) printf("found typedef: %s\n", typeName.c_str()); 
                  if (debug) {
                     printf("--------------------------\n"); 
                     printTree(tmpNode -> sub);
                  }
                  string header = "";
                  ///////////////////////////////////
                  // check if already in dbTypeNode
                  ///////////////////////////////////
                  if (trueType) {
                     NODE* subListNode = getTree(header, typeName, dbTypeNode);
                     if (subListNode == NULL) {
                        NODE* subNode = initNode(DB_LIST_ENTRY);
                        addSITree(typeName, subNode, dbTypeNode);
                        subNode = initSubNode(subNode, DB_LHS);
                        subNode = initSubNode(subNode, DB_LIST_ENTRY);
                        if (rootNode -> sub != NULL)
                           subNode -> sub = copyTree(rootNode -> sub);
                        subNode -> next = initNode(DB_LIST_ENTRY);
                        subNode = subNode -> next;
                        subNode -> sub = tmpNode -> sub;
                     } else {
                        if (debug) printf("found typedef: %s\n", typeName.c_str()); 
                        if (debug) printf("subListNode:\n");
                        if (debug) printTree(subListNode);
                        if (subListNode -> sub == NULL) {
                           printf("subListNode should not be empty:\n");
                           exit(-1);
                        }
                        NODE* dbLHSNode;
                        if (subListNode -> sub -> id == DB_LHS) {
                           dbLHSNode = subListNode -> sub;
                        } else
                        if (subListNode -> sub -> next == NULL) {
                           dbLHSNode = initNode(DB_LHS);
                           subListNode -> sub -> next = dbLHSNode;
                        } else
                           dbLHSNode = subListNode -> sub -> next;
                        NODE* listEntryNode;
                        if (dbLHSNode -> sub == NULL) {
                           listEntryNode = initNode(DB_LIST_ENTRY);
                           dbLHSNode -> sub = listEntryNode;
                        } else {
                           listEntryNode = dbLHSNode -> sub;
                           while (listEntryNode -> next != NULL) 
                              listEntryNode = listEntryNode -> next;
                           listEntryNode -> next = initNode(DB_LIST_ENTRY);
                           listEntryNode = listEntryNode -> next;
                        }
                        listEntryNode -> sub = copyTree(rootNode -> sub);
                        listEntryNode -> next = initNode(DB_LIST_ENTRY);
                        listEntryNode = listEntryNode -> next;
                        listEntryNode -> sub = tmpNode -> sub;
                        if (debug) printf("subListNode:\n");
                        if (debug) printTree(subListNode);
                     }
                  } else
                  if (!trueFullFalseParameterLHS) {
                     NODE* subNode = tmpNode -> sub;
                     addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                  }
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }                     
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         } 
      } else                    
      ////////////////////////////////////////////
      //	FUNCTIONS
      ////////////////////////////////////////////
      if ( (dbEntryNode -> id == DB_MODULE_FUNCTIONS) ) {
         NODE* tmpClNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("--------------------------\n"); 
            if (debug) printTree(tmpClNode -> sub);
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (tmpNode -> sub != NULL) {
                  NODE* typeIdentifierNode = getNode(tmpNode -> sub, G_SV_TF_IDENTIFIER);
                  string typeName = getSI(typeIdentifierNode);
                  if (debug) printf("found function: %s\n", typeName.c_str()); 
                  if (debug) {
                     printf("--------------------------\n"); 
                     printTree(tmpNode -> sub);
                  }
                  string header = "";
                  ///////////////////////////////////
                  // check if already in dbFunctionNode
                  ///////////////////////////////////
                  if (trueType) {
                     NODE* subListNode = getTree(header, typeName, dbFunctionNode);
                     if (subListNode == NULL) {
                        NODE* subNode = initNode(DB_LIST_ENTRY);
                        addSITree(typeName, subNode, dbFunctionNode);
                        subNode = initSubNode(subNode, DB_LHS);
                        subNode = initSubNode(subNode, DB_LIST_ENTRY);
                        if (rootNode -> sub != NULL)
                           subNode -> sub = copyTree(rootNode -> sub);
                        subNode -> next = initNode(DB_LIST_ENTRY);
                        subNode = subNode -> next;
                        subNode -> sub = tmpNode -> sub;
                     } else {
                        if (debug) printf("found function: %s\n", typeName.c_str()); 
                        if (debug) printf("subListNode:\n");
                        if (debug) printTree(subListNode);
                        if (subListNode -> sub == NULL) {
                           printf("subListNode should not be empty:\n");
                           exit(-1);
                        }
                        NODE* dbLHSNode;
                        if (subListNode -> sub -> id == DB_LHS) {
                           dbLHSNode = subListNode -> sub;
                        } else
                        if (subListNode -> sub -> next == NULL) {
                           dbLHSNode = initNode(DB_LHS);
                           subListNode -> sub -> next = dbLHSNode;
                        } else
                           dbLHSNode = subListNode -> sub -> next;
                        NODE* listEntryNode;
                        if (dbLHSNode -> sub == NULL) {
                           listEntryNode = initNode(DB_LIST_ENTRY);
                           dbLHSNode -> sub = listEntryNode;
                        } else {
                           listEntryNode = dbLHSNode -> sub;
                           while (listEntryNode -> next != NULL) 
                              listEntryNode = listEntryNode -> next;
                           listEntryNode -> next = initNode(DB_LIST_ENTRY);
                           listEntryNode = listEntryNode -> next;
                        }
                        listEntryNode -> sub = copyTree(rootNode -> sub);
                        listEntryNode -> next = initNode(DB_LIST_ENTRY);
                        listEntryNode = listEntryNode -> next;
                        listEntryNode -> sub = tmpNode -> sub;
                        if (debug) printf("subListNode:\n");
                        if (debug) printTree(subListNode);
                     }
                  } else
                  if (!trueFullFalseParameterLHS) {
                     NODE* subNode = tmpNode -> sub;
                     addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                  }
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }                     
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         } 
      } else                    
      ////////////////////////////////////////////
      //	Items
      ////////////////////////////////////////////
      if (dbEntryNode -> id == DB_MODULE_ITEMS) {
         NODE* tmpClNode = dbEntryNode -> sub;
         if (tmpClNode -> sub != NULL)
         while (1) {
            if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
            if (debug) printTree(tmpClNode -> sub);
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (tmpNode -> sub != NULL) {
                  NODE* itemNameNode = getNode(tmpNode -> sub, G_SI);
                  string itemName = getSI(tmpNode -> sub);
                  if (debug) printf("found item assignment: %s\n", itemName.c_str()); 
                  ////////////////////////////////
                  // Type
                  ////////////////////////////////
                  if (trueType) {
                     addTypeToDBType(tmpNode, dbTypeNode, rootNode);
                  } else {
                  ////////////////////////////////
                  // RHS
                  ////////////////////////////////
                  bool foundLHS = false;                           
                  NODE* subNode = tmpNode -> sub;
                  while (true) {
                     if (debug) printf("subNode: %d\n", subNode -> id);
                     if (debug) printTree(subNode);
                     if ( (trueFullFalseParameterLHS)  &
                          (subNode -> id == DB_ROUTED) ) {
                           getGlobalSignalTreeStep4(true, itemNameNode -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
                     } else
                     if ( (subNode -> id == DB_CONE) ) {
                        if (trueFullFalseParameterLHS) {
                           foundLHS = true;
                           NODE* rhsTree = initNode(0);
                           getRHSTree((subNode -> id == G_SV_BLOCKING_ASSIGN_EXPRESSION), subNode -> sub, rhsTree);
                           if (rhsTree -> sub != NULL)
                              getGlobalSignalTreeStep4(false, rhsTree -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
                           break;
                        } else
                           addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                     } else
                     if ( (subNode -> id == G_PDVL_IDENTIFIER_LIST) ) {
                        if (debug) printf("-------------------------- check for attribute\n"); 
                        if (debug) printTree(tmpNode -> sub);
                        NODE* attNode = getNodeSubLevel(tmpNode -> sub, G_SV_ATTRIBUTE_INSTANCE);
                        if (debug) printf("-------------------------- attNode\n"); 
                        if (attNode != NULL) {
                           if (debug) printTree(attNode);
                           string attName = getSI(attNode);
                           if (debug) printf("attName: %s\n", attName.c_str());
                           transform(attName.begin(), attName.end(), attName.begin(), ::tolower);
                           if (attName == "source")
                              foundLHS = true;
                           else
                           if (attName == "sink") {
                              NODE* rhsTree = initNode(0);
                              addSITree(subNode -> sub -> sub, NULL, rhsTree);
                              if (debug) printf("-------------------------- rhsTree\n"); 
                              if (debug) printTree(rhsTree);
                              if (rhsTree -> sub != NULL)
                                 getGlobalSignalTreeStep4(false, rhsTree -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
                              if (debug) printf("-------------------------- dbSignalNode\n"); 
                              if (debug) printTree(dbSignalNode);
                           }
                        }
                     } else
                     if ( (!trueFullFalseParameterLHS) &
                          (subNode -> id == DB_SIGNAL_TYPE)  ) {
                        addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                      }
                      if (subNode -> next == NULL)
                         break;
                      subNode = subNode -> next;
                  } 
                  ////////////////////////////////
                  // LHS, add type
                  ////////////////////////////////
                  if (foundLHS) {
                     NODE* typeSelectNode = NULL;
                     // point to first select, if exists
                     subNode = tmpNode -> sub;
                     bool firstFound = false;
                     while (true) {
                        if (subNode -> id == DB_SIGNAL_TYPE) {
                           typeSelectNode = subNode -> sub;
                        } 
                        if (debug) printf("subNode: %d\n", subNode -> id);
                        if (subNode -> id == G_SV_SELECT) {
                           if (!(firstFound))
                              typeSelectNode = subNode;
                        }
                        if (subNode -> next == NULL)
                           break;
                        subNode = subNode -> next;
                     }
                     getGlobalSignalTreeStep4(true, itemNameNode -> sub, tmpClNode -> id, typeSelectNode, NULL, dbSignalNode, rootNode -> sub);
                  }
                  }
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }                     
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         } 
      } else                    
      ////////////////////////////////////////////
      //	Registers
      ////////////////////////////////////////////
      if (dbEntryNode -> id == DB_MODULE_REGISTERS) {
         NODE* tmpClNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (debug) printf("tmpNode: %d\n", tmpNode -> id);
               if (tmpNode -> sub != NULL) {
                  NODE* registerNameNode = getNode(tmpNode -> sub, G_SI);
                  string itemName = getSI(tmpNode -> sub);
                  if (debug) printf("found register assignment: %s\n", itemName.c_str()); 
                  ////////////////////////////////
                  // Type
                  ////////////////////////////////
                  if (trueType) {
                     addTypeToDBType(tmpNode, dbTypeNode, rootNode);
                  } else {
                     bool foundLHS = false;                           
                     NODE* subNode = tmpNode -> sub;
                     if (debug) printTree(tmpNode -> sub);
                     while (true) {
                        if (debug) printf("subNode: %d\n", subNode -> id);
                        if (subNode -> id == DB_CONE) {
                           if (trueFullFalseParameterLHS) {
                              foundLHS = true;
                              NODE* rhsTree = initNode(0);
                              getRHSTree(false, subNode -> sub, rhsTree);
                              if (rhsTree -> sub != NULL)
                                 getGlobalSignalTreeStep4(false, rhsTree -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
                              break;
                           } else
                              addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                        } else
                        if ( (!trueFullFalseParameterLHS) &
                             (subNode -> id == DB_SIGNAL_TYPE)  ) {
                           addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                        }
                        if (subNode -> next == NULL)
                           break;
                        subNode = subNode -> next;
                     }
                     if (foundLHS) {
                        NODE* typeSelectNode = NULL;
                        // point to first select, if exists
                        subNode = tmpNode -> sub;
                        bool firstFound = false;
                        while (true) {
                           if (subNode -> id == DB_SIGNAL_TYPE) {
                              typeSelectNode = subNode -> sub;
                           } 
                           if (subNode -> id == G_SV_SELECT) {
                              if (!(firstFound))
                                 typeSelectNode = subNode;
                           }
                           if (subNode -> next == NULL)
                              break;
                           subNode = subNode -> next;
                        }
                        getGlobalSignalTreeStep4(true, registerNameNode -> sub, tmpClNode -> id, typeSelectNode, NULL, dbSignalNode, rootNode -> sub);
                     }
                  }
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }                     
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         }                     
      }  else
      ////////////////////////////////////////////
      //	Latches
      ////////////////////////////////////////////
      if (dbEntryNode -> id == DB_MODULE_LATCHES) {
         NODE* tmpClNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (debug) printf("tmpNode: %d\n", tmpNode -> id);
               if (tmpNode -> sub != NULL) {
                  NODE* registerNameNode = getNode(tmpNode -> sub, G_SI);
                  string itemName = getSI(tmpNode -> sub);
                  if (debug) printf("found register assignment: %s\n", itemName.c_str()); 
                  ////////////////////////////////
                  // Type
                  ////////////////////////////////
                  if (trueType) {
                     addTypeToDBType(tmpNode, dbTypeNode, rootNode);
                  } else {
                  bool foundLHS = false;                           
                  NODE* subNode = tmpNode -> sub;
                  while (true) {
                     if (debug) printf("subNode: %d\n", subNode -> id);
                     if (subNode -> id == DB_CONE) {
                        if (trueFullFalseParameterLHS) {
                           foundLHS = true;
                           NODE* rhsTree = initNode(0);
                           getRHSTree(false, subNode -> sub, rhsTree);
                           if (debug) printSITree(rhsTree -> sub);
                           if (rhsTree -> sub != NULL)
                              getGlobalSignalTreeStep4(false, rhsTree -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
                           break;
                        } else
                           addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                     } else
                     if ( (!trueFullFalseParameterLHS)       &
                          (subNode -> id == DB_SIGNAL_TYPE)  ) {
                        addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                        if (debug) printf("dbParameterNode:\n");
                        if (debug) printTree(5, dbParameterNode);
                     }
                     if (subNode -> next == NULL)
                        break;
                     subNode = subNode -> next;
                  }
                  if (foundLHS) {
                     NODE* typeSelectNode = NULL;
                     // point to first select, if exists
                     subNode = tmpNode -> sub;
                     bool firstFound = false;
                     while (true) {
                        if (subNode -> id == DB_SIGNAL_TYPE) {
                           typeSelectNode = subNode -> sub;
                        } 
                        if (debug) printf("subNode: %d\n", subNode -> id);
                        if (subNode -> id == G_SV_SELECT) {
                        }
                        if (subNode -> next == NULL)
                           break;
                        subNode = subNode -> next;
                     }
                     getGlobalSignalTreeStep4(true, registerNameNode -> sub, tmpClNode -> id, typeSelectNode,NULL, dbSignalNode, rootNode -> sub);
                  }
                  }
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }                     
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         }                     
      } else
      ////////////////////////////////////////////
      //	Submodules
      ////////////////////////////////////////////
      if (dbEntryNode -> id == DB_SUB_MODULES) {
         getGlobalSignalTreeStep3(dbEntryNode -> sub, rootNode, trueType, trueFullFalseParameterLHS, dbParameterNode, dbTypeNode, dbFunctionNode, leafNode -> sub -> sub);
      } else                    
      ////////////////////////////////////////////
      //	Parameters
      ////////////////////////////////////////////
      if (dbEntryNode -> id == DB_MODULE_PARAMETER) {
         NODE* tmpClNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
            if (debug) printTree(tmpClNode);
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (debug) printf("parameterNode: %d\n", tmpNode -> id);
               NODE* paramExpressionNode = getNode(tmpNode -> sub, G_SV_CONSTANT_PARAM_EXPRESSION);
               if (paramExpressionNode != NULL)
               if (trueFullFalseParameterLHS) {
                  string parameterName = getSI(tmpNode -> sub);
                  string header = "";
                  ///////////////////////////////////
                  // check if already in dbParameterNode
                  ///////////////////////////////////
                  NODE* subListNode = getTree(header, parameterName, dbParameterNode);
                  if (subListNode == NULL) {
                     NODE* subNode = initNode(DB_LIST_ENTRY);
                     addSITree(parameterName, subNode, dbParameterNode);
                     subNode = initSubNode(subNode, DB_LHS);
                     subNode = initSubNode(subNode, DB_LIST_ENTRY);
                     if (rootNode -> sub != NULL)
                        subNode -> sub = copyTree(rootNode -> sub);
                     subNode -> next = initNode(DB_LIST_ENTRY);
                     subNode = subNode -> next;
                     subNode -> sub = tmpNode -> sub;
                  } else {
                     if (debug) printf("found parameter assignment: %s\n", parameterName.c_str()); 
                     if (debug) printf("subListNode:\n");
                     if (debug) printTree(subListNode);
                     if (subListNode -> sub == NULL) {
                        printf("subListNode should not be empty:\n");
                        exit(-1);
                     }
                     NODE* dbLHSNode;
                     if (subListNode -> sub -> id == DB_LHS) {
                        dbLHSNode = subListNode -> sub;
                     } else
                     if (subListNode -> sub -> next == NULL) {
                        dbLHSNode = initNode(DB_LHS);
                        subListNode -> sub -> next = dbLHSNode;
                     } else
                        dbLHSNode = subListNode -> sub -> next;
                     NODE* listEntryNode;
                     if (dbLHSNode -> sub == NULL) {
                        listEntryNode = initNode(DB_LIST_ENTRY);
                        dbLHSNode -> sub = listEntryNode;
                     } else {
                        listEntryNode = dbLHSNode -> sub;
                        while (listEntryNode -> next != NULL) 
                           listEntryNode = listEntryNode -> next;
                        listEntryNode -> next = initNode(DB_LIST_ENTRY);
                        listEntryNode = listEntryNode -> next;
                     }
                     listEntryNode -> sub = copyTree(rootNode -> sub);
                     listEntryNode -> next = initNode(DB_LIST_ENTRY);
                     listEntryNode = listEntryNode -> next;
                     listEntryNode -> sub = tmpNode -> sub;
                     if (debug) printf("subListNode:\n");
                     if (debug) printTree(subListNode);
                  }
               } else
               if (!trueFullFalseParameterLHS) {
                  addRHSToCollectors(paramExpressionNode, rootNode, dbFunctionNode, dbParameterNode);
               }
               if (debug) printf("parameterNode: %d done\n", tmpNode -> id);
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }                     
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         }                     
      } else
      if (!(trueType))
      ////////////////////////////////////////////
      //	Inputs \ Outputs
      ////////////////////////////////////////////
      if (dbEntryNode -> id == DB_PORT_DECLARATIONS) {
         NODE* tmpPortNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("tmpPortNode: %d\n", tmpPortNode -> id);
            if (debug) printTree(tmpPortNode -> sub);
            NODE* tmpDecNode = tmpPortNode -> sub;
            NODE* tmpNode = tmpDecNode -> sub -> sub;
            while (1) {
               if ( (!trueFullFalseParameterLHS)          &
                    (tmpNode -> id == G_SV_NET_PORT_TYPE) ) {
                  addRHSToCollectors(tmpNode, rootNode, dbFunctionNode, dbParameterNode);
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
            if (tmpPortNode -> next == NULL)
               break;
            tmpPortNode = tmpPortNode -> next;
         }
      } else
      ////////////////////////////////////////////
      //	WIRES
      //////////////////////////////////////////// 
      if ( (dbEntryNode -> id == DB_MODULE_WIRES) ) {
         if (debug) printTree(dbEntryNode -> sub);
         NODE* tmpWireNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("tmpWireNode: %d\n", tmpWireNode -> id);
            if (debug) printTree(tmpWireNode -> sub);
            NODE* tmpDecNode = tmpWireNode -> sub;
            while (1) {
               NODE* tmpNode = tmpDecNode -> sub -> sub;  // twice !!!
               while (1) {
                  if ( (!trueFullFalseParameterLHS)                  & 
                       (tmpNode -> id == G_SV_DATA_TYPE_OR_IMPLICIT) ) {
                     addRHSToCollectors(tmpNode, rootNode, dbFunctionNode, dbParameterNode);
                  }
                  if (tmpNode -> next == NULL)
                     break;
                  tmpNode = tmpNode -> next;
               }
               if (tmpDecNode -> next == NULL)
                  break;
               tmpDecNode = tmpDecNode -> next;
            }
            if (tmpWireNode -> next == NULL)
               break;
            tmpWireNode = tmpWireNode -> next;
         }
      } else
      ////////////////////////////////////////////
      //	Conditions
      ////////////////////////////////////////////
      if (dbEntryNode -> id == DB_MODULE_CONDITIONS) {
         if (debug) printTree(6, dbEntryNode -> sub);
         NODE* tmpClNode = dbEntryNode -> sub;
         while (1) {
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (tmpNode -> sub != NULL) {
                  if (debug) printTree(5, tmpNode -> sub);
                  NODE* conditionNameNode = getNode(tmpNode -> sub, G_PDVL_LIST_OF_COND_IDENTIFIERS_BY_NAME);
                  if (conditionNameNode == NULL) {
                     conditionNameNode = getNode(tmpNode -> sub, G_PDVL_COND_IDENTIFIER_BY_NAME);
                     if (debug) printTree(tmpNode -> sub);
                  }
                  if (conditionNameNode == NULL) {
                     conditionNameNode = getNode(tmpNode -> sub, G_PDVL_COND_SI);
                     if (debug) printTree(tmpNode -> sub);
                  }
                  if (conditionNameNode == NULL) {
                     conditionNameNode = getNode(tmpNode -> sub, G_PDVL_LIST_OF_COND_IDENTIFIERS_SI);
                  }
                  if (debug) printf("--------------------------- tmpNode -> sub:\n");
                  if (debug) printTree(6, tmpNode -> sub);
                  while (1) {
                     if (debug) printf("--------------------------- conditionNameNode:\n");
                     if (debug) printTree(6, conditionNameNode);
                     string conditionName = getSI(conditionNameNode);
                     if (debug) printf("found condition assignment: %s\n", conditionName.c_str()); 
                     NODE* condSignalNameNode = getNode(tmpNode -> sub, G_PDVL_COND_SIGNAL_NAME);
                     if (condSignalNameNode != NULL) {
                        conditionNameNode = condSignalNameNode -> sub;
                        if (debug) printf("---------------------------\n");
                        if (debug) printTree(conditionNameNode);
                     }
                     bool foundLHS = false;                           
                     NODE* subNode = tmpNode -> sub;
                     while (true) {
                        if (subNode -> id == DB_CONE) {
                           if (trueFullFalseParameterLHS) {
                              foundLHS = true;
                              if (subNode -> sub != NULL)
                              if (subNode -> sub -> sub != NULL)
                              if (subNode -> sub -> sub -> id == G_SV_FUNCTION_DECLARATION)
                                 foundLHS = false;
                              NODE* rhsTree = initNode(0);
                              getRHSTree(false, subNode -> sub, rhsTree);
                              if (rhsTree -> sub != NULL)
                                 getGlobalSignalTreeStep4(false, rhsTree -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
                              break;
                           } else
                              addRHSToCollectors(subNode, rootNode, dbFunctionNode, dbParameterNode);
                        }
                        if (subNode -> next == NULL)
                           break;
                        subNode = subNode -> next;
                     }
                     if (foundLHS) {
                        if (debug) printf("Found LHS.\n");
                        if (debug) printf("--------------------------- dbSignalNode\n");
                        if (debug) printTree(conditionNameNode -> sub);
                        NODE* newSINode = initNode(G_SI);
                        parser_si(conditionName, 0, newSINode);
                        getGlobalSignalTreeStep4(true, newSINode -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
                        if (debug) printf("--------------------------- dbSignalNode\n");
                        if (debug) printSITree(dbSignalNode);
                     }
                     if (conditionNameNode -> sub == NULL)
                        break;
                     if (conditionNameNode -> sub -> next == NULL)
                        break;
                     if (conditionNameNode -> sub -> next -> id != G_LIST_OF_SI)
                        break;
                     conditionNameNode = conditionNameNode -> sub -> next;
                  }
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         }
      } else
      ////////////////////////////////////////////
      //	Events
      ////////////////////////////////////////////
      if ( (dbEntryNode -> id == DB_MODULE_EVENTS) &
           (trueFullFalseParameterLHS)             ) {
         NODE* tmpClNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (debug) printf("tmpNode: %d\n", tmpNode -> id);
               if (tmpNode -> sub != NULL) {
                  NODE* eventNameNode = getNode(tmpNode -> sub, G_PDVL_EVENT_IDENTIFIER_BY_NAME);
                  string eventName = getSI(tmpNode -> sub);
                  if (debug) printf("found event assignment: %s\n", eventName.c_str()); 
                  bool foundLHS = false;
                  NODE* subNode = tmpNode -> sub;
                  while (true) {
                     if (debug) printf("subNode: %d\n", subNode -> id);
                     if (subNode -> id == DB_CONE) {
                        foundLHS = true;
                        if (debug) printTree(subNode -> sub);
                        NODE* rhsTree = initNode(0);
                        getRHSTree(false, subNode -> sub, rhsTree);
                        if (debug) printSITree(rhsTree -> sub);
                        if (rhsTree -> sub != NULL)
                           getGlobalSignalTreeStep4(false, rhsTree -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
                        break;
                     }
                     if (subNode -> next == NULL)
                        break;
                     subNode = subNode -> next;
                  }  
                  if (foundLHS)
                     getGlobalSignalTreeStep4(true, eventNameNode -> sub, tmpClNode -> id, NULL, NULL, dbSignalNode, rootNode -> sub);
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }                     
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         }
      }                     
      if (dbEntryNode -> next == NULL)
         break;
      dbEntryNode = dbEntryNode -> next;
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Get global signal tree, step 3, "pass module name"
/////////////////////////////////////////////////////////////////////////////////
void getGlobalSignalTreeStep3 (NODE* node, NODE* rootNode, 
                               bool trueType, 
                               bool trueFullFalseParameterLHS, 
                               NODE* dbParameterNode, 
                               NODE* dbTypeNode, 
                               NODE* dbFunctionNode,
                               NODE* leafNode) {
   bool debug = false;
   if (debug) printf("getGlobalSignalTreeStep3 call:\n");
   if (debug) printTree(rootNode);
   while (true) {
      NODE* tmpLeafNode = initNode(node -> id);
      leafNode -> sub = tmpLeafNode;
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            getGlobalSignalTreeStep3(node -> sub, rootNode, trueType, trueFullFalseParameterLHS, dbParameterNode, dbTypeNode, dbFunctionNode, tmpLeafNode);
         } else {
            if (debug) printf("found step2\n");
            if (debug) printSITree(node -> sub -> sub);
            // switching modus to add to rootNode-line 
            NODE* tmp2LeafNode = initNode(node -> sub -> id);
            tmpLeafNode -> sub = tmp2LeafNode;
            if (debug) printf("rootNode:\n");
            if (debug) printSITree(rootNode -> sub -> sub -> sub);
            if (debug) printf("node:\n");
            if (debug) printTree(3, node);
            NODE* tmpNode = node -> sub;
            while (1) {
               getGlobalSignalTreeStep2(tmpNode -> sub, rootNode, trueType, trueFullFalseParameterLHS, dbParameterNode, dbTypeNode, dbFunctionNode, tmp2LeafNode); 
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
            delete tmp2LeafNode;
            if (debug) printf("cont 1\n");
         } 
      }
      if (debug) printf("cont 2\n");
      delete tmpLeafNode;

      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
}
/////////////////////////////////////////////////////////////////////////////////
/// Get module, "search by name"
/////////////////////////////////////////////////////////////////////////////////
NODE* getModule (NODE* node, 
                 string &header, 
                 string &topLevelName) {
   bool debug = false;
   while (true) {
      string moduleName = "";
      moduleName.append(header);
      moduleName.append(node2String(node));
      if (node -> sub != NULL)
      if (node -> sub -> id != 0) {
         NODE* returnNode = getModule(node -> sub, moduleName, topLevelName);
         if (returnNode != NULL)
            return returnNode;
      } else
      if (moduleName.compare(topLevelName) == 0) {
         if (debug) printf("Found top-module: %s\n", moduleName.c_str()); 
         if (node -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub != NULL)
         if (node -> sub -> sub -> sub -> sub != NULL) {
            return node -> sub -> sub -> sub;
         }
         if (node -> sub != NULL)
         if (node -> sub -> next != NULL) {
            NODE* returnNode = getModule(node -> sub -> next, moduleName, topLevelName);
            if (returnNode != NULL)
               return returnNode;
         }
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
   return NULL;   
}
/////////////////////////////////////////////////////////////////////////////////
/// Replace parameters
/////////////////////////////////////////////////////////////////////////////////
bool replaceParameters (NODE* node, 
                        NODE* parameterTree) {
   bool debug = false;
   if (	(node -> id == G_SV_HIERARCHICAL_IDENTIFIER) 			|
   		(node -> id == G_SV_GENVAR_IDENTIFIER) 			) {
      NODE* subNode = getSITreeNode(node -> sub -> sub, parameterTree -> sub);
      if (subNode != NULL) {
         if (debug) printf("Index found\n");
         node -> sub = subNode;
      }
      return true;
   } else
   if (node -> sub != NULL) {
      replaceParameters(node -> sub, parameterTree);
   }
   if (node -> next != NULL) {
      replaceParameters(node -> next, parameterTree);
   }
   return true;
} 
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL "if" construct
/////////////////////////////////////////////////////////////////////////////////
bool elaboratePDVLIf (NODE* tmpNode, 
                      NODE* ifNode, 
                      NODE* parameterTree) {
   bool debug = false;
   if (debug) printf("------------------ parameterTree:\n");
   if (debug) printTree(parameterTree);
   if (debug) printf("------------------ ifNode before:\n");
   if (debug) printTree(ifNode);
   NODE* expressionNode = copyTree(ifNode -> sub -> sub);
   if (parameterTree -> sub != NULL)
      replaceParameters(expressionNode, parameterTree);
   if (debug) printf("------------------ ifNode post mod:\n");
   if (debug) printTree(ifNode);
   
   bool execute = false;
   NODE* executeNode = solveEquation(expressionNode);
   if (executeNode == NULL) 
      return false;
   else {
      if (debug) printf("------------------ executeNode:\n");
      if (debug) printTree(executeNode);
      execute = sbin2Bool(executeNode);
   }
   deleteTree(executeNode);
   if (debug) printf("------------------ execute: %d\n", execute);
   ///////////////////////////////////
   // execute
   ///////////////////////////////////
   if (execute) {
      NODE* bodyNode = ifNode -> sub -> next;
      bodyNode -> next = tmpNode -> next;
      tmpNode -> next = bodyNode;
   } else
   ///////////////////////////////////
   // next based on if 
   ///////////////////////////////////
   if (ifNode -> sub -> next -> next != NULL) {
      ///////////////////////////////////
      // execute else
      ///////////////////////////////////
      if ( (ifNode -> sub -> next -> next -> id == G_PDVL_ELSE_COMMAND)     |
           (ifNode -> sub -> next -> next -> id == G_PDVL_ELSE_DECLARATION) ) {
         NODE* bodyNode = ifNode -> sub -> next -> next -> sub;
         bodyNode -> next = tmpNode -> next;
         tmpNode -> next = bodyNode;
      } else
      if ( (ifNode -> sub -> next -> next -> id == G_PDVL_ELSE_IF_COMMAND)     |
           (ifNode -> sub -> next -> next -> id == G_PDVL_ELSE_IF_DECLARATION) ) {
         return elaboratePDVLIf(tmpNode, ifNode -> sub -> next -> next, parameterTree); 
      }
   } else
   ///////////////////////////////////
   // next based on if 
   ///////////////////////////////////
   if ( (ifNode -> id == G_PDVL_ELSE_IF_COMMAND)     |
        (ifNode -> id == G_PDVL_ELSE_IF_DECLARATION) )
   if (ifNode -> next != NULL) {
      ///////////////////////////////////
      // execute else
      ///////////////////////////////////
      if ( (ifNode-> next -> id == G_PDVL_ELSE_COMMAND)     |
           (ifNode-> next -> id == G_PDVL_ELSE_DECLARATION) ) {
         NODE* bodyNode = ifNode -> next -> sub;
         bodyNode -> next = tmpNode -> next;
         tmpNode -> next = bodyNode;
      } else
      if ( (ifNode -> next -> id == G_PDVL_ELSE_IF_COMMAND)     |
           (ifNode -> next -> id == G_PDVL_ELSE_IF_DECLARATION) ) {
         return elaboratePDVLIf(tmpNode, ifNode -> next, parameterTree); 
      }
   }
   if (debug) printf("------------------ returning tmpNode:\n");
   if (debug) printTree(tmpNode);
   return true;
}
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL "case" construct
/////////////////////////////////////////////////////////////////////////////////
bool elaboratePDVLCase (NODE* tmpNode, 
                        NODE* caseNode, 
                        NODE* parameterTree) {
   bool debug = false;
   if (debug) printf("------------------ parameterTree:\n");
   if (debug) printTree(parameterTree);
   if (debug) printf("------------------ caseNode before:\n");
   if (debug) printTree(caseNode);
   
   NODE* caseItemNode = caseNode -> sub -> next;
   while (1) {
      ///////////////////////////////////////
      // handling default case
      ///////////////////////////////////////
      if ( (caseItemNode -> sub -> id == G_PDVL_CASE_COMMAND_DEFAULT)     |
           (caseItemNode -> sub -> id == G_PDVL_CASE_DECLARATION_DEFAULT) ) {
         if (debug) printf("------------------ found default:\n");
         NODE* bodyNode = caseItemNode -> sub -> sub;
         bodyNode -> next = tmpNode -> next;
         tmpNode -> next = bodyNode;
         if (debug) printf("------------------ tmpNode:\n");
         if (debug) printTree(tmpNode);
         return true;
      }
      NODE* listOfConstantExpressionNode = caseItemNode -> sub -> sub;
      while (1) {
         if (debug) printf("------------------ caseNode -> sub -> sub:\n");
         if (debug) printTree(caseNode -> sub -> sub);
         string expressionString = "";
         writer_sv_constant_expression(expressionString, caseNode -> sub -> sub); 
         expressionString.append(" == ");
         writer_sv_constant_expression(expressionString, listOfConstantExpressionNode -> sub -> sub); 
         expressionString.append(" ");
         if (debug) printf("expressionString: %s\n", expressionString.c_str());
         NODE* expressionNode = initNode(0);
         parser_sv_constant_expression(expressionString, 0, expressionNode);
         if (debug) printTree(expressionNode);
         if (parameterTree -> sub != NULL)
            replaceParameters(expressionNode, parameterTree);
         if (debug) printf("------------------ expressionNode post mod:\n");
         if (debug) printTree(expressionNode);
         NODE* executeNode = solveEquation(expressionNode);
         if (executeNode == NULL) {
            exit(-1);
            return false;
         } else {
            if (debug) printf("------------------ executeNode:\n");
            if (debug) printTree(executeNode);
            bool execute = sbin2Bool(executeNode);
            if (execute) {
               NODE* bodyNode = caseItemNode -> sub -> sub -> next;
               bodyNode -> next = tmpNode -> next;
               tmpNode -> next = bodyNode;
               return true;
            }
         }
         deleteTree(executeNode);
         if (listOfConstantExpressionNode -> next == NULL)
            break;
         if ( (listOfConstantExpressionNode -> next -> id == G_PDVL_BUILD_COMMAND_BODY)       |
              (listOfConstantExpressionNode -> next -> id == G_PDVL_CLUSTER_DECLARATION_BODY) ) {
            if (listOfConstantExpressionNode -> sub -> next == NULL)
               break;
            listOfConstantExpressionNode = listOfConstantExpressionNode -> sub -> next;
         } else
            listOfConstantExpressionNode = listOfConstantExpressionNode -> next;
      }
      if (caseItemNode -> next == NULL)
         break;
      caseItemNode = caseItemNode -> next;
   }
   ///////////////////////////////////
   // return true and remove command, because
   // all case items where checked and no default found
   ///////////////////////////////////
   return true;
}
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL "foreach" construct. 
/// Checks if foreach command can be executed. 
/// Does so when parameter defined and returns true, otherwise false.
/////////////////////////////////////////////////////////////////////////////////
bool elaboratePDVLForeach (NODE* tmpNode, 
                           NODE* foreachNode, 
                           NODE* parameterTree) {
   bool debug = false;
   //if (reportLevel > 2)
   //   printf("Elaborate foreach.\n");
   if (debug) 
      printTree(foreachNode);
   ////////////////////////////////
   // standards
   ////////////////////////////////
   NODE* bodyNode = foreachNode -> sub -> next -> next;
   string indexNameString = getSI(foreachNode -> sub);
   NODE* ptrNode = tmpNode;
   //while (ptrNode -> next != NULL) ptrNode = ptrNode -> next;
      
   ////////////////////////////////
   // foreach index in constant expression
   ////////////////////////////////
   if (debug) printf("------------------------- foreachNode:\n");
   if (debug) printTree(foreachNode);
   if (foreachNode -> sub -> next -> sub -> id == G_PDVL_FOREACH_CONSTANT_EXPRESSION) {
      NODE* expressionNode = copyTree(foreachNode -> sub -> next -> sub -> sub -> sub);
      if (parameterTree -> sub != NULL)
         replaceParameters(expressionNode, parameterTree);
      if (debug) printSITree(parameterTree);
      expressionNode = solveEquation(expressionNode);
      if (expressionNode == NULL)
         return false;
      if (debug) printf("------------------------- expressionNode:\n");
      if (debug) printTree(expressionNode); 
      unsigned maxInt = sbin2Unsigned(expressionNode);
      deleteTree(expressionNode);
      if (debug) printf("maxInt: %d\n", maxInt);
      if (maxInt > 0) {
         for (int i = 0; i < maxInt; i++) {  
            string indexValueString = to_string(i);
            if (debug) printf("indexNameString: %s indexValueString: %s\n", indexNameString.c_str(), indexValueString.c_str());
            NODE* newBodyNode = copyTree(bodyNode);
            replaceIndexName(newBodyNode, false, indexNameString, indexValueString);
            if (debug) printf("------------------------------- newBodyNode:\n");
            if (debug) printTree(newBodyNode); 
                       
            ////////////////////////////////
            // execution
            ////////////////////////////////
            NODE* endPtr = newBodyNode;
            while (1) {
               if (endPtr -> next == NULL)
                  break;
               endPtr = endPtr -> next;
            }
            endPtr -> next = ptrNode -> next;
            ptrNode -> next = newBodyNode;
            ptrNode = endPtr; 
         } 
         if (debug) printf("------------------------------- tmpNode:\n");
         if (debug) printTree(tmpNode);
         if (indexNameString.compare("i") != 0)
         return true;
      }
   ////////////////////////////////
   // foreach index in list
   ////////////////////////////////
   } else {
      NODE* listNode = foreachNode -> sub -> next -> sub -> sub;
      while (1) {
         if (debug) printf("------------------------------- listNode -> sub:\n");
         if (debug) printTree(listNode -> sub);

         string indexValueString = getSI(listNode);
         if (debug) printf("indexNameString: %s indexValueString: %s\n", indexNameString.c_str(), indexValueString.c_str());
         NODE* newBodyNode = copyTree(bodyNode);
         replaceIndexName(newBodyNode, false, indexNameString, indexValueString);
         if (debug) printTree(newBodyNode); 
                       
         ////////////////////////////////
         // execution
         ////////////////////////////////
         NODE* endPtr = newBodyNode;
         while (1) {
            if (endPtr -> next == NULL)
               break;
            endPtr = endPtr -> next;
         }
         endPtr -> next = ptrNode -> next;
         ptrNode -> next = newBodyNode;
         ptrNode = endPtr; 

         if (listNode -> next == NULL)
            break;
         listNode = listNode -> next;
      }
      if (debug) printf("-------------------------------\n");
      if (debug) printTree(tmpNode);
      return true;
   }
   return false;
}

/////////////////////////////////////////////////////////////////////////////////
/// Elaborate PDVL "for" construct. 
/// Checks if foreach command can be executed. 
/// Does so when parameter defined and returns true, otherwise false.
/////////////////////////////////////////////////////////////////////////////////
bool elaboratePDVLFor (NODE* tmpNode, 
                       NODE* forNode, 
                       NODE* parameterTree) {
   bool debug = false;
   //if (reportLevel > 2)
   //   printf("Elaborate for.\n");
   if (debug) printf("------------------ forNode:\n");
   if (debug) printTree(forNode);

   ////////////////////////////////
   // get index value node and string
   ////////////////////////////////
   NODE* indexValueNode = copyTree(forNode -> sub -> sub -> next -> sub);
   if (debug) printf("------------------ indexValueNode:\n");
   if (debug) printTree(indexValueNode);
   if (parameterTree -> sub != NULL)
      replaceParameters(indexValueNode, parameterTree);
   string indexValueString = "";
   writer_sv_constant_expression(indexValueString, indexValueNode);
   indexValueString = indexValueString.substr(1);
   if (debug) printf("indexValueString: %s\n", indexValueString.c_str());

   ////////////////////////////////
   // standards
   ////////////////////////////////
   NODE* bodyNode = forNode -> sub -> next -> next -> next;
   NODE* indexNode = getNode(forNode -> sub, G_SI);
   string indexNameString = getSI(indexNode);
   if (debug) printf("indexNameString: %s\n", indexNameString.c_str());
   
   ////////////////////////////////
   // loop
   ////////////////////////////////
   NODE* ptrNode = tmpNode;
   while (1) {
      ////////////////////////////////
      // check execution
      ////////////////////////////////
      NODE* newParameterTree = copyTree(parameterTree);
      addSITree(indexNode, indexValueNode, newParameterTree);
      if (debug) printf("------------------------- newParameterTree:\n");
      if (debug) printSITree(newParameterTree);
      if (debug) printTree(newParameterTree);

      NODE* expressionNode = copyTree(forNode-> sub -> next -> sub);
      if (debug) printf("------------------------- check expressionNode before:\n");
      if (debug) printTree(expressionNode);
      replaceParameters(expressionNode, newParameterTree);
      if (debug) printf("------------------------- check expressionNode mid:\n");
      if (debug) printTree(expressionNode);
      expressionNode = solveEquation(expressionNode);
      if (expressionNode == NULL)
         exit(-1);
      if (debug) printf("------------------------- check expressionNode after:\n");
      if (debug) printTree(expressionNode);
      if (!(sbin2Bool(expressionNode))) {
         deleteTree(expressionNode);
         return true;
      }
            
      ////////////////////////////////
      // execution
      ////////////////////////////////
      if (debug) printf("indexNameString: %s indexValueString: .%s.\n", indexNameString.c_str(), indexValueString.c_str());
      NODE* newBodyNode = copyTree(bodyNode);
      replaceIndexName(newBodyNode, false, indexNameString, indexValueString);
      if (debug) printTree(newBodyNode); 
      NODE* endPtr = newBodyNode;
      while (1) {
         if (endPtr -> next == NULL)
            break;
         endPtr = endPtr -> next;
      }
      endPtr -> next = ptrNode -> next;
      ptrNode -> next = newBodyNode;
      ptrNode = endPtr; 
      
      ////////////////////////////////
      // next index value
      ////////////////////////////////
      NODE* modifyNode = forNode -> sub -> next -> next;
      if (modifyNode -> sub -> id == G_SV_GENVAR_ITERATION_ASSIGNMENT) {
          // check if index is identical ?
         if (modifyNode -> sub -> sub -> next -> sub -> id == G_SV_ASSIGNMENT_OPERATOR_ASSIGN)
            expressionNode = copyTree(modifyNode -> sub -> sub -> next -> next -> sub -> sub);
         else
            expressionNode = copyTree(modifyNode -> sub);
      } else
          // check if index is identical ?
          expressionNode = copyTree(modifyNode -> sub);

      if (debug) printf("------------------------- next expressionNode before:\n");
      if (debug) printTree(expressionNode);
      replaceParameters(expressionNode, newParameterTree);
      if (debug) printf("------------------------- next expressionNode mid:\n");
      if (debug) printTree(expressionNode);
      expressionNode = solveEquation(expressionNode);
      if (expressionNode == NULL)
         exit(-1); //return false;
      if (debug) printf("------------------------- next expressionNode after:\n");
      if (debug) printTree(expressionNode); 
      unsigned maxInt = sbin2Unsigned(expressionNode);
      if (debug) printf("------------------------- maxInt: %d\n", maxInt);
      deleteTree(expressionNode);
      indexValueString = to_string(maxInt);
      indexValueString.append(" ");
      parser_sv_unsigned_number(indexValueString, 0, indexValueNode);
      indexValueString = to_string(maxInt);
      if (debug) printf("------------------------- indexValueString: %s\n", indexValueString.c_str());
      if (debug) printf("------------------------- indexValueNode end:\n");
      if (debug) printTree(indexValueNode);
   }
   exit(-1);
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
/// Collect states in transaction
/////////////////////////////////////////////////////////////////////////////////
void collectTransactionState (NODE* node, 
                              NODE* fsmBag, 
                              NODE* moduleNode,
                              bool *aboveEdge, 
                              NODE* eventTree) {
   bool debug = false;
   if (debug) printf("processTransactionState: %d\n", node -> id);
   if (debug) printTree(node);
   if (debug) printf("------------------------\n");
   if ( (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) ) {
      string conditionName = getSI(node -> sub); 
      if (	(checkTree(conditionName, eventTree)) 	) {
         if (debug) printf("edge found: %s\n", conditionName.c_str());
         *aboveEdge = false;
      }
      if (node -> sub != NULL) 
         collectTransactionState(node -> sub, fsmBag, moduleNode, aboveEdge, eventTree);
   } else
   //////////////////////////////////////////////////////
   // new finite conversion using unique case (state == PARAMETER)
   //////////////////////////////////////////////////////
   if (node -> id == G_PDVL_TRANSACTION_STATEMENT) {
      if (node -> sub != NULL)
      if (node -> sub -> id == G_PDVL_TRANSACTION_FINITE_STATEMENT) { //G_PDVL_TRANSACTION_STATE) {
         NODE* fsmNameNode = node -> sub -> sub -> next;
         bool oneHot = false;
         if (node -> sub -> sub -> next -> id == G_PDVL_TRANSACTION_FINITE_ONE_HOT_KEYWORD) {
            oneHot = true;
            fsmNameNode = fsmNameNode -> next;
         }
         string fsmName = getSI(fsmNameNode);
         if (*aboveEdge) {
            printf("ERR.FSM.NO_EDGE_FOUND: %s\n", fsmName.c_str());
            exit(-1);
         }
         if (debug) printf("------------------------ G_PDVL_TRANSACTION_STATEMENT:\n");
         if (debug) printTree(node);
         NODE* tmpNode = fsmNameNode -> next;
         NODE* stateTree = initNode(0);
         while (1) {
            if (tmpNode -> id == G_PDVL_TRANSACTION_FINITE_CASE_ITEM) { //G_PDVL_TRANSACTION_STATE) {
               string entryName = getSI(tmpNode);
               addSITree(entryName, stateTree);
               if (debug) { 
                  printf("checking state: %s\n", entryName.c_str()); 
               }
               NODE* siNode = getNode(tmpNode, G_SI);
               bool add = true;
               string stateName = getSI(siNode);
               transform(stateName.begin(), stateName.end(), stateName.begin(), ::tolower);
               if ("default" == stateName)
                  add = false;
               else
               if (fsmBag -> sub != NULL) {
                  if (checkSITree(fsmNameNode -> sub -> sub, fsmBag -> sub)) {
                     NODE* thisFSMBag = getSITreeNode(fsmNameNode -> sub -> sub, fsmBag -> sub);
                     if (debug) printf("------------------------\n");
                     if (debug) printTree(thisFSMBag);
                     addSITree(siNode, NULL, thisFSMBag);
                     if (debug) printf("------------------------\n");
                     if (debug) printTree(thisFSMBag);
                     if (debug) printSITree(thisFSMBag);
                     if (oneHot) {
                        thisFSMBag -> id = 1;
                     }
                     add = false;
                  }
               }
               if (add) {                               // there must be a better way
                  NODE* tmpSiNode = initNode(0);
                  if (oneHot)
                     tmpSiNode -> id = 1;
                  addSITree(entryName, tmpSiNode);
                  addSITree(fsmNameNode, tmpSiNode, fsmBag);
               }
            }
            if (tmpNode -> next == NULL)
               break;
            tmpNode = tmpNode -> next;
         }    
         if (debug) printf("------------------------\n");
         if (debug) printSITree(stateTree);
      } else
      if (node -> sub != NULL) 
         collectTransactionState(node -> sub, fsmBag, moduleNode, aboveEdge, eventTree);
   } else                                           
   if (node -> sub != NULL) 
      collectTransactionState(node -> sub, fsmBag, moduleNode, aboveEdge, eventTree);
   if (node -> next != NULL) 
      collectTransactionState(node -> next, fsmBag, moduleNode, aboveEdge, eventTree);
}
/////////////////////////////////////////////////////////////////////////////////
///  Convert emit statements of a FSM
/////////////////////////////////////////////////////////////////////////////////
void finiteStateEmitConversion (NODE* node, 
                                NODE* fsmBag, 
                                NODE* moduleNode,
                                bool *aboveEdge, 
                                NODE* eventTree) {
   bool debug = false;
   if (debug) printf("processTransactionState: %d\n", node -> id);
   if (debug) printTree(node);
   if (debug) printf("------------------------\n");
   if ( (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) ) {
      string conditionName = getSI(node -> sub); 
      if (	(checkTree(conditionName, eventTree)) 	) {
         if (debug) printf("edge found: %s\n", conditionName.c_str());
         *aboveEdge = false;
      }
      if (node -> sub != NULL) 
         finiteStateEmitConversion(node -> sub, fsmBag, moduleNode, aboveEdge, eventTree);
   } else
   //////////////////////////////////////////////////////
   // new finite conversion using unique case (state == PARAMETER)
   //////////////////////////////////////////////////////
   if (node -> id == G_PDVL_TRANSACTION_STATEMENT) {
      if (node -> sub)
      if (node -> sub -> id == G_PDVL_TRANSACTION_FINITE_STATEMENT) {
         NODE* fsmNameNode = node -> sub -> sub -> next;
         string fsmName = getSI(fsmNameNode);
         if (node -> sub -> sub -> next -> id == G_PDVL_TRANSACTION_FINITE_ONE_HOT_KEYWORD) {
            fsmNameNode = fsmNameNode -> next;
         }
         if (*aboveEdge) {
            printf("ERR.FSM.NO_EDGE_FOUND: %s\n", fsmName.c_str());
            exit(-1);
         }
         if (debug) printf("------------------------ G_PDVL_TRANSACTION_STATEMENT:\n");
         if (debug) printTree(node);
         if (debug) printf("------------------------ fsmNameNode -> sub -> sub\n");
         if (debug) printTree(fsmNameNode -> sub -> sub);
         if (debug) printf("------------------------\n");
         if (debug) printTree(fsmBag);
         NODE* stateTree = getSITreeNode(fsmNameNode -> sub -> sub, fsmBag -> sub);
         if (debug) printf("------------------------\n");
         if (debug) printTree(stateTree);
         stateEmitToStateAssignment(node -> sub -> sub, fsmName, stateTree, moduleNode);
         string line = "unique case endcase";              
         if (debug) printf("   %s\n", line.c_str());
         // parse to caseNode
         NODE* caseNode = initNode(G_TMP_TRANSACTION_CASE_STATEMENT);
         unsigned ptr = parser_tmp_transaction_case_statement(line, 0, caseNode);                  
         if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
         if (debug) printf("------------------------\n");
         if (debug) printTree(caseNode);
         // case case items ...   
         NODE* caseLastItemNode = caseNode -> sub -> next;
         NODE* tmpNode = node -> sub -> sub -> next -> next;
         while (1) {
            if (tmpNode -> id == G_PDVL_TRANSACTION_FINITE_CASE_ITEM) {
               // add a new slice to the new case item
               string stateName = getSI(tmpNode -> sub);
               transform(stateName.begin(), stateName.end(), stateName.begin(), ::tolower);
               string entryName = "";
               if (stateName == "default") {  
                  entryName.append(stateName);
               } else {
                  entryName.append(fsmName);
                  entryName.append(" == ");
                  string paramName = "";
                  paramName.append(fsmName);
                  paramName.append("_state_");
                  paramName.append(stateName);
                  transform(paramName.begin(), paramName.end(), paramName.begin(), ::toupper);
                  entryName.append(paramName);
               }
               entryName.append(" : { } "); 
               if (debug) printf("new case slice for item: %s\n", entryName.c_str());
               
               // add a new slice to the new case item
               NODE* caseItemNode = initNode(0);
               ptr = parser_tmp_transaction_case_item(entryName, 0, caseItemNode);                  
               if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
               if (debug) printf("-------------------------------------- caseItemNode:\n");
               if (debug) printTree(caseItemNode);

               if (stateName == "default") {
                  // add the original case item body to the new case item
                  caseItemNode -> sub -> sub = tmpNode -> sub -> next;
               } else {                                                       
                  // add the original case item body to the new case item
                  caseItemNode -> sub -> sub -> next = tmpNode -> sub -> next;
               }
                  caseLastItemNode -> next = caseItemNode;
                  caseLastItemNode = caseItemNode;
            }
            if (tmpNode -> next == NULL)
               break;
            tmpNode = tmpNode -> next;
         }    
         // append new case slice
         node -> sub = caseNode;
         if (debug) {
            printf("------------------------ final case node\n");
            printTree(node -> sub);
            string caseString = "";
            writer_tmp_transaction_case_statement(caseString, node -> sub -> sub);
            printf("caseString: %s\n", caseString.c_str());
         }
      } else
      if (node -> sub != NULL) 
         finiteStateEmitConversion(node -> sub, fsmBag, moduleNode, aboveEdge, eventTree);
   } else                                           
   if (node -> sub != NULL) 
      finiteStateEmitConversion(node -> sub, fsmBag, moduleNode, aboveEdge, eventTree);
   if (node -> next != NULL) 
      finiteStateEmitConversion(node -> next, fsmBag, moduleNode, aboveEdge, eventTree);
}
/////////////////////////////////////////////////////////////////////////////////
/// Convert states of FSM to parameters
/////////////////////////////////////////////////////////////////////////////////
unsigned finiteTreeToParameter (unsigned cnt, 
                                string &header, 
                                NODE* node, 
                                NODE* moduleNode) {
   bool debug = false;
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      thisHeader.append(node2String(node));
      
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0)
            cnt = finiteTreeToParameter(cnt, thisHeader, node -> sub, moduleNode);
         else {
            if (debug) printf("   %s %x\n", thisHeader.c_str(), cnt); 
            NODE* stateTree = node -> sub -> sub;
            string newHeader = thisHeader;
            newHeader.append("_state_");
            if (debug) printf("----------------------- states\n");
            if (debug) printTree(stateTree);
            if (debug) printf("----------------------- states\n");
            if (debug) printSITree(stateTree);
            bool oneHot = false;
            if (stateTree -> id == 1)
               oneHot = true;
            unsigned stateCNT = stateTreeToParameter(0, oneHot, newHeader, stateTree, moduleNode);

            int pwr = 0;
            if (oneHot) {
               pwr = stateCNT - 1;
            } else {
               int log2 = 1;
               while (log2 < stateCNT) { 
                  log2 *= 2; 
                  if (log2 < stateCNT) 
                     pwr += 1; }
            }
 
            //////////////////////////////////////////////
            // check for existing register definition
            //////////////////////////////////////////////
            bool found = false;
            if (debug) printf("--------------------------------\n");
            if (debug) printTree(0, 4, moduleNode);
            NODE* moduleRegNode = getNodeSubLevel(moduleNode, DB_MODULE_REGISTERS);
            if (moduleRegNode != NULL) {
               NODE* clRegNode = moduleRegNode -> sub;
               while (1) {
                  NODE* subRegNode = clRegNode -> sub;
                  while (1) {
                     string thisParam = getSI(subRegNode -> sub);
                     if (debug) printf("thisParam: %s\n", thisParam.c_str());
                     if (thisParam == thisHeader) {
                        if (debug) printf("found\n");
                        found = true;
                        break;
                     }
                     if (subRegNode -> next == NULL)
                        break;
                     subRegNode = subRegNode -> next;
                  }
                  if (found)
                     break;
                  if (clRegNode -> next == NULL)
                     break;
                  clRegNode = clRegNode -> next;
               }
            }
            if (!(found)) {
               string line = "reg ";              
               line.append("[ ");
               line.append(to_string(pwr));
               line.append(" : 0 ] ");
               line.append(thisHeader);
               line.append(" ;");
               if (debug) printf("   %s\n", line.c_str());
 
               NODE* regNode = initNode(0);
               int ptr = parser_pdvl_reg_declaration(line, 0, regNode);                  
               NODE* decNode = initNode(G_PDVL_REG_DECLARATION);
               NODE* newNode = initNode(G_PDVL_IDENTIFIER_LIST); 
               newNode -> sub = regNode -> sub -> sub -> sub -> next;
               decNode -> sub = newNode;
               decNode -> sub -> next = initNode(DB_SIGNAL_TYPE);
               decNode -> sub -> next -> sub = regNode -> sub -> sub -> sub;
               decNode -> sub -> next -> sub -> next = NULL;
               joinConstruct(moduleNode, decNode, 0, DB_MODULE_REGISTERS);
            }
            cnt++;
            if (node -> sub -> next != NULL)
               cnt = finiteTreeToParameter(cnt, thisHeader, node -> sub -> next, moduleNode); 
         } 
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
   return cnt;
}

/////////////////////////////////////////////////////////////////////////////////
/// Extract parameters of FSM
/////////////////////////////////////////////////////////////////////////////////
unsigned stateTreeToParameter (unsigned cnt, 
                               bool oneHot, 
                               string &header, 
                               NODE* node, 
                               NODE* moduleNode) {
   bool debug = false;
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      thisHeader.append(node2String(node));
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0)
            cnt = stateTreeToParameter(cnt, oneHot, thisHeader, node -> sub, moduleNode);
         else { 
            string newParameterName = thisHeader;
            transform(newParameterName.begin(), newParameterName.end(), newParameterName.begin(), ::toupper);
            //////////////////////////////////////////////
            // check for existing parameter
            //////////////////////////////////////////////
            bool found = false;
            if (debug) printf("--------------------------------\n");
            if (debug) printTree(0, 4, moduleNode);
            NODE* moduleParamNode = getNodeSubLevel(moduleNode, DB_MODULE_PARAMETER);
            if (moduleParamNode != NULL) {
               if (debug) printf("--------------------------------\n");
               if (debug) printTree(moduleParamNode -> sub);
               if (debug) printf("newParameterName: %s\n", newParameterName.c_str());
               NODE* clParamNode = moduleParamNode -> sub;
               while (1) {
                  NODE* subParamNode = clParamNode -> sub;
                  while (1) {
                     string thisParam = getSI(subParamNode -> sub);
                     if (debug) printf("thisParam: %s\n", thisParam.c_str());
                     if (thisParam == newParameterName) {
                        if (debug) printf("found\n");
                        found = true;
                        break;
                     }
                     if (subParamNode -> next == NULL)
                        break;
                     subParamNode = subParamNode -> next;
                  }
                  if (found)
                     break;
                  if (clParamNode -> next == NULL)
                     break;
                  clParamNode = clParamNode -> next;
               }
            }
            if (!(found)) {
               string line = "parameter ";              
               line.append(newParameterName);
               line.append(" = ");
               if (oneHot) {
                  line.append("1'b1 << ");
               }
               line.append(to_string(cnt));
               line.append("; ");
               if (debug) printf("   %s\n", line.c_str());

               NODE* returnNode = initNode(0);
               int ptr = parser_sv_parameter_declaration(line, 0, returnNode);                  
               if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
               if (debug) printTree(returnNode);
            
               joinConstruct(moduleNode, returnNode, 0, DB_MODULE_PARAMETER);
            }
            cnt++;
            if (node -> sub -> next != NULL)
               cnt = stateTreeToParameter(cnt, oneHot, thisHeader, node -> sub -> next, moduleNode); } }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
   return cnt;
}
/////////////////////////////////////////////////////////////////////////////////
/// Convert new state assignments of a FSM
/////////////////////////////////////////////////////////////////////////////////
void stateEmitToStateAssignment (NODE* node, 
                                 string &transName, 
                                 NODE* stateTree, 
                                 NODE* moduleNode) {
   bool debug = false;
   if (debug) printf("calling stateEmitToStateAssignment: %d\n", node -> id);
   if (node -> id == G_PDVL_TRANSACTION_STATEMENT) {
      if (node -> sub != NULL)
      if (node -> sub -> id == G_PDVL_EMIT) {
         string entryName = getSI(node -> sub);
         if (debug) printf("checking entry a: %s\n", entryName.c_str());
         if (checkTree(entryName, stateTree))  {
            if (debug) printTree(node);
            if (debug) printf("found state: %s <-----------------\n", entryName.c_str());
            string line = transName;
            line.append(" <= ");
            string nextState = transName;
            nextState.append("_state_");
            nextState.append(entryName);
            transform(nextState.begin(), nextState.end(), nextState.begin(), ::toupper);
            line.append(nextState);
            line.append(";");
            if (debug) printf("%s <-----------------\n", line.c_str());

            NODE* returnNode = initNode(0);
            int ptr = parser_sv_nonblocking_assignment(line, 0, returnNode);                  
            if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
            if (debug) printTree(returnNode);
            
            node -> sub = returnNode;
            
            return;
         }  
      } else
      if (node -> sub != NULL) 
         stateEmitToStateAssignment(node -> sub, transName, stateTree, moduleNode);
   } else                                           
   if (node -> sub != NULL) 
      stateEmitToStateAssignment(node -> sub, transName, stateTree, moduleNode);
   if (node -> next != NULL) 
      stateEmitToStateAssignment(node -> next, transName, stateTree, moduleNode);
}
/////////////////////////////////////////////////////////////////////////////////
/// Handle propagate statement
/////////////////////////////////////////////////////////////////////////////////
void handlePropagateStatement (NODE* node, 
                               unsigned insert) {
   bool debug = false;
   if (debug) printf("Handle propagate statement %d.\n", node -> id);
   //////////////////////////////////////////////////////////
   //	adapt insert
   //////////////////////////////////////////////////////////
   if (node -> id == G_PDVL_TRANSACTION_UNIQUE_SINGLE)
      node -> id = G_PDVL_TRANSACTION_UNIQUE_LIST;
   else if (node -> id == G_PDVL_TRANSACTION_UNIQUE0_SINGLE)
      node -> id = G_PDVL_TRANSACTION_UNIQUE0_LIST;
   if (	(node -> id == G_PDVL_TRANSACTION_PRIORITY_LIST) |
   		(node -> id == G_PDVL_TRANSACTION_UNIQUE_LIST)   |
        (node -> id == G_PDVL_TRANSACTION_UNIQUE0_LIST)  ) {
      if (node -> sub != NULL) {
         if (node -> sub -> id == G_PDVL_PRIORITY_UNIQUE_PROPAGATE) {
            node -> sub = node -> sub -> next;
            if (node -> id == G_PDVL_TRANSACTION_PRIORITY_LIST)
               insert = 1;
   		    else if (node -> id == G_PDVL_TRANSACTION_UNIQUE_LIST)
               insert = 2;
            else if (node -> id == G_PDVL_TRANSACTION_UNIQUE0_LIST)
               insert = 3;
         } else 
         if ( (node -> id == G_PDVL_TRANSACTION_PRIORITY_LIST) &
              (insert != 1)                               )
            insert = 0;
   		 else 
   		 if ( (node -> id == G_PDVL_TRANSACTION_UNIQUE_LIST) &
              (insert != 2)                             )
            insert = 0;
         else 
         if ( (node -> id == G_PDVL_TRANSACTION_UNIQUE0_LIST) &
              (insert != 3)                              )
            insert = 0;
      }
   } else
   //////////////////////////////////////////////////////////
   //	rare case of a single at statement
   //////////////////////////////////////////////////////////
   if (	(node -> id == G_PDVL_TRANSACTION_AT_STATEMENT) &
        (insert > 0)                               ) {
      NODE* entryNode = initNode(G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY);
      entryNode -> sub = node -> sub;
      node -> sub = entryNode;
      if (insert == 1)
         node -> id = G_PDVL_TRANSACTION_PRIORITY_LIST;
      if (insert == 2)
         node -> id = G_PDVL_TRANSACTION_UNIQUE_LIST;
      if (insert == 3)
         node -> id = G_PDVL_TRANSACTION_UNIQUE0_LIST;
      if (debug) printTree(node);
   } else
   //////////////////////////////////////////////////////////
   //	Below G_PDVL_TRANSACTION_STATEMENT:
   //      join multiple at single statements
   //	   combine multiple single else statements
   //////////////////////////////////////////////////////////
   if (	(node -> id == G_PDVL_TRANSACTION_STATEMENT) &
        (insert > 0)                       ) {
      if (node -> sub != NULL) {
         NODE* listEntryNode = node -> sub;
         if (listEntryNode -> id == G_PDVL_TRANSACTION_AT_STATEMENT) {
            if (listEntryNode -> sub != NULL) {
               //////////////////////////////////////////////////////////
               //	join multiple at single statements
               //////////////////////////////////////////////////////////
               if (listEntryNode -> sub -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) {
                  // handle first entry
                  NODE* listNode = initNode(0);
                  if (insert == 1)
                     listNode -> id = G_PDVL_TRANSACTION_PRIORITY_LIST;
                  if (insert == 2)
                     listNode -> id = G_PDVL_TRANSACTION_UNIQUE_LIST;
                  if (insert == 3)
                     listNode -> id = G_PDVL_TRANSACTION_UNIQUE0_LIST;
                  NODE* entryNode = initNode(G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY);
                  listNode -> sub = entryNode;
                  entryNode -> sub = node -> sub -> sub;
                  node -> sub = listNode;
                  // continue propagate 
                  handlePropagateStatement(entryNode -> sub, insert);
                  // handle next entries
                  if (node -> next != NULL) {
                     if (node -> next -> id == G_PDVL_TRANSACTION_STATEMENT)
                     if (node -> next -> sub != NULL)
                     if (node -> next -> sub -> id == G_PDVL_TRANSACTION_AT_STATEMENT) {
                        entryNode = initNode(G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY);
                        entryNode -> sub = node -> next -> sub -> sub;
                        listNode -> sub -> next = entryNode;
                        node -> next = NULL;
                        // continue propagate 
                        handlePropagateStatement(entryNode -> sub, insert);
                     }
                  }
               } else
               //////////////////////////////////////////////////////////
               //	combine multiple single else statements
               //////////////////////////////////////////////////////////
               if (listEntryNode -> sub -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) {
                  if (debug) printf("--------------------\n");
                  if (debug) printTree(node);
                  NODE* tmpNode = listEntryNode -> sub -> sub -> sub -> next -> next;
                  NODE* listNode = initNode(0);
                  if (insert == 1)
                     listNode -> id = G_PDVL_TRANSACTION_PRIORITY_LIST;
                  if (insert == 2)
                     listNode -> id = G_PDVL_TRANSACTION_UNIQUE_LIST;
                  if (insert == 3)
                     listNode -> id = G_PDVL_TRANSACTION_UNIQUE0_LIST;
                  NODE* entryNode = initNode(G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY);
                  entryNode -> sub = node -> sub -> sub -> sub;
                  entryNode -> sub -> id = G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT;
                  entryNode -> sub -> sub -> next -> next = NULL;
                  listNode -> sub = entryNode;
                  node -> sub = listNode;
                  while (tmpNode -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) {
                     NODE* tmpNode2 = tmpNode;
                     tmpNode = tmpNode -> sub -> sub -> next -> next;
                     tmpNode2 -> id = G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY;
                     tmpNode2 -> sub -> id = G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT;
                     tmpNode2 -> sub -> sub -> next -> next = NULL;
                     entryNode -> next = tmpNode2;
                     entryNode = tmpNode2;
                     if (tmpNode == NULL)
                        break;
                  }
                  if (tmpNode != NULL)
                  if (tmpNode -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) {
                     NODE* tmpNode2 = initNode(G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY);
                     tmpNode2 -> sub = tmpNode;
                     entryNode -> next = tmpNode2;
                  }
                  if (debug) printf("--------------------\n");
                  if (debug) printTree(node);
                  return;
               }
            }
         }
      }        
      if (debug) printf("--------------------\n");
      if (debug) printTree(node);
      return;
   } else
   //////////////////////////////////////////////////////////
   //	combine multiple single else statements
   //////////////////////////////////////////////////////////
   if (	(node -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) &
        (insert > 0)                                           ) {
   } else
   if (	(node -> id == G_SI) )
      return;
   if (node -> sub != NULL) 
      handlePropagateStatement(node -> sub, insert);
   if (node -> next != NULL) 
      handlePropagateStatement(node -> next, insert);
}
/////////////////////////////////////////////////////////////////////////////////
/// Merge transactions
/////////////////////////////////////////////////////////////////////////////////
bool mergeTransaction (NODE* node, 
                       NODE* transactionTree, 
                       NODE* mergedTransactionsTree, 
                       NODE* moduleNode) {
   bool debug = false;
   if (debug) printf("-------------------------------- node:\n");
   if (debug) printTree(node);
   if (debug) printf("Merging transactions %d.\n", node -> id);
   if (debug) printf("-------------------------------- transactionTree:\n");
   if (debug) printSITree(transactionTree);
   bool found = false;
   if (	(node -> id == G_PDVL_TRANSACTION_STATEMENT)                  | 
        (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY) ) {
      if (node -> sub != NULL)
      if (node -> sub -> id == G_PDVL_EMIT) {
         string entryName = getSI(node -> sub);
         if (debug) printf("checking entry: %s\n", entryName.c_str());
         NODE* emitNameNode = getNode(node -> sub, G_SI);
         if (debug) printTree(emitNameNode);
         NODE* emitTransNode = getSITreeNode(emitNameNode -> sub, transactionTree -> sub);
         if (emitTransNode != NULL) { //checkSITree(emitNameNode -> sub, transactionTree -> sub)) {
            addSITree(emitNameNode, NULL, mergedTransactionsTree);
            if (debug) printf("Merging: %s\n", entryName.c_str());
            if (debug) printf("------------------------------------------------\n");
            if (debug) printf("------------------------ start node\n");
            if (debug) printTree(node);
            if (debug) printf("------------------------ emitTransNode\n");
            if (debug) printTree(emitTransNode);
            emitTransNode = copyTree(emitTransNode);
            node -> sub = emitTransNode -> sub;
            if (emitTransNode -> next != NULL) {
               NODE* tmpNode = emitTransNode;
               while (tmpNode -> next != NULL)
                  tmpNode = tmpNode -> next;
               tmpNode -> next = node -> next;
               node -> next = emitTransNode -> next;
            }
            if (debug) printf("------------------------ result node\n");
            if (debug) printTree(node);
            if (mergeTransaction(node, transactionTree, mergedTransactionsTree, moduleNode))
               found = true;
         }
      } else
      if (node -> sub != NULL) 
         if (mergeTransaction(node -> sub, transactionTree, mergedTransactionsTree, moduleNode))
            found = true;
   }                                          
   if (node -> sub != NULL) 
      if (mergeTransaction(node -> sub, transactionTree, mergedTransactionsTree, moduleNode))
         found = true;
   if (node -> next != NULL) 
      if (mergeTransaction(node -> next, transactionTree, mergedTransactionsTree, moduleNode))
         return true;
   return found;
}
/////////////////////////////////////////////////////////////////////////////////
/// Merge constructs
/////////////////////////////////////////////////////////////////////////////////
void mergeConstructs (NODE* node) {
   bool debug = false;
   if (debug) printf("Merging constructs %d.\n", node -> id);
   if (	(node -> id == G_PDVL_TRANSACTION_BODY) ) {
      if (node -> sub != NULL) {
         NODE* aNode = node -> sub;
         while (true) { 
            if (aNode -> sub == NULL)
               break;
            if (aNode -> next == NULL)
               break;
            NODE* bNode = aNode -> next;
            if (bNode -> sub == NULL)
               break;
            
            bool progessANode = true;
            //////////////////////////////////////////
            // Merge unique or unique0: always merge !!!
            //////////////////////////////////////////
            if ( ( (aNode -> sub -> id == G_PDVL_TRANSACTION_UNIQUE_LIST) &
                   (bNode -> sub -> id == G_PDVL_TRANSACTION_UNIQUE_LIST) )  |
                 ( (aNode -> sub -> id == G_PDVL_TRANSACTION_UNIQUE0_LIST) &
                   (bNode -> sub -> id == G_PDVL_TRANSACTION_UNIQUE0_LIST) ) ) {
               if (debug) printf("------------ node\n");
               if (debug) printTree(node);
               /////////////////////////////////////////////////////
               //  go through all bSub entries
               /////////////////////////////////////////////////////
               NODE* bSubNode = bNode -> sub -> sub;
               while (true) { 
                  if (bSubNode -> sub == NULL)
                     break;
                  NODE* bConditionNode = bSubNode -> sub -> sub;
                  if (debug) printf("------------ bConditionNode\n");
                  if (debug) printTree(bConditionNode);
                  NODE* aSubNode = aNode -> sub -> sub;
                  bool found = false;
                  if (bConditionNode -> sub == NULL) // empty default
                     found = true;
                  else
                  while (1) {
                     if (aSubNode -> sub == NULL)
                        break;
                        NODE* aConditionNode = aSubNode -> sub -> sub;
                        if (debug) printf("------------ aConditionNode\n");
                        if (debug) printTree(aConditionNode);
                        //////////////////////////////////////////
                        // Check both default
                        //////////////////////////////////////////
                        if (aSubNode -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY) {
                           if (bSubNode -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY) {
                              if (reportLevel >= 2)
                                 printf("Merging constructs (default).\n");
                              NODE* aTransactionBodyNode = aConditionNode;
                              NODE* bTransactionBodyNode = bConditionNode;
                              if (aTransactionBodyNode -> sub == NULL) {
                                 aTransactionBodyNode -> sub = bTransactionBodyNode -> sub;
                              } else {
                                 NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                                 while (1) {
                                    if (aTransactionBodySubNode -> next == NULL)
                                       break;
                                    aTransactionBodySubNode = aTransactionBodySubNode -> next;
                                 }
                                 aTransactionBodySubNode -> next = bTransactionBodyNode -> sub;
                              }
                              found = true;
                              if (reportLevel >= 2)
                                 printf("Merging constructs done.\n");
                              if (debug) printf("------------ node\n");
                              if (debug) printTree(node);
                              break;
                           }
                        //////////////////////////////////////////
                        // Check same condition
                        //////////////////////////////////////////
                        } else
                        if (checkTree(aConditionNode -> sub, bConditionNode -> sub)) {
                           if (debug) printf("Merging constructs.\n");
                           NODE* aTransactionBodyNode = aConditionNode -> next;
                           NODE* bTransactionBodyNode = bConditionNode -> next;
                           if (aTransactionBodyNode -> sub == NULL)
                              aTransactionBodyNode -> sub = bTransactionBodyNode -> sub; 
                           else {
                              NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                              while (1) {
                                 if (aTransactionBodySubNode -> next == NULL)
                                    break;
                                 aTransactionBodySubNode = aTransactionBodySubNode -> next;
                              }
                              aTransactionBodySubNode -> next = bTransactionBodyNode -> sub; 
                           }
                           found = true;
                           break;
                        }
                     if (aSubNode -> next == NULL)
                        break;
                     aSubNode = aSubNode -> next;   
                  }
                  if (!(found)) {
                     if (debug) printf("Appending constructs.\n");
                     NODE* newEntryNode = copyTree(bSubNode -> sub);
                     NODE* newNode = initNode(G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY);
                     newNode -> sub = newEntryNode;
                     while (true) {
                        if (aSubNode -> next == NULL)
                           break;
                        aSubNode = aSubNode -> next;
                     }
                     aSubNode -> next = newNode;
                  }
                  if (bSubNode -> next == NULL)
                     break;
                  bSubNode = bSubNode -> next;
               }   
               /////////////////////////////////////////////////////
               //  handling bNode default entry
               /////////////////////////////////////////////////////
               if (bNode -> sub -> next != NULL) {
                  if (aNode -> sub -> next == NULL)
                     aNode -> sub -> next = copyTree(bNode -> sub -> next);
                  else {
                     NODE* aTransactionBodyNode = aNode -> sub -> next -> sub -> sub;
                     NODE* bTransactionBodyNode = bNode -> sub -> next -> sub -> sub;
                     if (aTransactionBodyNode -> sub == NULL)
                        aTransactionBodyNode -> sub = bTransactionBodyNode -> sub; 
                     else {
                        NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                        while (1) {
                           if (aTransactionBodySubNode -> next == NULL)
                              break;
                           aTransactionBodySubNode = aTransactionBodySubNode -> next;
                        }
                        aTransactionBodySubNode -> next = bTransactionBodyNode -> sub; 
                     }
                  }
               }
               // always merge !!!
               progessANode = false;
               aNode -> next = aNode -> next -> next;
               if (debug) printf("------------ done\n");
               if (debug) printTree(node);
            } else
            //////////////////////////////////////////
            // Merge priority: merge when identical !!!
            ////////////////////////////////////////// 
            if ( (aNode -> sub -> id == G_PDVL_TRANSACTION_PRIORITY_LIST) &
                 (bNode -> sub -> id == G_PDVL_TRANSACTION_PRIORITY_LIST) ) {
               if (debug) printf("------------ priority node\n");
               if (debug) printTree(node);
               NODE* bSubNode = bNode -> sub -> sub;
               NODE* aSubNode = aNode -> sub -> sub;
               bool merge = true;
               while (true) { 
                  if (aSubNode -> sub == NULL)
                     break;
                  if (bSubNode -> sub == NULL) {
                     merge = false;
                     break;
                  }
                  if (aSubNode -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY) {
                  } else {
                     NODE* bConditionNode = bSubNode -> sub -> sub;
                     if (debug) printf("------------ check bConditionNode\n");
                     if (debug) printTree(bConditionNode);
                     NODE* aConditionNode = aSubNode -> sub -> sub;
                     if (debug) printf("------------ check aConditionNode\n");
                     if (debug) printTree(aConditionNode);
                     //////////////////////////////////////////
                     // Check same condition
                     //////////////////////////////////////////
                     if (checkTree(aConditionNode -> sub, bConditionNode -> sub)) {
                     } else {
                        merge = false;
                        break;
                     }
                  }   
                  //////////////////////////////////
                  // same conditions => default is don't care
                  //////////////////////////////////
                  if ( (aSubNode -> next == NULL) &
                       (bSubNode -> next == NULL) ) {
                     //merge = true;
                     break;
                  } else
                  //////////////////////////////////
                  // different conditions => both without default !!!
                  //////////////////////////////////
                  if ( (aSubNode -> next == NULL) |
                       (bSubNode -> next == NULL) ) {
                     if (bNode -> sub -> next == NULL)
                     if (aNode -> sub -> next == NULL)
                        merge = true;
                     break;
                  }
                  aSubNode = aSubNode -> next;   
                  bSubNode = bSubNode -> next;
               }
               if (debug) printf("merge: %d\n", merge);

               if (merge) {
                  bSubNode = bNode -> sub -> sub;
                  aSubNode = aNode -> sub -> sub;
                  while (true) { 
                     if (bSubNode -> sub == NULL)
                        break;
                     NODE* bConditionNode = bSubNode -> sub -> sub;
                     if (debug) printf("------------ bConditionNode\n");
                     if (debug) printTree(bConditionNode);
                     NODE* aSubNode = aNode -> sub -> sub;
                     bool found = false; 
                     if (bConditionNode -> sub == NULL) // empty default
                        found = true;
                     else
                     while (1) {
                        if (aSubNode -> sub == NULL)
                           break;
                           NODE* aConditionNode = aSubNode -> sub -> sub;
                           if (debug) printf("------------ aConditionNode\n");
                           if (debug) printTree(aConditionNode);
                           //////////////////////////////////////////
                           // Check both default
                           //////////////////////////////////////////
                           if (aSubNode -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY) {
                              if (bSubNode -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY) {
                                 if (reportLevel >= 2)
                                    printf("Merging priority constructs (default).\n");
                                 NODE* aTransactionBodyNode = aConditionNode;
                                 NODE* bTransactionBodyNode = bConditionNode;
                                 if (aTransactionBodyNode -> sub == NULL) {
                                    aTransactionBodyNode -> sub = bTransactionBodyNode -> sub;
                                 } else {
                                    NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                                    while (1) {
                                       if (aTransactionBodySubNode -> next == NULL)
                                          break;
                                       aTransactionBodySubNode = aTransactionBodySubNode -> next;
                                    }
                                    aTransactionBodySubNode -> next = bTransactionBodyNode -> sub;
                                 }
                                 found = true;
                                 if (debug) printf("Merging constructs done.\n");
                                 if (debug) printf("------------ node\n");
                                 if (debug) printTree(node);
                                 //exit(-1);
                                 break;
                              }
                           //////////////////////////////////////////
                           // Check same condition
                           //////////////////////////////////////////
                           } else 
                           if (checkTree(aConditionNode -> sub, bConditionNode -> sub)) {
                              if (debug) printf("Merging priority constructs.\n");
                              NODE* aTransactionBodyNode = aConditionNode -> next;
                              NODE* bTransactionBodyNode = bConditionNode -> next;
                              if (0) //aTransactionBodyNode -> sub == NULL)
                                 aTransactionBodyNode -> sub = bTransactionBodyNode -> sub; 
                              else {
                                 NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                                 while (1) {
                                 if (aTransactionBodySubNode -> next == NULL)
                                       break;
                                    aTransactionBodySubNode = aTransactionBodySubNode -> next;
                                 }
                                 aTransactionBodySubNode -> next = bTransactionBodyNode -> sub; 
                              }
                              found = true;
                              break;
                           }
                        if (aSubNode -> next == NULL)
                           break;
                        aSubNode = aSubNode -> next;   
                     }
                     if (!(found)) {
                        if (debug) printf("Appending constructs.\n");
                        NODE* newEntryNode = copyTree(bSubNode -> sub);
                        NODE* newNode = initNode(G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY);
                        newNode -> sub = newEntryNode;
                        while (true) {
                           if (aSubNode -> next == NULL)
                              break;
                           aSubNode = aSubNode -> next;
                        }
                        aSubNode -> next = newNode;
                     }
                     if (bSubNode -> next == NULL)
                        break;
                     bSubNode = bSubNode -> next;
                  }
                  if (debug) printf("cont\n");
                  /////////////////////////////////////////////////////
                  //  handling bNode default entry
                  /////////////////////////////////////////////////////
                  if (bNode -> sub -> next != NULL) {
                     if (aNode -> sub -> next == NULL)
                        exit(-1); // Shouldn't happen, aNode -> sub -> next = copyTree(bNode -> sub -> next);
                     else {
                        NODE* aTransactionBodyNode = aNode -> sub -> next -> sub -> sub;
                        NODE* bTransactionBodyNode = bNode -> sub -> next -> sub -> sub;
                        if (aTransactionBodyNode -> sub == NULL)
                           aTransactionBodyNode -> sub = bTransactionBodyNode -> sub; 
                        else {
                           NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                           while (1) {
                              if (aTransactionBodySubNode -> next == NULL)
                                 break;
                              aTransactionBodySubNode = aTransactionBodySubNode -> next;
                           }
                           aTransactionBodySubNode -> next = bTransactionBodyNode -> sub; 
                        }
                     }
                  }
                  // always merge !!!
                  progessANode = false;
                  aNode -> next = aNode -> next -> next;
                  if (debug) printf("------------ priority done\n");
                  if (debug) printTree(node);
                }   
            } else
            //////////////////////////////////////////
            // Merge TRANSACTION_CASE_statement
            ////////////////////////////////////////// 
            if ( (aNode -> sub -> id == G_TMP_TRANSACTION_CASE_STATEMENT) &
                 (bNode -> sub -> id == G_TMP_TRANSACTION_CASE_STATEMENT) ) {
               if (debug) printf("------------\n");
               if (debug) printTree(node);
               if (aNode -> sub -> sub != NULL)
               if (bNode -> sub -> sub != NULL) {
                  if ( (aNode -> sub -> sub -> id == G_SV_UNIQUE_PRIORITY) &
                       (bNode -> sub -> sub -> id == G_SV_UNIQUE_PRIORITY) ) {
                     //////////////////////////////////////////
                     // Consecutive case statements with identical uni[0]\prio statements => try to merge
                     ////////////////////////////////////////// 
                     if (aNode -> sub -> sub -> sub -> id == 
                         bNode -> sub -> sub -> sub -> id) {
                        if (debug) printf("found identical uni, prio statements\n");
                        //////////////////////////////////////////
                        // Test for same case transaction expression
                        ////////////////////////////////////////// 
                        if (1) {
                           if (debug) printf("found identical uni, prio statements and keyword\n");
                           NODE* bSubNode = bNode -> sub -> sub -> next -> next -> next;
                           NODE* aSubNode = aNode -> sub -> sub -> next -> next -> next;
                           bool merge = true;
                           //////////////////////////////////////////
                           // In case of priority, check order, break if no merge
                           //////////////////////////////////////////
                           if (aNode -> sub -> sub -> sub -> id == G_SV_UNIQUE_PRIORITY_PRIORITY) {
                              //////////////////////////////////////////
                              // Merge priority: merge when identical !!!
                              ////////////////////////////////////////// 
                              merge = false;
                              //exit(-1);
                              while (true) { 
                                 if (aSubNode -> sub == NULL)
                                    break;
                                 if (bSubNode -> sub == NULL)
                                    break;
                                 NODE* bConditionNode = bSubNode -> sub -> sub; 
                                 if (debug) printf("------------ bConditionNode\n");
                                 if (debug) printTree(bConditionNode);
                                 NODE* aConditionNode = aSubNode -> sub -> sub; 
                                 if (debug) printf("------------ aConditionNode\n");
                                 if (debug) printTree(aConditionNode);
                                 //////////////////////////////////////////
                                 // Check same condition
                                 //////////////////////////////////////////
                                 if (checkTree(aConditionNode -> sub, bConditionNode -> sub)) {
                                 } else
                                    break;
                                 if ( (aSubNode -> next == NULL) |
                                      (bSubNode -> next == NULL) ) {
                                    merge = true;
                                    break;
                                 }
                                 aSubNode = aSubNode -> next;   
                                 bSubNode = bSubNode -> next;
                              }
                           }   
                           //////////////////////////////////////////
                           // Merge
                           //////////////////////////////////////////
                           if (merge) {
                              bSubNode = bNode -> sub -> sub -> next -> next;
                              while (true) { 
                                 if (bSubNode -> sub == NULL)
                                    break;
                                 if (bSubNode -> sub == NULL)
                                 if (bSubNode -> sub -> sub == NULL)
                                    break;
                                 NODE* bConditionNode = bSubNode -> sub;
                                 if (debug) printf("------------ bConditionNode\n");
                                 if (debug) printTree(bConditionNode);
                                 NODE* aSubNode = aNode -> sub -> sub -> next -> next;
                                 bool found = false;
                                 NODE* bTransactionBodyNode = bConditionNode -> sub;
                                 if (bSubNode -> sub -> id != G_TMP_TRANSACTION_DEFAULT_CASE) 
                                    bTransactionBodyNode = bConditionNode -> sub -> next;
                                 if (debug) printf("------------ bTransactionBodyNode\n");
                                 if (debug) printTree(bTransactionBodyNode);
                                 if (bTransactionBodyNode -> sub == NULL) {
                                    found = true;
                                 } else
                                 while (1) {
                                    if (aSubNode -> sub == NULL)
                                       break;
                                    if (aSubNode -> sub != NULL)
                                    if (aSubNode -> sub -> sub == NULL)
                                       break;
                                       NODE* aConditionNode = aSubNode -> sub;
                                       if (debug) printf("------------ aConditionNode\n");
                                       if (debug) printTree(aConditionNode);
                                       //////////////////////////////////////////
                                       // Check both default
                                       //////////////////////////////////////////
                                       if ( (bSubNode -> sub -> id == G_TMP_TRANSACTION_DEFAULT_CASE) &
                                            (aSubNode -> sub -> id == G_TMP_TRANSACTION_DEFAULT_CASE) ) {
                                          if (debug) printf("Merging constructs (default).\n");
                                          NODE* aTransactionBodyNode = aConditionNode -> sub;
                                          if (aTransactionBodyNode -> sub == NULL) {
                                             aTransactionBodyNode -> sub = bTransactionBodyNode -> sub;
                                          } else {
                                             NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                                             while (1) {
                                                if (aTransactionBodySubNode -> next == NULL)
                                                   break;
                                                aTransactionBodySubNode = aTransactionBodySubNode -> next;
                                             }
                                             aTransactionBodySubNode -> next = bTransactionBodyNode -> sub;
                                          }
                                          found = true;
                                          if (debug) printf("Merging constructs done.\n");
                                          break;
                                       //////////////////////////////////////////
                                       // Check same condition
                                       //////////////////////////////////////////
                                       } else
                                       if (checkTree(aConditionNode -> sub -> sub, bConditionNode -> sub -> sub)) {
                                          //////////////////////////////////////////
                                          // Merge = append b into a
                                          //////////////////////////////////////////
                                          if (debug) printf("Merging constructs.\n");
                                          NODE* aTransactionBodyNode = aConditionNode -> sub -> next;
                                          if (aTransactionBodyNode -> sub == NULL) {
                                             aTransactionBodyNode -> sub = bTransactionBodyNode -> sub;
                                          } else {
                                             NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                                             while (1) {
                                                if (aTransactionBodySubNode -> next == NULL)
                                                   break;
                                                aTransactionBodySubNode = aTransactionBodySubNode -> next;
                                             }
                                             aTransactionBodySubNode -> next = bTransactionBodyNode -> sub; 
                                          }
                                          found = true;
                                          if (debug) printf("Merging constructs done.\n");
                                          break;
                                       }
                                    if (aSubNode -> next == NULL)
                                       break;
                                    aSubNode = aSubNode -> next;   
                                 }
                                 if (!(found)) {
                                    if (debug) printf("Appending constructs.\n");
                                    NODE* newEntryNode = copyTree(bSubNode -> sub);
                                    NODE* newNode = initNode(G_TMP_TRANSACTION_CASE_ITEM);
                                    newNode -> sub = newEntryNode;
                                    bool defaultFound = false;
                                    NODE* lastNode = aNode -> sub -> sub -> next -> next;
                                    aSubNode = aNode -> sub -> sub -> next -> next;
                                    if (debug) printf("------------ before\n");
                                    if (debug) printTree(node);
                                    while (true) {
                                       if (debug) printf("------------ aSubNode\n");
                                       if (debug) printTree(aSubNode);
                                       // n.p.: if (bSubNode -> sub -> id != G_TMP_TRANSACTION_DEFAULT_CASE)
                                       if (aSubNode -> sub -> id == G_TMP_TRANSACTION_DEFAULT_CASE) {
                                          newNode -> next = aSubNode;
                                          if (lastNode != NULL) {
                                             if (debug) printf("------------ lastNode\n");
                                             if (debug) printTree(lastNode);
                                          }
                                          lastNode -> next = newNode;
                                          defaultFound = true;
                                          break;
                                       }
                                       if (aSubNode -> next == NULL)
                                          break;
                                       lastNode = aSubNode;
                                       aSubNode = aSubNode -> next;
                                    }
                                    if (!(defaultFound))
                                       aSubNode -> next = newNode;
                                    if (debug) printf("------------ done\n");
                                    if (debug) printTree(node);
                                 }
                                 if (bSubNode -> next == NULL)
                                    break;
                                 bSubNode = bSubNode -> next;
                              }
                              if (debug) printf("------------ done\n");
                              if (debug) printTree(node);
                              // always merge !!!
                              progessANode = false;
                              aNode -> next = aNode -> next -> next;
                           }
                        }
                     }
                  }
               }   
            } else
            //////////////////////////////////////////
            // Merge emit
            //////////////////////////////////////////
            if ( (aNode -> sub -> id == G_PDVL_EMIT) &
                 (bNode -> sub -> id == G_PDVL_EMIT) ) {
               if (debug) printf("------------\n");
               if (debug) printTree(node);
               //////////////////////////////////////////
               // Check same event
               //////////////////////////////////////////
               if (checkTree(aNode -> sub -> sub, bNode -> sub -> sub)) {
                  if (debug) printf("Merging constructs.\n");
                  progessANode = false;
                  aNode -> next = aNode -> next -> next;
               }   
               if (debug) printf("------------ done\n");
               if (debug) printTree(node);
               //exit(-1);
            } else
            //////////////////////////////////////////
            // Merge unique or unique0: always merge !!!
            //////////////////////////////////////////
            if ( (aNode -> sub -> id == G_PDVL_TRANSACTION_AT_STATEMENT) &
                 (bNode -> sub -> id == G_PDVL_TRANSACTION_AT_STATEMENT) ) {
               if (debug) printf("------------ node\n");
               if (debug) printTree(node); 
               bool merge = true;
               ///////////////////////////////////////////////
               // get condition nodes
               ///////////////////////////////////////////////
               NODE* aConditionNode = aNode -> sub -> sub -> sub;
               if (aNode -> sub -> sub -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) {
                  if (aNode -> sub -> sub -> sub -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV0)
                     aConditionNode = aNode -> sub -> sub -> sub -> sub;
                  else
                     merge = false;;
               }
               if (debug) printf("------------ aConditionNode\n");
               if (debug) printTree(aConditionNode);
               NODE* bConditionNode = bNode -> sub -> sub -> sub;
               if (bNode -> sub -> sub -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) {
                  if (bNode -> sub -> sub -> sub -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV0)
                     bConditionNode = bNode -> sub -> sub -> sub -> sub;
                  else
                     merge = false;;
               }
               if (debug) printf("------------ bConditionNode\n");
               if (debug) printTree(bConditionNode);

               ///////////////////////////////////////////////
               // compare condition nodes
               ///////////////////////////////////////////////
               if (merge)
               if (checkTree(aConditionNode -> sub, bConditionNode -> sub)) {
                  ///////////////////////////////////////////////
                  // merge if branch
                  ///////////////////////////////////////////////
                  if (debug) printf("Merging multiple (if-branch) constructs.\n");
                  NODE* aTransactionBodyNode = aConditionNode -> next;
                  NODE* bTransactionBodyNode = bConditionNode -> next;
                  if (aTransactionBodyNode -> sub == NULL)
                     aTransactionBodyNode -> sub = bTransactionBodyNode -> sub; 
                  else {
                     NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                     while (1) {
                        if (aTransactionBodySubNode -> next == NULL) {
                           break;
                        }
                        aTransactionBodySubNode = aTransactionBodySubNode -> next;
                     }
                     aTransactionBodySubNode -> next = bTransactionBodyNode -> sub; 
                  }
                  if (debug) printf("------------ bTransactionBodyNode\n");
                  if (debug) printTree(bTransactionBodyNode);
                  ///////////////////////////////////////////////
                  // merge if branch
                  ///////////////////////////////////////////////
                  if (bTransactionBodyNode -> next != NULL) {
                     if (aTransactionBodyNode -> next == NULL) {
                        aNode -> sub -> sub -> id = G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT;
                     	NODE* tmpNode = initNode(G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV0);
                     	tmpNode -> sub = aConditionNode;
                     	aNode -> sub -> sub -> sub = tmpNode;
                     	aTransactionBodyNode -> next = initNode(G_PDVL_TRANSACTION_BODY);
                     }
                     aTransactionBodyNode = aTransactionBodyNode -> next;
                     bTransactionBodyNode = bTransactionBodyNode -> next;
                     if (aTransactionBodyNode -> sub == NULL)
                        aTransactionBodyNode -> sub = bTransactionBodyNode -> sub; 
                     else {
                        NODE* aTransactionBodySubNode = aTransactionBodyNode -> sub;
                        while (1) {
                           if (aTransactionBodySubNode -> next == NULL) {
                              break;
                           }
                           aTransactionBodySubNode = aTransactionBodySubNode -> next;
                        }
                        aTransactionBodySubNode -> next = bTransactionBodyNode -> sub; 
                     }
                  }
                  progessANode = false;
                  aNode -> next = aNode -> next -> next;
               }
               if (debug) printf("------------ node\n");
               if (debug) printTree(node);
            }
            if (aNode -> next == NULL)
               break;
            if (progessANode)
               aNode = aNode -> next;
         }
      }
   }
   if (node -> sub != NULL) 
      mergeConstructs(node -> sub);
   if (node -> next != NULL) 
      mergeConstructs(node -> next);
   return;
}
/////////////////////////////////////////////////////////////////////////////////
/// Add to sensitivity list
/////////////////////////////////////////////////////////////////////////////////
void addToSensList (string conditionName, 
                    bool trueEventFalseCond, 
                    NODE* eventOrCondTree, 
                    NODE* hierRootNode, 
                    string &sensList) {
   bool debug = false;
   string edgeName = "posedge ";
   string signalName = conditionName;
   if (trueEventFalseCond)
      signalName = "clk";
   string tmpHeader = "";
   NODE* eventDevNode = getTree(tmpHeader, conditionName, eventOrCondTree); 
   if (eventDevNode != NULL)
   if (eventDevNode -> sub != NULL) 
   if (eventDevNode -> sub -> sub != NULL) {
      eventDevNode = eventDevNode -> sub -> sub;
      if (debug) printf("-------------------------- hierRootNode\n"); 
      if (debug) printTree(hierRootNode);
      if (debug) printf("-------------------------- eventDevNode\n"); 
      if (debug) printTree(eventDevNode);
      if (eventDevNode -> next != NULL) 
      if (eventDevNode -> next -> next != NULL) {
         NODE* tmpEventDevNode = eventDevNode; 
         unsigned minDist = 10000;
         while (1) {
            unsigned dist = (unsigned)getDist(hierRootNode, tmpEventDevNode -> sub);                  
            if (debug) printf("dist: %d\n", dist);
            if (dist == 0) {
               eventDevNode = tmpEventDevNode;
                  break;
            }
            if (dist < minDist) {
               eventDevNode = tmpEventDevNode;
               minDist = dist;
            }
            if (tmpEventDevNode -> next -> next == NULL)
               break;
            tmpEventDevNode = tmpEventDevNode -> next -> next;
         }
      }
      if (trueEventFalseCond) {
         NODE* edgeNode = getNode(eventDevNode, G_SV_EDGE_IDENTIFIER);
         NODE* posEdgeNode = getNode(edgeNode, G_SV_POSEDGE_IDENTIFIER);
         if (posEdgeNode == NULL)
            edgeName = "negedge ";
         NODE* signalNameNode = getNode(eventDevNode, G_PDVL_EVENT_SIGNAL_NAME);
         if (signalNameNode != NULL) {
            signalName = getSI(signalNameNode);
         }
      } else {
         NODE* levelNode = getNode(eventDevNode, G_PDVL_LEVEL_IDENTIFIER);
         NODE* highLevelNode = getNode(levelNode, G_PDVL_HIGH_LEVEL_IDENTIFIER);
         if (highLevelNode == NULL)
            edgeName = "negedge ";
         NODE* signalNameNode = getNode(eventDevNode, G_PDVL_COND_SIGNAL_NAME);
         if (signalNameNode != NULL) {
            signalName = getSI(signalNameNode);
         }
      }
   }
   if (sensList.length() != 0)
      sensList.append(" or ");
   sensList.append(edgeName);
   sensList.append(signalName);
   if (debug) printf("sensList: %s\n", sensList.c_str());
}
/////////////////////////////////////////////////////////////////////////////////
/// Repace condition name
/////////////////////////////////////////////////////////////////////////////////
string replaceConditionName (string conditionName, 
                             NODE* condTree, 
                             NODE* hierRootNode, 
                             NODE* transactionNode) {
   bool debug = false;
   string tmpHeader = "";
   NODE* eventDevNode = getTree(tmpHeader, conditionName, condTree); 
   if (eventDevNode != NULL)
   if (eventDevNode -> sub != NULL) 
   if (eventDevNode -> sub -> sub != NULL) {
      eventDevNode = eventDevNode -> sub -> sub;
      if (debug) printf("-------------------------- hierRootNode\n"); 
      if (debug) printTree(hierRootNode);
      if (debug) printf("-------------------------- eventDevNode\n"); 
      if (debug) printTree(eventDevNode);
      if (eventDevNode -> next != NULL) 
      if (eventDevNode -> next -> next != NULL) {
         NODE* tmpEventDevNode = eventDevNode; 
         unsigned minDist = 10000;
         while (1) {
            unsigned dist = (unsigned)getDist(hierRootNode, tmpEventDevNode -> sub);                  
            if (debug) printf("dist: %d\n", dist);
            if (dist == 0) {
               eventDevNode = tmpEventDevNode;
                  break;
            }
            if (dist < minDist) {
               eventDevNode = tmpEventDevNode;
               minDist = dist;
            }
            if (tmpEventDevNode -> next -> next == NULL)
               break;
            tmpEventDevNode = tmpEventDevNode -> next -> next;
         }
      }
      NODE* levelNode = getNode(eventDevNode, G_PDVL_LEVEL_IDENTIFIER);
      if (levelNode != NULL) {
         string signalName = "";
         NODE* highLevelNode = getNode(levelNode, G_PDVL_HIGH_LEVEL_IDENTIFIER);
         if (highLevelNode == NULL)
            signalName = "!";
         NODE* signalNameNode = getNode(eventDevNode, G_PDVL_COND_SIGNAL_NAME);
         if (signalNameNode != NULL) {
            signalName.append(getSI(signalNameNode));
            conditionName = signalName;
         }
      }
   }
   return conditionName;
}
/////////////////////////////////////////////////////////////////////////////////
/// Replace condition
/////////////////////////////////////////////////////////////////////////////////
string replaceCondition (string conditionName, 
                         NODE* condTree, 
                         NODE* hierRootNode, 
                         NODE* transactionNode) {
   bool debug = false;
   string returnString = "";
   if (transactionNode -> sub -> sub -> next -> sub -> id == G_PDVL_CONDITION_EXPRESSION_PREV1) {
      writer_sv_expression(returnString, transactionNode -> sub -> sub -> next -> sub -> sub -> sub); 
   } else {
      returnString = replaceConditionName(conditionName, condTree, hierRootNode, transactionNode);
      if (debug) printf("returnString: %s\n", returnString.c_str());
   }
   if (transactionNode -> sub -> sub -> sub -> id == G_PDVL_AT_FALSE_CONDITION) {
      returnString.insert(0, "!(");
      returnString.append(")");
   }

   NODE* expressionListBrackets = getNode(transactionNode -> sub -> sub, G_PDVL_EXPRESSION_LIST_BRACKETS);
   if (expressionListBrackets != NULL) {
      if (debug) printf("--------------------- transactionNode -> sub -> sub -> next:\n");
      if (debug) printTree(transactionNode -> sub -> sub -> next);
      writer_pdvl_expression_list_brackets(returnString, expressionListBrackets -> sub);
   }
   return returnString;
}
/////////////////////////////////////////////////////////////////////////////////
/// Replace map
/////////////////////////////////////////////////////////////////////////////////
void replaceMap (string &header,
                 NODE* node,
                 string &replaceString) {
   bool debug = false;
   if (debug) printf("placeNewParameterTypeStep1 place id: %d\n", node -> id);
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      thisHeader.append(node2String(node));                              
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0) {
            replaceMap(thisHeader, node -> sub, replaceString);
         } else {
            if (debug) printf("replaceMap: .%s.\n", thisHeader.c_str());
            string expString = "";
            writer_sv_expression(expString, node -> sub -> sub -> sub);
            if (debug) printf("expString: .%s.\n", expString.c_str());
            expString.append(" ");
            string tmpString = thisHeader;
            tmpString.append(" ");
            size_t pos = replaceString.find(tmpString);
            while (pos != std::string::npos) {
               replaceString.replace(pos, tmpString.length(), expString);
               pos = replaceString.find(tmpString, pos + 3);
            } 
            if (node -> sub -> next != NULL) {
               replaceMap(thisHeader, node -> sub -> next, replaceString);
            }
         } 
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
}
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
                            NODE* hierRootNode) {
   bool debug = false;
   if (debug) printf("calling convertTrans2Process (%s): %d trueRegFalseItem: %d defaultZero: %d\n", regOrItemName.c_str(), transactionNode -> id, trueRegFalseItem, defaultZero);
   if (debug) printTree(0, 4, transactionNode);
   if (transactionNode -> id == G_PDVL_TRANSACTION_DECLARATION_BODY) {
      if (transactionNode -> sub != NULL) {
         transactionNode = transactionNode -> sub;
         if (transactionNode -> next != NULL) 
         if (transactionNode -> next -> sub != NULL) {
            transactionNode = transactionNode -> next;
            NODE* tmpNode = initNode(G_PDVL_TRANSACTION_BODY);
            tmpNode -> sub = transactionNode;
            NODE* subNode = convertTrans2Process(tmpNode, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
            if (subNode != NULL) {
               /////////////////////////////////////
               // procedure 
               /////////////////////////////////////
               if (debug) printf("sensList: %s\n", sensList.c_str());
               string procedureString;
               if (	(trueRegFalseItem)			&
               		(sensList.length() != 0) 	) {
                  procedureString = "always_ff @ (";
                  procedureString.append(sensList);
                  procedureString.append(") begin end ");
               } else 
               if (	(trueRegFalseItem)		&
               		(!trueRegFalseLatch) 	) {
                  procedureString = "always_latch begin end ";
               } else {
                  procedureString = "always_comb begin end ";
               }
               if (debug) printf("procedureString: %s\n", procedureString.c_str());
   
               maxPtr = 0;
               NODE* returnNode = initNode(0);
               int ptr = parser_sv_always_construct(procedureString, 0, returnNode);                  
               if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
               if (debug) printTree(returnNode);
            
               NODE* seqBlockNode = getNode(returnNode, G_SV_SEQ_BLOCK); 
               seqBlockNode -> sub = subNode;
               return returnNode;
            } 
         }
      }
   } else
   if (	(transactionNode -> id == G_PDVL_TRANSACTION_BODY) ) {
      if (transactionNode -> sub == NULL) {
         if (regOrItemName == "") {
            string beginEndString = "; ";
            maxPtr = 0;
            NODE* newNode = initNode(0);
            int ptr = parser_sv_statement_or_null(beginEndString, 0, newNode);                  
            return newNode;  
         }
      } else {
         //////////////////////////////////////
         // single statement in transaction body
         //////////////////////////////////////
         if (transactionNode -> sub -> next == NULL) {
            NODE* returnNode = convertTrans2Process(transactionNode -> sub -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
            if (debug) printf("return from %d\n", transactionNode -> id);
            return returnNode;
         } else
         //////////////////////////////////////
         // multiple statements in transaction body
         //////////////////////////////////////
         { 
            if (debug) printf("-------------------- transactionNode\n");
            if (debug) printTree(transactionNode);
            NODE* newTransactionBodyNode = initNode(G_PDVL_TRANSACTION_BODY);
            NODE* subTransactionBodyPtrNode = NULL;
            NODE* subPtrNode = transactionNode -> sub;
            NODE* subNode = NULL;
            NODE* lastSubNode = NULL;
            while (true) {
               if (subPtrNode -> sub != NULL) {            
                  subNode = convertTrans2Process(subPtrNode -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
                  if (debug) printf("-------------------- subNode\n");
                  if (debug) 
                  if (subNode != NULL)
                     printTree(subNode);
                  //////////////////////////////////////
                  // copy to newTransactionBodyNode when singal in subNode
                  //////////////////////////////////////
                  if (subNode != NULL) {
                     lastSubNode = subNode;
                     NODE* newSubTransactionNode = initNode(subPtrNode -> id);
                     newSubTransactionNode -> sub = copyTree(subPtrNode -> sub);
                     if (newTransactionBodyNode -> sub == NULL) {
                        newTransactionBodyNode -> sub = newSubTransactionNode;
                     } else {
                        subTransactionBodyPtrNode -> next = newSubTransactionNode;
                     }
                     subTransactionBodyPtrNode = newSubTransactionNode;
                  }
               }
               if (subPtrNode -> next == NULL)
                  break;
               subPtrNode = subPtrNode -> next;
            }
            if (debug) printf("-------------------- newTransactionBodyNode %s\n", regOrItemName.c_str());
            if (debug) printTree(newTransactionBodyNode);
            //////////////////////////////////////
            // Nothing in subCone
            //////////////////////////////////////
            if (newTransactionBodyNode -> sub == NULL) {
               return NULL;
            } else
            //////////////////////////////////////
            // only one (last) subCone
            //////////////////////////////////////
            if (newTransactionBodyNode -> sub -> next == NULL) {
               return lastSubNode;
            } else {
            //////////////////////////////////////
            // multiyple subCone => merge and retry 
            //////////////////////////////////////
               if (debug) printf("-------------------- newTransactionBodyNode merge\n");
               mergeConstructs(newTransactionBodyNode);
               if (debug) printf("-------------------- newTransactionBodyNode post merge\n");
               if (debug) printTree(newTransactionBodyNode);
               //exit(-1);
               NODE* returnNode = convertTrans2Process(newTransactionBodyNode -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
               if (debug) printf("return from %d\n", transactionNode -> id);
               if (debug) printf("-------------------- returnNode post merge\n");
               if (debug) printTree(returnNode);
               return returnNode;
            }
         }
      }
   } else
   if (transactionNode -> id == G_PDVL_TRANSACTION_PIPE_STATEMENT) {
      NODE* tmpNode = getNode(transactionNode -> sub, G_PDVL_TRANSACTION_BODY);
      NODE* subNode = convertTrans2Process(tmpNode, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
      if (debug) printf("-------------------------- transactionNode -> sub:\n");
      if (debug) printTree(transactionNode -> sub);
      if (subNode != NULL)
      if (pipeThis == 0) {
         NODE* pipeNode = transactionNode -> sub -> sub -> next;
         unsigned thisPipe = 0;
         if (debug) printf("-------------------------- pipeNode:\n");
         if (debug) printTree(pipeNode);
         if (pipeNode -> id == G_SV_PACKED_DIMENSION) {
            if (debug) printf("--------------------------\n");
            if (debug) printTree(pipeNode);
            pipeNode = getNode(pipeNode -> sub -> sub, G_SV_CONSTANT_PRIMARY);
            if (debug) printf("--------------------------\n");
            if (debug) printTree(pipeNode);
            thisPipe = sbin2Unsigned(solveEquation(pipeNode));
         } else
            thisPipe = sbin2Unsigned(solveEquation(pipeNode -> sub));
         if (debug) printf("thisPipe: %d\n", thisPipe);
         if (thisPipe == 0) {
            return subNode;
         } else {
            *piped = thisPipe;
            string assignString = regOrItemName;
            assignString.append(" <= ");
            assignString.append(regOrItemName);
            assignString.append("_pipe[0];");
            maxPtr = 0;
            NODE* subNode = initNode(0);
            parser_sv_statement_or_null(assignString, 0, subNode);
            return subNode;
         }
      } else {
         if (debug) printf("found pipe.\n");
         if (pipeThis < 2)
            return subNode;
         NODE* subInitNode = NULL;
         NODE* subInitNodePtr = NULL;
         for (int i = 0; i < pipeThis - 1; i++) {
            string assignString = "";
            assignString.append(regOrItemName);
            assignString.append("_pipe[");
            assignString.append(to_string(i));
            assignString.append("] <= ");
            assignString.append(regOrItemName);
            assignString.append("_pipe[");
            assignString.append(to_string(i + 1));
            assignString.append("]; ");

            maxPtr = 0;
            NODE* newInitNode = initNode(0);
            parser_sv_statement_or_null(assignString, 0, newInitNode);
            if (subInitNode == NULL)
               subInitNode = newInitNode;
            else
               subInitNodePtr -> next = newInitNode;
            subInitNodePtr = newInitNode;
         }
         subInitNodePtr -> next = subNode;
         return subInitNode;
         if (debug) printTree(subInitNode);
      }
   } else
   if (transactionNode -> id == G_PDVL_TRANSACTION_STATEMENT) {
      if (transactionNode -> sub != NULL) {
         NODE* subNode = convertTrans2Process(transactionNode -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
         NODE* nextNode = NULL;
         if (transactionNode -> next != NULL)
            nextNode = convertTrans2Process(transactionNode -> next, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, NULL, moduleNode, hierRootNode);
         if (debug) {
            if (subNode != NULL) {
               printf("returned subnode!\n");
            } else
               printf("returned subnode NULL\n");
            if (nextNode != NULL) {
               printf("returned nextNode!\n");
            } else
               printf("returned nextNode NULL\n");
        }
      
         if (subNode != NULL) {
            if (subNode -> id == 0) {
              if (nextNode != NULL)
                  return nextNode;
               else
                  return NULL;
            }
            if (nextNode != NULL)
               subNode -> next = nextNode;
            if (debug) printf("return subNode\n");
            return subNode;
         } else
         if (nextNode != NULL) {
            return nextNode;
         }
      } else
         return NULL;
   } else 
   if (	(transactionNode -> id == G_PDVL_TRANSACTION_AT_STATEMENT) ) {
      if (transactionNode -> sub != NULL) {
         NODE* returnNode = convertTrans2Process(transactionNode -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
         if (debug) printf("return from %d\n", transactionNode -> id);
         return returnNode;
      }
   } else
   if ( (transactionNode -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) ) {
      string conditionName = getSI(transactionNode -> sub); 
      if (	(checkTree(conditionName, eventTree)) 	) {
         if (debug) printf("edge found: %s\n", conditionName.c_str());
         if (trueRegFalseItem) {
            addToSensList(conditionName, true, eventTree, hierRootNode, sensList); 
         }
         skipPreEdge = false;
         *aboveEdge = false;
         NODE* returnNode = convertTrans2Process(transactionNode -> sub -> next, sensList, regOrItemName, 
                                                     false, //trueRegFalseItem, 
                                                     trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
         if (debug) printf("return from %d\n", transactionNode -> id);
         if ( (returnNode != NULL) &
              (trueRegFalseItem) &
              (defaultZero)      ) {
            string newAssignString = regOrItemName;
            newAssignString.append(" <= 0; ");
            maxPtr = 0;
            NODE* newNode = initNode(0);
            int ptr = parser_sv_statement_or_null(newAssignString, 0, newNode);                  
            if (debug) printTree(newNode);
            if (debug) printf("------------------------------------\n");
            if (debug) printTree(returnNode);
            newNode -> next = returnNode;
            return newNode;
         } else
            return returnNode;
      } else {
         NODE* subNode = convertTrans2Process(transactionNode -> sub -> next, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
         // if of if-else with content in if
         if (subNode != NULL)
         {
            // if of if-else with content only in if
            if (debug) printf("returned!\n");
            if (debug) printf("--------------------- transactionNode:\n");
            if (debug) printTree(10, transactionNode);
            string ifString = "if (";
            ifString.append(replaceCondition(conditionName, condTree, hierRootNode, transactionNode));
            ifString.append(" ) begin end ");
            if (debug) printf("ifString: %s\n", ifString.c_str());
            maxPtr = 0;
            NODE* returnNode = initNode(0);
            int ptr = parser_sv_statement_or_null(ifString, 0, returnNode);                  
            if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
          
            NODE* seqBlockNode = getNode(returnNode, G_SV_SEQ_BLOCK); 
            seqBlockNode -> sub = subNode;
            return returnNode;
         }
      }
   } else
   if ( (transactionNode -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) ) {
      // skip prevN
      transactionNode = transactionNode -> sub;
      string conditionName = getSI(transactionNode -> sub);
      if (debug) printf("conditionName: %s\n", conditionName.c_str()); 
      if (	(checkTree(conditionName, eventTree)) 	) {
         printf("edge found: %s\n", conditionName.c_str());
         exit(-1);
         return convertTrans2Process(transactionNode -> sub -> next, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
      } else {
         NODE* subNode = convertTrans2Process(transactionNode -> sub -> next, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
         // if of if-else with content in if
         if (subNode != NULL)
         {
            //if (transactionNode -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) {
            NODE* sub2Node = convertTrans2Process(transactionNode -> sub -> next -> next, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
            // if or if-else with content in if and else
            if (sub2Node != NULL)
            {   
               if (debug) printf("trueRegFalseItem %d sensList.length() %d\n", trueRegFalseItem, sensList.length());
               if (trueRegFalseItem)
               if (sensList.length() != 0) {
                  addToSensList(conditionName, false, condTree, hierRootNode, sensList); 
                  trueRegFalseItem = false;
               }
               if (debug) printTree(transactionNode);                                                                        
               if (debug) printf("exit a\n");
               string ifString = "if (";
               ifString.append(replaceCondition(conditionName, condTree, hierRootNode, transactionNode));
               ifString.append(") begin end else begin end ");
               if (debug) printf("ifString: %s\n", ifString.c_str());

               maxPtr = 0;
               NODE* returnNode = initNode(0);
               int ptr = parser_sv_statement_or_null(ifString, 0, returnNode);                  
               if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
          
               NODE* ifElseNode = getNode(returnNode, G_SV_IF_ELSE_CONDITIONAL_STATEMENT); 
               NODE* seqBlockNode = getNode(ifElseNode -> sub -> next, G_SV_SEQ_BLOCK); 
               seqBlockNode -> sub = subNode;

               seqBlockNode = getNode(ifElseNode -> sub -> next -> next, G_SV_SEQ_BLOCK); 
               seqBlockNode -> sub = sub2Node;
            
               if (debug) printTree(returnNode);
               return returnNode;
            }
            // if of if-else with content only in if
            if (debug) printf("returned!\n");
            if (debug) printf("--------------------- transactionNode:\n");
            if (debug) printTree(10, transactionNode); 
            string ifString = "if (";
            ifString.append(replaceCondition(conditionName, condTree, hierRootNode, transactionNode));
            ifString.append(") begin end ");
            if (debug) printf("ifString: %s\n", ifString.c_str());

            maxPtr = 0;
            NODE* returnNode = initNode(0);
            int ptr = parser_sv_statement_or_null(ifString, 0, returnNode);                  
            if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
          
            NODE* seqBlockNode = getNode(returnNode, G_SV_SEQ_BLOCK); 
            seqBlockNode -> sub = subNode;
            return returnNode;
         } 
         // if-else 
         NODE* sub2Node = convertTrans2Process(transactionNode -> sub -> next -> next, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
         // if of if-else with content in (if and?) else
         if (sub2Node != NULL)
         {
            if (debug) printf("returned!\n");
            if (skipPreEdge)
            if (!(*aboveEdge))
               return sub2Node;                                                                           
            if (debug) printf("returned!\n");
            if (debug) printf("--------------------- transactionNode:\n");
            if (debug) printTree(10, transactionNode);
            maxPtr = 0;
            NODE* returnNode = initNode(0);
            string ifString = "if (";
            if ( (trueRegFalseItem)	&
                 (defaultZero)      ) {
               if (sensList.length() != 0) {
                  addToSensList(conditionName, false, condTree, hierRootNode, sensList); 
               }
               ifString.append(replaceCondition(conditionName, condTree, hierRootNode, transactionNode));
               ifString.append(") begin ");
               ifString.append(regOrItemName);
               ifString.append(" <= 0; end else begin end ");
               if (debug) printf("ifString: %s\n", ifString.c_str());
               int ptr = parser_sv_statement_or_null(ifString, 0, returnNode);                  
               NODE* seqBlockNode = getNode(returnNode, G_SV_IF_ELSE_CONDITIONAL_STATEMENT); 
               seqBlockNode = seqBlockNode -> sub -> next -> next;
               seqBlockNode = getNode(seqBlockNode, G_SV_SEQ_BLOCK);
               seqBlockNode -> sub = sub2Node;
               if (debug) printf("----------------------------\n");
               if (debug) printTree(15, returnNode);
            } else {
               ifString.append("!(");
               ifString.append(replaceCondition(conditionName, condTree, hierRootNode, transactionNode));
               ifString.append(")) begin end ");
               if (debug) printf("ifString: %s\n", ifString.c_str());
               int ptr = parser_sv_statement_or_null(ifString, 0, returnNode);                  
               NODE* seqBlockNode = getNode(returnNode, G_SV_SEQ_BLOCK); 
               seqBlockNode -> sub = sub2Node;
            }
            return returnNode;
         }
      }
   } else
   if ( (transactionNode -> id == G_PDVL_TRANSACTION_PRIORITY_LIST) |
        (transactionNode -> id == G_PDVL_TRANSACTION_UNIQUE_LIST)   |
        (transactionNode -> id == G_PDVL_TRANSACTION_UNIQUE0_LIST) ) {
      string conditionName = getSI(transactionNode -> sub);
      if (debug) printf("conditionName: %s\n", conditionName.c_str());
      if (debug) printf("------------------------ call\n"); 
      if (debug) printTree(transactionNode);
      if (1) {
         NODE* listEntryNode = transactionNode -> sub;
         NODE* returnNode = NULL;
         NODE* ifCondNode = NULL;
         bool found = false;
         bool init = true;
         while (1) {
            NODE* subNode = convertTrans2Process(listEntryNode -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
            if (subNode == NULL) {
               string emptyName = "";
               subNode = convertTrans2Process(listEntryNode -> sub, sensList, emptyName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
               if (debug) printf("------------------------ subNode\n"); 
               if (debug) 
               if (subNode != NULL)
                  printTree(subNode);
            } else
               found = true;
            if (subNode != NULL) {
               if (debug) printf("------------------------ subNode\n"); 
               if (debug) 
               if (subNode != NULL)
                  printTree(subNode);
               if (returnNode == NULL) {
                  returnNode = subNode;
               } else {
                  if (subNode -> next != NULL) {
                     NODE* tmpNode = initNode(G_SV_STATEMENT_OR_NULL);
                     tmpNode -> sub = initNode(G_SV_STATEMENT);
                     tmpNode -> sub -> sub = initNode(G_SV_STATEMENT_ITEM);
                     tmpNode -> sub -> sub -> sub = initNode(G_SV_SEQ_BLOCK);
                     tmpNode -> sub -> sub -> sub -> sub = subNode;
                     subNode = tmpNode;
                  }
                  if (init) {
                     NODE* uniquePriorityNode = initNode(G_SV_UNIQUE_PRIORITY);
                     if (transactionNode -> id == G_PDVL_TRANSACTION_PRIORITY_LIST) {
                        NODE* uniquePriorityPriorityNode = initNode(G_SV_UNIQUE_PRIORITY_PRIORITY);
                        uniquePriorityNode -> sub = uniquePriorityPriorityNode;
                     } else
                     if (transactionNode -> id == G_PDVL_TRANSACTION_UNIQUE_LIST) {
                        NODE* uniquePriorityPriorityNode = initNode(G_SV_UNIQUE_PRIORITY_UNIQUE);
                        uniquePriorityNode -> sub = uniquePriorityPriorityNode;
                     } else {
                        NODE* uniquePriorityPriorityNode = initNode(G_SV_UNIQUE_PRIORITY_UNIQUE0);
                        uniquePriorityNode -> sub = uniquePriorityPriorityNode;
                     }
                     if (debug) printf("------------------------ ifCondNode 1\n"); 
                     if (debug) printTree(ifCondNode);
                     ifCondNode -> id = G_SV_IF_ELSE_CONDITIONAL_STATEMENT;
                     uniquePriorityNode -> next = ifCondNode -> sub;
                     ifCondNode -> sub = uniquePriorityNode;
                     ifCondNode -> sub -> next -> next -> next = subNode;
                  } else {
                     ifCondNode -> id = G_SV_IF_ELSE_CONDITIONAL_STATEMENT;
                     ifCondNode -> sub -> next -> next = subNode;
                  }
                  init = false;
               }
               ifCondNode = getNode(subNode, G_SV_IF_CONDITIONAL_STATEMENT);
            }
            if (debug) printf("------------------------ ifCondNode\n"); 
            if (debug) 
            if (ifCondNode != NULL)
               printTree(ifCondNode);
            if (listEntryNode -> next == NULL) {
               if (subNode != NULL)
               if (ifCondNode != NULL) {
                  // rare case for single entry
                  if (init) {
                     NODE* uniquePriorityNode = initNode(G_SV_UNIQUE_PRIORITY);
                     if (transactionNode -> id == G_PDVL_TRANSACTION_PRIORITY_LIST) {
                        NODE* uniquePriorityPriorityNode = initNode(G_SV_UNIQUE_PRIORITY_PRIORITY);
                        uniquePriorityNode -> sub = uniquePriorityPriorityNode;
                     } else
                     if (transactionNode -> id == G_PDVL_TRANSACTION_UNIQUE_LIST) {
                        NODE* uniquePriorityPriorityNode = initNode(G_SV_UNIQUE_PRIORITY_UNIQUE);
                        uniquePriorityNode -> sub = uniquePriorityPriorityNode;
                     } else {
                        NODE* uniquePriorityPriorityNode = initNode(G_SV_UNIQUE_PRIORITY_UNIQUE0);
                        uniquePriorityNode -> sub = uniquePriorityPriorityNode;
                     }
                     ifCondNode -> id = G_SV_IF_CONDITIONAL_STATEMENT;
                     uniquePriorityNode -> next = ifCondNode -> sub;
                     ifCondNode -> sub = uniquePriorityNode;
                     if (debug) printf("---------------------------\n");
                     if (debug) printTree(returnNode);
                  }
               }
               if (returnNode != NULL)
               if (transactionNode -> next != NULL) { 
                  if (debug) printf("------------------------ ifCondNode 2\n"); 
                  if (debug) printTree(ifCondNode);
                  subNode = convertTrans2Process(transactionNode -> next -> sub -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
                  if (subNode == NULL) {  // not found in default
                      if (!found)         // not found at all => return NULL
                          return NULL;
                  }
                  if (debug) printf("------------------------ subNode\n"); 
                  if (debug) 
                  if (subNode != NULL)
                     printTree(subNode); 
                  ifCondNode -> id = G_SV_IF_ELSE_CONDITIONAL_STATEMENT;
                  NODE* tmpNode = ifCondNode -> sub -> next; // -> next;
                  if (tmpNode -> next != NULL)
                     tmpNode = tmpNode -> next;
                  tmpNode -> next = initNode(G_SV_STATEMENT_OR_NULL);
                  tmpNode -> next -> sub = initNode(G_SV_STATEMENT);
                  tmpNode -> next -> sub -> sub = initNode(G_SV_STATEMENT_ITEM);
                  tmpNode -> next -> sub -> sub -> sub = initNode(G_SV_SEQ_BLOCK);
                  if (subNode == NULL){
                     tmpNode -> next -> sub -> sub -> sub -> sub = initNode(G_SV_STATEMENT_OR_NULL);
                     tmpNode -> next -> sub -> sub -> sub -> sub -> sub = initNode(G_SV_NULL_STATEMENT);
                  } else
                     tmpNode -> next -> sub -> sub -> sub -> sub = subNode;
                  if (debug) printf("------------------------ return\n"); 
                  if (debug) printTree(returnNode);
                  if (subNode == NULL) {
                     string beginEndString = "; ";
                     maxPtr = 0;
                     NODE* newNode = initNode(0);
                     int ptr = parser_sv_statement_or_null(beginEndString, 0, newNode);
                     if (debug) printTree(newNode);
                  }
               }
               break;
            }
            listEntryNode = listEntryNode -> next;
         }
         if (debug) printf("done\n");
         if (debug) 
         if (returnNode != NULL) {
            printf("------------------------ return\n"); 
            printTree(returnNode);
         } 
         if (found)
            return returnNode;
         else
            return NULL;
      }
   } else
   if (	(transactionNode -> id == G_PDVL_TRANSACTION_DEFAULT_SINGLE_STATEMENT) ) {
      if (transactionNode -> sub == NULL)
         return NULL;
      return convertTrans2Process(transactionNode -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
   } else
   if (	(transactionNode -> id == G_TMP_TRANSACTION_CASE_ITEM_EXPRESSION) ) {
      if (transactionNode -> next == NULL)
         return NULL;
      return convertTrans2Process(transactionNode -> sub -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
   } else
   if (transactionNode -> id == G_TMP_TRANSACTION_CASE_STATEMENT) {
      if (debug) printf("------------------------------------ transaction case statement\n");
      if (debug) printTree(0, 5, transactionNode -> sub);
      NODE* returnNode = initNode(0);
      bool subFound = false;      
      NODE* nextStatItemNode = NULL;
      NODE* condBodyNode = NULL;
      if (transactionNode -> sub != NULL)
         condBodyNode = transactionNode -> sub;
      if (condBodyNode != NULL)
      while (1) {   
         string line = "";
         if (condBodyNode -> id == G_SV_UNIQUE_PRIORITY) {
            if (condBodyNode -> sub -> id == G_SV_UNIQUE_PRIORITY_UNIQUE)
               line.append("unique ");              
            if (condBodyNode -> sub -> id == G_SV_UNIQUE_PRIORITY_UNIQUE0)
               line.append("unique0 ");              
            if (condBodyNode -> sub -> id == G_SV_UNIQUE_PRIORITY_PRIORITY)
               line.append("priority ");
            condBodyNode = condBodyNode -> next;
         }
         if (condBodyNode -> id == G_TMP_TRANSACTION_CASE_KEYWORD)
            condBodyNode = condBodyNode -> next;
         /////////////////////////////////////
         // handline if-else and condition
         /////////////////////////////////////
         NODE* thisStatItemNode = NULL;
         if (condBodyNode -> next == NULL) {
            if (debug) printf("last\n");
            if (condBodyNode -> sub -> id == G_TMP_TRANSACTION_DEFAULT_CASE) {
               if (returnNode -> id == 0) {
                  returnNode -> id = G_SV_STATEMENT_OR_NULL;
                  thisStatItemNode = returnNode;
               } else
                  thisStatItemNode = nextStatItemNode;
            } else {
               line.append("if ( a ) ; "); 
               NODE* tmpStatementNode = NULL;
               if (returnNode -> id == 0) {
                  returnNode -> id = G_SV_STATEMENT_OR_NULL;
                  tmpStatementNode = initSubNode(returnNode, G_SV_STATEMENT);
               } else {
                  tmpStatementNode = initSubNode(nextStatItemNode, G_SV_STATEMENT);
               }
               tmpStatementNode = initSubNode(tmpStatementNode, G_SV_STATEMENT_ITEM);
               tmpStatementNode = initSubNode(tmpStatementNode, G_SV_CONDITIONAL_STATEMENT);
               if (debug) printTree(tmpStatementNode); 
               if (debug) printf("   %s\n", line.c_str());
               int ptr = parser_sv_conditional_statement(line, 0, tmpStatementNode);
               if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
            
               thisStatItemNode = getNode(tmpStatementNode -> sub, G_SV_STATEMENT_OR_NULL);
               NODE* exprNode = getNode(tmpStatementNode -> sub, G_SV_EXPRESSION);
               exprNode -> sub = condBodyNode -> sub -> sub -> sub -> sub;
            
               if (debug) printTree(tmpStatementNode);
            }
         } else {
            line.append("if ( a ) ; else ; "); 
            NODE* tmpStatementNode = NULL;
            if (returnNode -> id == 0) {
               returnNode -> id = G_SV_STATEMENT_OR_NULL;
               tmpStatementNode = initSubNode(returnNode, G_SV_STATEMENT);
            } else {
               tmpStatementNode = initSubNode(nextStatItemNode, G_SV_STATEMENT);
            }
            tmpStatementNode = initSubNode(tmpStatementNode, G_SV_STATEMENT_ITEM);
            tmpStatementNode = initSubNode(tmpStatementNode, G_SV_CONDITIONAL_STATEMENT);
            if (debug) printTree(tmpStatementNode); 
            if (debug) printf("   %s\n", line.c_str());
            int ptr = parser_sv_conditional_statement(line, 0, tmpStatementNode);
            if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
            
            thisStatItemNode = getNode(tmpStatementNode -> sub, G_SV_STATEMENT_OR_NULL);
            nextStatItemNode = thisStatItemNode -> next;
            NODE* exprNode = getNode(tmpStatementNode -> sub, G_SV_EXPRESSION);
            exprNode -> sub = condBodyNode -> sub -> sub -> sub -> sub;
            
            if (debug) printTree(tmpStatementNode);
         }
         /////////////////////////////////////
         // sub cone
         /////////////////////////////////////
         NODE* subNode = NULL;
         if (condBodyNode -> sub -> id == G_TMP_TRANSACTION_DEFAULT_CASE)
            subNode = convertTrans2Process(condBodyNode -> sub -> sub, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
         else
            subNode = convertTrans2Process(condBodyNode -> sub -> sub -> next, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
         if (subNode != NULL) {
            subFound = true;
            if (debug) printf("case subNode returned!\n");
            if (thisStatItemNode != NULL) { 
               // allways use begin end !
               if (1) { //subNode -> next != NULL) {
                  if (debug) printf("----------------------------- thisStatItemNode:\n");
                  if (debug) printTree(thisStatItemNode);
                  NODE* seqBlockNode = initNode(0);
                  string seqString = "begin ; end";
                  parser_sv_statement_or_null(seqString, 0, seqBlockNode);
                  seqBlockNode -> sub -> sub -> sub -> sub = subNode;
                  thisStatItemNode -> sub = seqBlockNode -> sub;
               } else
                  thisStatItemNode -> sub = subNode -> sub;
            }
         }
      	 if (condBodyNode -> next == NULL) {
      	    if (debug)
            if (subFound) {
               printf("----------------------------- returnNode:\n");
               printTree(returnNode);
               string returnString = "";
               writer_sv_statement_or_null(returnString, returnNode -> sub);
               printf("returnString: %s\n", returnString.c_str());
            }
            if (subFound)     
               return returnNode;
            else
               return NULL;
            break;                          
         }
         condBodyNode = condBodyNode -> next;
      }      
      
      NODE* refNode = NULL;
      string caseName = "";
      if (debug) printf("caseName: %s\n", caseName.c_str()); 
      NODE* uniquePriorityNode = NULL;
      if (transactionNode -> sub != NULL) {
         if (transactionNode -> sub -> id == G_SV_UNIQUE_PRIORITY) {
            uniquePriorityNode = transactionNode -> sub;
            if (transactionNode -> sub -> next != NULL)
            if (transactionNode -> sub -> next -> next != NULL)
            if (transactionNode -> sub -> next -> next -> next != NULL) {
               caseName = getSI(transactionNode -> sub -> next);
               condBodyNode = transactionNode -> sub -> next -> next -> next;
            }
         } else
         if (transactionNode -> sub -> next != NULL)
         if (transactionNode -> sub -> next -> next != NULL) {
            caseName = getSI(transactionNode -> sub);
            condBodyNode = transactionNode -> sub -> next -> next;
         }
      }
      NODE* defaultItemNode = NULL;
      if (condBodyNode != NULL)
      while (1) {   
         string conditionName = getSI(condBodyNode -> sub);
         if (debug) printf("conditionName: %s <-\n", conditionName.c_str()); 
         if (debug) printTree(condBodyNode);

         NODE* subNode = convertTrans2Process(condBodyNode -> sub -> next, sensList, regOrItemName, trueRegFalseItem, trueRegFalseLatch, skipPreEdge, defaultZero, aboveEdge, piped, pipeThis, eventTree, condTree, datapathTree, coneNode, moduleNode, hierRootNode);
                 
         if (subNode != NULL) {
            subFound = true;
            if (debug) printf("case subNode returned!\n");
         }
         if (returnNode -> id == 0) {
            // if skeleton ....
            string line = "";
            if (uniquePriorityNode != NULL)  {
               if (uniquePriorityNode -> sub -> id == G_SV_UNIQUE_PRIORITY_UNIQUE)
                  line.append("unique ");              
               if (uniquePriorityNode -> sub -> id == G_SV_UNIQUE_PRIORITY_UNIQUE0)
                  line.append("unique0 ");              
               if (uniquePriorityNode -> sub -> id == G_SV_UNIQUE_PRIORITY_PRIORITY)
                  line.append("priority ");                                   
            }
            line.append("if (");              
            line.append(caseName);
            line.append(") begin end else begin end ");
            if (debug) printf("   %s\n", line.c_str());
             // parse to caseNode
            returnNode -> id = G_SV_STATEMENT_OR_NULL;
            NODE* tmpStatementNode = initSubNode(returnNode, G_SV_STATEMENT);
            tmpStatementNode = initSubNode(tmpStatementNode, G_SV_STATEMENT_ITEM);
            tmpStatementNode = initSubNode(tmpStatementNode, G_SV_IF_ELSE_CONDITIONAL_STATEMENT);

            if (debug) printTree(tmpStatementNode); 
            int ptr = parser_sv_if_else_conditional_statement(line, 0, tmpStatementNode);                  
            if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
            if (debug) printTree(tmpStatementNode);
               
            refNode = tmpStatementNode -> sub -> next; 
            if (uniquePriorityNode != NULL)
               refNode = refNode -> next;
         }
            
         string line = "";              
         line.append(conditionName);
         line.append(": begin end ");
         if (debug) printf("   %s\n", line.c_str());

         // parse to caseNode
         NODE* itemNode = initNode(G_SV_CASE_ITEM);
         int ptr = parser_sv_case_item(line, 0, itemNode);                  
         if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
         if (debug) printTree(itemNode); 
            
         NODE* seqBlockNode = getNode(itemNode -> sub, G_SV_SEQ_BLOCK);
         if (subNode == NULL) {
            subNode = initNode(G_SV_STATEMENT_OR_NULL);
            NODE* nullStatementNode = initNode(G_SV_NULL_STATEMENT);
            subNode -> sub = nullStatementNode;
         }
         seqBlockNode -> sub = subNode;
            
         if (conditionName == "default") 
            defaultItemNode = itemNode;
         else {
            refNode -> next = itemNode;
            refNode = itemNode;   
         }
         exit(-1);

      	 if (condBodyNode -> next == NULL) {
            if (debug) printf("break\n"); 
            if (defaultItemNode != NULL) {
               refNode -> next = defaultItemNode;
            }
            if (subFound)
               return returnNode;
            else
               return NULL;
            break;                          
         }
         condBodyNode = condBodyNode -> next;
      }
      if (debug) printf("cont\n");
   } else
   if (	(transactionNode -> id == G_PDVL_EMIT_DELAYED_EVENT)            ) {
      string emitName = getSI(transactionNode -> sub -> next);
      if (debug) printf("emitName (delay event): %s\n", emitName.c_str());
      if (debug) printf("----------------------------- datapathNode:\n");
      if (debug) printTree(transactionNode); 
      if (checkTree(emitName, datapathTree)) {
         if (debug) printf("datapath found: %s\n", emitName.c_str());    
         NODE* datapathNode = getSubTree(emitName, datapathTree);
         datapathNode = datapathNode -> sub -> sub -> next;
         if (debug) printf("----------------------------- datapathNode:\n");
         if (debug) printTree(datapathNode);
         NODE* subNode = extractTreeLHS(regOrItemName, NULL, datapathNode);
         if (subNode != NULL) {
            if (debug) printf("reg|item found: %s\n", regOrItemName.c_str());    
            if (1) { //assignmentNode != NULL) {
               NODE* returnNode = initNode(G_SV_STATEMENT_OR_NULL); 
               NODE* returnSubNode = initSubNode(returnNode, G_SV_STATEMENT);
               returnSubNode = initSubNode(returnSubNode, G_SV_STATEMENT_ITEM);
               returnSubNode = initSubNode(returnSubNode, G_SV_PROCEDURAL_TIMING_CONTROL_STATEMENT);
               returnSubNode = initSubNode(returnSubNode, G_SV_PROCEDURAL_TIMING_CONTROL);
               NODE* returnDelayControlNode = initSubNode(returnSubNode, G_SV_DELAY_CONTROL);
               returnDelayControlNode -> sub = transactionNode -> sub -> sub;
               NODE* returnSubNextNode = initNode(G_SV_STATEMENT_OR_NULL);
               returnSubNode -> next = returnSubNextNode;
               returnSubNextNode = initSubNode(returnSubNextNode, G_SV_STATEMENT);
               returnSubNextNode = initSubNode(returnSubNextNode, G_SV_STATEMENT_ITEM);
               returnSubNextNode -> sub = datapathNode -> sub;
               if (debug) printf("-----------------------------\n");
               if (debug) printTree(returnNode);
               return returnNode;  
            } else
               exit(-1);
         }
      }
   } else
   if (	(transactionNode -> id == G_PDVL_DO_NOT_EMIT)            ) {
      string emitName = getSI(transactionNode -> sub);
      if (debug) printf("emitName: %s\n", emitName.c_str()); 
      if (emitName.compare(regOrItemName) == 0) {
         emitName.append(" <= 1'b0; ");
         maxPtr = 0;
         NODE* newNode = initNode(0);
         int ptr = parser_sv_statement_or_null(emitName, 0, newNode);                  
         if (debug) printf("%s\n", emitName.c_str());
         if (debug) printf("ptr: %d maxPtr: %d\n", ptr, maxPtr);
         return newNode;  
      }
   } else
   if (	(transactionNode -> id == G_PDVL_EMIT)            ) {
      if (regOrItemName == "") {
         string beginEndString = "; ";
         maxPtr = 0;
         NODE* newNode = initNode(0);
         int ptr = parser_sv_statement_or_null(beginEndString, 0, newNode);                  
         return newNode;  
      }
      NODE* emitNameNode = getNode(transactionNode -> sub, G_SI);
      string emitName = getSI(emitNameNode);
      if (debug) printf("emitName: %s\n", emitName.c_str()); 
      if (emitName.compare(regOrItemName) == 0) {
         emitName.append(" <= 1'b1; ");
         maxPtr = 0;
         NODE* newNode = initNode(0);
         int ptr = parser_sv_statement_or_null(emitName, 0, newNode);                  
         return newNode;  
      } else
      if (checkTree(emitName, datapathTree)) {
         if (debug) printf("datapath found: %s\n", emitName.c_str());    
         NODE* datapathNode = getSubTree(emitName, datapathTree);
         if (debug) printf("----------------------------- datapathNode:\n");
         if (debug) if (datapathNode != NULL) printTree(datapathNode);
         if (datapathNode -> sub -> sub -> next == NULL)
            return NULL;
         datapathNode = datapathNode -> sub -> sub -> next;
         if (debug) printf("----------------------------- datapathNode:\n");
         if (debug) if (datapathNode != NULL) printTree(datapathNode);
         if (debug) printf("----------------------------- transactionNode -> sub:\n");
         if (debug) printTree(transactionNode -> sub);
         if (transactionNode -> sub -> next != NULL) {
            NODE* mapTree = initNode(0);
            if (datapathNode -> id != G_PDVL_TF_PORT_LIST_BRACKETS) {
               printf("ERR.CONVERT.DATAPATH.PORT_MISMATCH: %s\n", emitName.c_str());
               exit(-1);
            }
            NODE* mapStringPtrNode = datapathNode -> sub; // -> sub;
            NODE* mapExpPtrNode = transactionNode -> sub -> next -> sub;
            while (1) {
               if (debug) printf("-------------- map:\n");
               NODE* functionPortItemNode = getNode(mapStringPtrNode -> sub, G_SV_FUNCTION_PORT_ITEM);
               NODE* mapStringSINode = functionPortItemNode -> sub -> sub -> next -> sub;
               if (debug) printTree(mapStringSINode);
               NODE* mapExpNode = initNode(G_SV_EXPRESSION);
               if (mapExpPtrNode -> id == G_SV_EXPRESSION)
                  mapExpNode -> sub = copyTree(mapExpPtrNode -> sub);
               else
                  mapExpNode -> sub = copyTree(mapExpPtrNode -> sub -> sub);
               if (debug) printTree(mapExpNode);
               addSITree(mapStringSINode, mapExpNode, mapTree);
               if (mapExpPtrNode -> next == NULL) {
                  if (mapStringPtrNode -> next != NULL)
                  if (mapStringPtrNode -> next -> sub -> sub != NULL) {
                     printf("ERR.CONVERT.DATAPATH.PORT_MISMATCH: %s\n", emitName.c_str());
                     exit(-1);
                  }
                  break;
               }
               mapExpPtrNode = mapExpPtrNode -> next;
               if (mapStringPtrNode -> next == NULL) {
                  printf("ERR.CONVERT.DATAPATH.PORT_MISMATCH: %s\n", emitName.c_str());
                  exit(-1);
               }
               mapStringPtrNode = mapStringPtrNode -> next;
            }
            if (debug) printSITree(mapTree);
            if (debug) printTree(mapTree); 
            string replaceString = "";
            writer_pdvl_data_declaration_body(replaceString, datapathNode -> next -> sub);
            if (debug) printf("replaceString: %s\n", replaceString.c_str());
            string header = " ";
            replaceMap(header, mapTree, replaceString);
            if (debug) printf("replaceString: %s\n", replaceString.c_str());
            datapathNode = initNode(G_PDVL_DATA_DECLARATION_BODY);
            parser_pdvl_data_declaration_body(replaceString, 0, datapathNode);
            if (debug) printf("----------------------------- datapathNode\n");
            if (debug) printTree(datapathNode);
         }
         if (debug) printf("cont here\n");
         NODE* subNode = extractTreeLHS(regOrItemName, NULL, datapathNode);
         if (debug) printf("cont here\n");
         if (subNode != NULL) {
            if (debug) printf("reg|item found: %s\n", regOrItemName.c_str());    
            if (debug) {
               printf("-----------------------------\n");
               printTree(subNode);
            }
            if (1) {
               NODE* returnNode = initNode(G_SV_STATEMENT_OR_NULL);
               NODE* ptrReturnNode = returnNode;
               while (1) {
                  if (ptrReturnNode -> sub != NULL) {
                     ptrReturnNode -> next = initNode(G_SV_STATEMENT_OR_NULL);
                     ptrReturnNode = ptrReturnNode -> next;
                  }
                  NODE* returnSubNode = initSubNode(ptrReturnNode, G_SV_STATEMENT);
                  returnSubNode = initSubNode(returnSubNode, G_SV_STATEMENT_ITEM);
                  returnSubNode -> sub = subNode -> sub;
                  if (subNode -> next == NULL)
                     break;
                  subNode = subNode -> next;
               }
               if (pipeThis > 0) {
                  unsigned min = pipeThis - 1;
                  if (*aboveEdge)
                     min = 0;
                  NODE* newReturnNode = NULL;
                  NODE* newSubNodePtr = NULL;
                  for (int i = min; i < pipeThis; i++) {
                     NODE* tmpSubNode = returnNode;
                     while (1) {
                        NODE* thisNewSubNode = initNode(tmpSubNode -> id);
                        thisNewSubNode -> sub = copyTree(tmpSubNode -> sub);
                        if (newReturnNode == NULL)
                           newReturnNode = thisNewSubNode;
                        else 
                           newSubNodePtr -> next = thisNewSubNode;
                        newSubNodePtr = thisNewSubNode;
                        NODE* lValueNode = getNode(thisNewSubNode, G_SV_VARIABLE_LVALUE);
                        string lValueString = "";
                        writer_sv_variable_lvalue(lValueString, lValueNode -> sub);
                        lValueString.append("_pipe[");
                        lValueString.append(to_string(i));
                        lValueString.append("]"); 
                        maxPtr = 0;
                        parser_sv_variable_lvalue(lValueString, 0, lValueNode);
                        if (debug) printf("lValueString: %s\n", lValueString.c_str());
                        if (tmpSubNode -> next == NULL)
                           break;
                        tmpSubNode = tmpSubNode -> next;
                     }
                  }
                  if (debug) printf("-----------------------------\n");
                  if (debug) printTree(newReturnNode);
                  return newReturnNode;
               }
               return returnNode;  
            } else
            if (1) { //assignmentNode != NULL) {
               NODE* returnNode = initNode(G_SV_STATEMENT_OR_NULL); 
               NODE* returnSubNode = initSubNode(returnNode, G_SV_STATEMENT);
               returnSubNode = initSubNode(returnSubNode, G_SV_STATEMENT_ITEM);
               returnSubNode -> sub = subNode -> sub;
               return returnNode;  
            } else
               exit(-1);
         } else 
         if (debug) {
            printTree(5, datapathNode);
            printf("Empty subNode\n");
         }
      } else
      if (checkSITree(emitNameNode -> sub, condTree -> sub)) {
      } else {
          printf("ERR.CONVERTING.REFERENCE_NOT_FOUND: %s\n", emitName.c_str());
          exit(-1);
      }
   } else
   if (	(transactionNode -> id == G_SV_NONBLOCKING_ASSIGNMENT)            ) {
      string assignLHS = getSI(transactionNode -> sub);
      if (debug) printf("assignLHS: %s\n", assignLHS.c_str()); 
      if (assignLHS.compare(regOrItemName) == 0) {
         NODE* returnNode = initNode(G_SV_STATEMENT_OR_NULL); 
         NODE* returnSubNode = initSubNode(returnNode, G_SV_STATEMENT);
         returnSubNode = initSubNode(returnSubNode, G_SV_STATEMENT_ITEM);
         returnSubNode = initSubNode(returnSubNode, G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT);
         returnSubNode -> sub = transactionNode;
         return returnNode;  
      }
   } else
   if (	(transactionNode -> id == G_SV_PRIMARY) ) {
      printf("Unresolved entry for convertTrans2Process: %d\n", transactionNode -> id);
      printTree(transactionNode);
      exit(-1);
   } else {
      printf("Unresolved entry for convertTrans2Process: %d\n", transactionNode -> id);
      printTree(transactionNode);
      exit(-1);
   }
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
/// Check if source cluster exists
/////////////////////////////////////////////////////////////////////////////////
NODE* checkSourceCluster (NODE* topClusterNameNode, 
                          NODE* subClusterNameNode, 
                          NODE* targetTree) {
   bool debug = false;
   NODE* sourceClusterIdentifierNode = getNode(topClusterNameNode, G_SI);
   NODE* sourceClusterNode = getSITreeNode(sourceClusterIdentifierNode -> sub, dbClusterNode -> sub); 
   unsigned clusterId = 0;
   if (sourceClusterNode == NULL) {
      if (debug) printf("Top source cluster not found in dbClusterNode (join cluster).\n");
   } else {
      if (debug) printf("Top source cluster found in dbClusterNode.\n");
      ///////////////////////////////////////////
      //  Check if hierarchical name
      ///////////////////////////////////////////
      if (subClusterNameNode != NULL) {
         if (debug) printf("-------------------------- subClusterNameNode:\n");
         if (debug) printTree(subClusterNameNode);
         if (debug) printf("-------------------------- sourceClusterNode:\n");
         if (debug) printTree(4, sourceClusterNode);
         while (true) {
            //////////////////////////////////////////////////
            /// Get sub cluster construct
            //////////////////////////////////////////////////
            NODE* clusterDBEntryNode = sourceClusterNode -> sub;
            if (debug) printf("------------------------------------- clusterDBEntryNode: \n");
            if (debug) printTree(4, clusterDBEntryNode);
            bool subClusterFound = false;
            while (true) {                                      
               if (clusterDBEntryNode -> sub != NULL)
               if (clusterDBEntryNode -> sub -> id == G_PDVL_SUB_CLUSTER_DECLARATION) {
                  NODE* subClusterName = getNode(clusterDBEntryNode -> sub -> sub, G_PDVL_CLUSTER_CL_SI);
                  if (subClusterName == NULL)
                     subClusterName = getNode(clusterDBEntryNode -> sub -> sub, G_SI);
                  if (debug) printf("------------------------------------- subClusterName: \n");
                  if (debug) printTree(4, subClusterName);
                  NODE* compareNode = subClusterNameNode -> sub;
                  if (subClusterNameNode -> id != G_SI)
                     compareNode = subClusterNameNode -> sub -> sub;
                  if (debug) printf("------------------------------------- compareNode: \n");
                  if (debug) printTree(4, compareNode);
                  if (checkTree(subClusterName -> sub, compareNode)) {
                     if (debug) printf("found subcluster\n");
                     sourceClusterNode = clusterDBEntryNode -> sub;
                     subClusterFound = true;
                     break;
                  }
               }
               if (clusterDBEntryNode -> next == NULL)
                  break;
               clusterDBEntryNode = clusterDBEntryNode -> next;
            }
            if (!(subClusterNameNode)) {
                if (debug) printf("Source cluster not found in dbClusterNode (join cluster).\n");
                return NULL;
            }
            if (subClusterNameNode -> next == NULL)
               break;
            subClusterNameNode = subClusterNameNode -> next;
         }
      }
      ///////////////////////////////////////////
      //  Check if cluster in target tree
      ///////////////////////////////////////////
      if (sourceClusterNode == NULL) {
         if (debug) printf("Source cluster not found in dbClusterNode.\n");
      } else {
         if (debug) printf("found source cluster in dbClusterNode.\n");
         if (debug) printTree(4, sourceClusterNode);
         /////////////////////////////////
         // check if source cluster is in targetTree
         ///////////////////////////////////
         if (targetTree -> sub != NULL) {
            if (checkSITree(sourceClusterIdentifierNode -> sub, targetTree -> sub)) {
               if (debug) printf("found source cluster in targetTree.\n");
               sourceClusterNode = NULL;
            }
         }
      }
   }
   return sourceClusterNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Check if target cluster exists
/////////////////////////////////////////////////////////////////////////////////
bool checkTargetCluster (NODE* targetNode, 
                         bool join, /* bool incrCluserPtr, unsigned *clCntPtr, */ 
                         NODE* sourceClusterNode) {
   bool debug = false;
   if (debug) printf("---------------------- targetNode:\n");
   if (debug) printTree(targetNode);
   NODE* targetClusterIdentifierNode = getNode(targetNode -> sub, G_SI);
   if (debug) printf("---------------------- targetClusterIdentifierNode:\n");
   if (debug) printTree(targetClusterIdentifierNode);
   NODE* targetClusterNode = getSITreeNode(targetClusterIdentifierNode -> sub, dbClusterNode -> sub);
   if (debug) printf("---------------------- targetClusterNode:\n");
   if (debug) printTree(targetClusterNode);
    
   if (targetClusterNode == NULL) {
      if (debug) printf("returning false\n");
      return false;
   } else
   if (targetNode -> sub -> next == NULL) {
      if (debug) printf("cont\n");
      if (join) 
      if (sourceClusterNode -> sub -> next != NULL) {
         if (debug) printf("---------------------- sourceClusterNode:\n");
         if (debug) printTree(3, sourceClusterNode);
         if (debug) printf("---------------------- targetClusterNode:\n");
         if (debug) printTree(3, targetClusterNode);
         NODE* tmpNode = targetClusterNode -> sub;
         while (tmpNode -> next != NULL)
            tmpNode = tmpNode -> next;
         tmpNode -> next = copyTree(sourceClusterNode -> sub -> next);
      }
   } else {
      if (debug) printf("Target cluster found, continue hierarchical name\n");
      if (debug) printf("-------------------------------------\n");
      NODE* hierarchicalSINode = targetNode -> sub -> next;
      while (true) {
         //////////////////////////////////////////////////
         /// Get sub cluster construct
         //////////////////////////////////////////////////
         NODE* clusterDBEntryNode = targetClusterNode -> sub;
         if (debug) printTree(3, clusterDBEntryNode);
         bool subClusterFound = false;
         while (true) {                                      
            if (clusterDBEntryNode -> sub != NULL)
            if (clusterDBEntryNode -> sub -> id == G_PDVL_SUB_CLUSTER_DECLARATION) {
               NODE* subClusterName = getNode(clusterDBEntryNode -> sub, G_SI);
               if (debug) printTree(3, subClusterName);
               if (checkTree(subClusterName, hierarchicalSINode -> sub)) {
                  if (debug) printf("found subcluster\n");
                  targetClusterNode = clusterDBEntryNode -> sub;
                  subClusterFound = true;
                  break;
               }
            }
            if (clusterDBEntryNode -> next == NULL)
               break;
            clusterDBEntryNode = clusterDBEntryNode -> next;
         }
         if (!(subClusterFound)) {
            if (debug) printf("Target cluster not found in dbClusterNode.\n"); 
            return false;
         }
         if (hierarchicalSINode -> next == NULL) {
            if (join) {
               NODE* tmpNode = targetClusterNode -> sub;
               while (tmpNode -> next != NULL)
                  tmpNode = tmpNode -> next;
               tmpNode -> next = copyTree(sourceClusterNode -> sub -> next);
               if (debug) printf("---------------------- targetClusterNode (exit):\n");
               if (debug) printTree(3, targetClusterNode);
               exit(-1);
            }
            return true;
         }
         hierarchicalSINode = hierarchicalSINode -> next;
      }
   }
   return true;
}
/////////////////////////////////////////////////////////////////////////////////
/// Check target module
/////////////////////////////////////////////////////////////////////////////////
NODE* checkTargetModule (NODE* targetNode, 
                         NODE* modNode) {
   bool debug = false;
   while (1) { 
      if (debug) printf("---------------------targetNode joinBody: \n");
      if (debug) printTree(targetNode);
      modNode = getSubModule(targetNode, modNode);
      if (modNode == NULL) {
         if (debug) printf("modNode == NULL\n");
         return NULL;
      }
      if (targetNode -> next == NULL)
         break;
      targetNode = targetNode -> next;
   }
   return modNode; 
}
/////////////////////////////////////////////////////////////////////////////////
/// Join cluster module
/////////////////////////////////////////////////////////////////////////////////
bool joinClusterModule (NODE* modNode, 
                        NODE* commandBodyNode, 
                        bool incrCluserPtr, 
                        unsigned clusterId, 
                        NODE* sourceClusterNode) {
   bool debug = false;
         NODE* joinedClusterNode = NULL;
            if (debug) printf("Target instantiation found.\n");
            if (modNode -> sub == NULL) {
               joinedClusterNode = initNode(DB_JOINED_CLUSTERS);
               modNode -> sub = joinedClusterNode;
            } else {
               NODE* tmpDBEntryNode = modNode -> sub;
               while (true) {
                  if (tmpDBEntryNode -> id == DB_JOINED_CLUSTERS) {
                     joinedClusterNode = tmpDBEntryNode;
                     break;
                  }
                  if (tmpDBEntryNode -> next == NULL) {
                     // insert at beginning
                     joinedClusterNode = initNode(DB_JOINED_CLUSTERS);
                     joinedClusterNode -> next = modNode -> sub;
                     modNode -> sub = joinedClusterNode;
                     break;
                  }
                  tmpDBEntryNode = tmpDBEntryNode -> next;
               }
            }
         if (joinedClusterNode != NULL) {
            if (debug) printf("Adding cluster to joinedclusterNode.\n");
            if (debug) printTree(joinedClusterNode);
            if (debug) printf("---------------------------- sourceClusterNode\n");
            if (debug) printTree(sourceClusterNode);
            if (debug) printf("---------------------------- commandBodyNode: \n");
            if (debug) printTree(commandBodyNode);
            NODE* nameNode = getNode(commandBodyNode -> sub, G_SI);
            // pass hierarchical name
            while (true) {
               if (nameNode -> next == NULL)
                  break;
               nameNode = nameNode -> next;
            }
            NODE* copiedSourceClusterNode = copyTree(sourceClusterNode);
            if (incrCluserPtr) {
               copiedSourceClusterNode -> id = clusterId;
            }            
            addSITree(nameNode, copiedSourceClusterNode, joinedClusterNode);
            return true;
         }
   return false;
}
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
                  NODE* targetTree) {
   bool debug = false;
   if (debug) printf("joinCluster called.\n");
   if (debug) printTree(commandBodyNode);
   bool cont = false; 
   NODE* sourceClusterNode = NULL;
   unsigned clusterId = 0;
   ///////////////////////////////////////////
   //  G_PDVL_JOIN_CLUSTER_SINGLE_COMMAND
   ///////////////////////////////////////////
   if (commandBodyNode -> id == G_PDVL_JOIN_CLUSTER_SINGLE_COMMAND) {
      ///////////////////////////////////////////
      //  Check if executable and execute
      //  1) source cluster exists and is not in targetTree
      ///////////////////////////////////////////
      commandBodyNode = commandBodyNode -> sub;
      if (debug) printTree(commandBodyNode);
      sourceClusterNode = checkSourceCluster(commandBodyNode -> sub, commandBodyNode -> sub -> next, targetTree);
      if (sourceClusterNode == NULL) {
         string clusterName = getSI(commandBodyNode -> sub);
         if (debug) printf("ERR.JOINING.CLUSTER_NOT_FOUND: %s\n", clusterName.c_str());
         
         *clCntPtr = *clCntPtr + 1;
         if (debug) printTree(commandBodyNode);
         if (reportLevel > 2) {
            printf("2.1.1 Saving cluster %s (%d) into database.\n", clusterName.c_str(), *clCntPtr);
         }
         NODE* newClusterCnt = initNode(*clCntPtr);
         NODE* newClusterCntSub = initSubNode(newClusterCnt, 0);
         parser_pdvl_cluster_identifier(clusterName, 0, newClusterCntSub);
         if (debug) printTree(newClusterCnt);
         addSITree(commandBodyNode -> sub, newClusterCnt, dbClusterNode);
         if (debug) printTree(7, dbClusterNode);
         sourceClusterNode = checkSourceCluster(commandBodyNode -> sub, commandBodyNode -> sub -> next, targetTree);
         if (debug) printTree(7, sourceClusterNode);
      }
      if (sourceClusterNode == NULL) {
         return false;
      }
      ///////////////////////////////////////////
      //  2a) no target exists => place in module
      ///////////////////////////////////////////
      if (debug) printf("check if target exists.\n");
      if (commandBodyNode -> next == NULL) { 
         if (debug) printf("join source cluster into this module.\n");
         NODE* dbEntryNode = modNode -> sub;
         while (true) {
            if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
            if (dbEntryNode -> id == DB_JOINED_CLUSTERS) {
               NODE* copiedSourceClusterNode = copyTree(sourceClusterNode);
               *clCntPtr = *clCntPtr + 1;
               copiedSourceClusterNode -> id = *clCntPtr;
               if (debug) printTree(copiedSourceClusterNode);
               addSITree(getNode(commandBodyNode -> sub, G_SI), copiedSourceClusterNode, dbEntryNode);
               return true;
            }
            if (dbEntryNode -> next == NULL) {
               // insert at beginning
               dbEntryNode = initNode(DB_JOINED_CLUSTERS);
               dbEntryNode -> next = modNode -> sub;
               modNode -> sub = dbEntryNode;
            } else  
               dbEntryNode = dbEntryNode -> next;
         }
         if (debug) printf("join source cluster into this module done.\n");
      } else {
         ///////////////////////////////////////////
         //  2b) target exists and is a cluster
         ///////////////////////////////////////////
         if (debug) printf("check if target is cluster.\n");
         if (checkTargetCluster(commandBodyNode -> next, true, sourceClusterNode)) {
            if (debug) printf("returning true\n");
            return true;
         } else {
            ///////////////////////////////////////////
            //  2c) target exists and is a module
            ///////////////////////////////////////////
            if (debug) printf("check if target is module.\n");
            NODE* newModNode = checkTargetModule(commandBodyNode -> next -> sub, modNode);
            if (newModNode != NULL) {
               if (debug) printf("Target is module.\n");
               if (debug) printf("---------------------- sourceClusterNode:\n");
               if (debug) printTree(4, sourceClusterNode);
               *clCntPtr = *clCntPtr + 1;
               if (joinClusterModule(newModNode, commandBodyNode, true, *clCntPtr, sourceClusterNode)) {
                  if (debug) printf("---------------------- newModNode:\n");
                  if (debug) printTree(6, newModNode);
                  return true;
               }
            }
            return false;
         }
      }
   ///////////////////////////////////////////
   //  G_PDVL_JOIN_CLUSTER_BODY_COMMAND
   ///////////////////////////////////////////
   } else 
   if (commandBodyNode -> sub != NULL)
   if (commandBodyNode -> sub -> next != NULL) {
      if (debug) printf("---------------------- commandBodyNode:\n");
      if (debug) printTree(commandBodyNode);
      ///////////////////////////////////////////
      //  Check if all executable
      //  1) source cluster exists and is not in targetTree
      ///////////////////////////////////////////
      NODE* subCommandNode = commandBodyNode -> sub -> next;
      while (true) {
         if (debug) printf("---------------------- subCommandNode (check):\n");
         if (debug) printTree(subCommandNode);
         ///////////////////////////////////////////
         //  Check if subCommandNode executable
         //  1) source cluster exists and is not in targetTree
         ///////////////////////////////////////////
         NODE* sourceClusterNode = checkSourceCluster(commandBodyNode -> sub, subCommandNode -> sub -> sub, targetTree);
         if (sourceClusterNode == NULL) {
            return false;
         }
         if (subCommandNode -> sub -> next == NULL) { 
         } else {
            ///////////////////////////////////////////
            //  2b) target exists and is a cluster
            ///////////////////////////////////////////
            if (debug) printf("check if target is cluster a.\n");
            if (checkTargetCluster(subCommandNode -> sub -> next, false, /*true, clCntPtr,*/ NULL)) {
            } else {
               ///////////////////////////////////////////
               //  2c) target exists and is a module
               ///////////////////////////////////////////
               if (debug) printf("check if target is module.\n");
               NODE* newModNode = checkTargetModule(subCommandNode -> sub -> next -> sub, modNode);
               if (newModNode == NULL)
                  return false;
            }
         }
         if (subCommandNode -> next == NULL)
            break;
         subCommandNode = subCommandNode -> next;
      }
      ///////////////////////////////////////////
      //  Execute command
      ///////////////////////////////////////////
      subCommandNode = commandBodyNode -> sub -> next;
      *clCntPtr = *clCntPtr + 1;
      unsigned clusterId = *clCntPtr;
      while (true) {
         if (debug) printf("---------------------- subCommandNode (execute):\n");
         if (debug) printTree(subCommandNode);
         ///////////////////////////////////////////
         //  1) get source cluster 
         ///////////////////////////////////////////
         NODE* sourceClusterNode = checkSourceCluster(commandBodyNode -> sub, subCommandNode -> sub -> sub, targetTree);
         if (subCommandNode -> sub -> next == NULL) { 
            if (debug) printf("join source cluster into this module.\n");
            NODE* dbEntryNode = modNode -> sub;
            while (true) {
               if (dbEntryNode -> id == DB_JOINED_CLUSTERS) {
                  NODE* copiedSourceClusterNode = copyTree(sourceClusterNode);
                  copiedSourceClusterNode -> id = clusterId;
                  addSITree(getNode(commandBodyNode -> sub, G_SI), copiedSourceClusterNode, dbEntryNode);
                  break;
               }
               if (dbEntryNode -> next == NULL) {
                  // insert at beginning
                  dbEntryNode = initNode(DB_JOINED_CLUSTERS);
                  dbEntryNode -> next = modNode -> sub;
                  modNode -> sub = dbEntryNode;
               } else  
                  dbEntryNode = dbEntryNode -> next;
            }
         } else {
            ///////////////////////////////////////////
            //  2b) target exists and is a cluster
            ///////////////////////////////////////////
            if (debug) printf("check if target is cluster b.\n");
            if (checkTargetCluster(subCommandNode -> sub -> next, true, sourceClusterNode)) {
            } else {
               ///////////////////////////////////////////
               //  2c) target exists and is a module
               ///////////////////////////////////////////
               if (debug) printf("add to new module.\n");
               NODE* newModNode = checkTargetModule(subCommandNode -> sub -> next -> sub, modNode);
               joinClusterModule(newModNode, commandBodyNode, true, clusterId, sourceClusterNode);
            }
         }
         if (subCommandNode -> next == NULL)
            break;
         subCommandNode = subCommandNode -> next;
      }
      return true;
   }
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
/// Join PDVL body
/////////////////////////////////////////////////////////////////////////////////
bool joinBody (NODE* commandBodyNode, 
               NODE* modNode, 
               unsigned *clCntPtr) {
   bool debug = false;
   if (debug) printf("-------------------------------------\n");
   if (debug) printTree(commandBodyNode);
   NODE* sourceBodyNode = commandBodyNode -> sub;
      ///////////////////////////////////
      // join cluster\body into something other than this module
      ///////////////////////////////////
      bool hierarchical = false;
      if (commandBodyNode -> next != NULL)   
      if (commandBodyNode -> next -> id == G_HIERARCHICAL_NAME)
         hierarchical = true;
      if (hierarchical) {
         NODE* targetClusterNode = NULL;
         if (dbClusterNode -> sub != NULL) {
            NODE* targetClusterIdentifierNode = getNode(commandBodyNode -> next -> sub, G_SI);
            targetClusterNode = getSITreeNode(targetClusterIdentifierNode -> sub, dbClusterNode -> sub);

            if (targetClusterNode != NULL)
            if (commandBodyNode -> next -> sub -> next != NULL) {
               if (debug) printf("-------------------------------------\n");
               NODE* hierarchicalSINode = commandBodyNode -> next -> sub -> next;
               while (true) {
                  //////////////////////////////////////////////////
                  /// Get sub cluster construct
                  //////////////////////////////////////////////////
                  NODE* clusterDBEntryNode = targetClusterNode -> sub;
                  if (debug) printTree(clusterDBEntryNode);
                  bool subClusterFound = false;
                  while (true) {                                      
                     if (clusterDBEntryNode -> sub != NULL)
                     if (clusterDBEntryNode -> sub -> id == G_PDVL_SUB_CLUSTER_DECLARATION) {
                        NODE* subClusterName = getNode(clusterDBEntryNode -> sub, G_SI);
                        if (debug) printTree(subClusterName);
                        if (checkTree(subClusterName, hierarchicalSINode -> sub)) {
                           if (debug) printf("found subcluster\n");
                           targetClusterNode = clusterDBEntryNode -> sub;
                           subClusterFound = true;
                           break;
                        }
                     }
                     if (clusterDBEntryNode -> next == NULL)
                        break;
                     clusterDBEntryNode = clusterDBEntryNode -> next;
                  }
                  if (!(subClusterFound)) {
                     if (debug) printf("Target cluster not found in dbClusterNode.\n"); 
                     return false;
                  }
                  if (hierarchicalSINode -> next == NULL) {
                     NODE* tmpNode = targetClusterNode -> sub;
                     while (tmpNode -> next != NULL)
                        tmpNode = tmpNode -> next;
                     tmpNode -> next = copyTree(sourceBodyNode);
                     return true;
                  }
                  hierarchicalSINode = hierarchicalSINode -> next;
               }
            }
         }
         ///////////////////////////////////
         // target cluster found
         ///////////////////////////////////
         if (targetClusterNode != NULL) {
            if (debug) printf("Target cluster found\n");
            if (debug) printTree(targetClusterNode);     
            if (targetClusterNode -> sub != NULL) {
               NODE* tmpNode = targetClusterNode -> sub;
               while (tmpNode -> next != NULL)
                  tmpNode = tmpNode -> next;
               tmpNode -> next = copyTree(sourceBodyNode);
               return true;
               if (debug) printTree(targetClusterNode);     
            }
            exit(-1);
         }
         ///////////////////////////////////
         // target cluster not found yet
         // check target is an instantiation
         ///////////////////////////////////
         NODE* targetModuleHierNode = commandBodyNode -> next -> sub;
         if (targetModuleHierNode != NULL) 
         while (1) { 
             if (debug) printf("---------------------targetModuleHierNode joinBody: \n");
             if (debug) printTree(targetModuleHierNode);
             if (debug) printf("---------------------modNode: \n");
             if (debug) printTree(4, modNode);
             modNode = getSubModule(targetModuleHierNode, modNode);
             if (modNode == NULL) {
                if (debug) printf("modNode == NULL\n");
                return false;
             }
             if (targetModuleHierNode -> next == NULL)
                break;
             targetModuleHierNode = targetModuleHierNode -> next;
         } 
         if (debug) printf("-------------------------------- cont:\n");
         NODE* joinedClusterNode = NULL;
         if (modNode != NULL) {
            if (debug) printf("Target instantiation found.\n");
            if (debug) printTree(modNode);
            if (modNode -> sub == NULL) {
               joinedClusterNode = initNode(DB_JOINED_CLUSTERS);
               modNode -> sub = joinedClusterNode;
            } else {
               NODE* tmpDBEntryNode = modNode -> sub;
               while (true) {
                  if (tmpDBEntryNode -> id == DB_JOINED_CLUSTERS) {
                     joinedClusterNode = tmpDBEntryNode;
                     break;
                  }
                  if (tmpDBEntryNode -> next == NULL) {
                     // insert at beginning
                     joinedClusterNode = initNode(DB_JOINED_CLUSTERS);
                     joinedClusterNode -> next = tmpDBEntryNode -> next;
                     tmpDBEntryNode -> next = joinedClusterNode;
                     break;
                  }
                  tmpDBEntryNode = tmpDBEntryNode -> next;
               }
            }
         }
         if (joinedClusterNode != NULL) {
            if (debug) printf("Adding cluster to joinedclusterNode.\n");
            *clCntPtr = *clCntPtr + 1;
            NODE* sourceBodyIDNode = initNode(*clCntPtr);
            sourceBodyIDNode -> sub = copyTree(sourceBodyNode);
            if (debug) printTree(sourceBodyIDNode);
            addSITree(getNode(commandBodyNode -> sub, G_SI), sourceBodyIDNode, joinedClusterNode);
            if (debug) printf("---------------------- joinedClusterNode:\n");
            if (debug) printTree(joinedClusterNode);
            if (debug) printf("----------------------\n");
            return true;
         }
       ///////////////////////////////////
       // join cluster\body into this module
       ///////////////////////////////////
       } else {
          if (debug) printf("join body into this module.\n");
          NODE* dbEntryNode = modNode -> sub;
          while (true) {
             if (dbEntryNode -> id == DB_JOINED_CLUSTERS) {
                if (debug) printf("found joined cluster entry.\n");
                addSITree(getNode(commandBodyNode -> sub, G_SI), copyTree(sourceBodyNode), dbEntryNode);
                return true;
             }
             if (dbEntryNode -> next == NULL) {
                // insert at beginning
                NODE* dbSubNode = initNode(DB_JOINED_CLUSTERS);
                *clCntPtr = *clCntPtr + 1;
                NODE* sourceBodyIDNode = initNode(*clCntPtr);
                sourceBodyIDNode -> sub = copyTree(sourceBodyNode);
                dbSubNode -> next = modNode -> sub;
                modNode -> sub = dbSubNode;
                addSITree(getNode(commandBodyNode -> sub, G_SI), sourceBodyIDNode, dbSubNode);
                return true;
             }  
             dbEntryNode = dbEntryNode -> next;
          }
       }
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
///  Checks the complete tree, if NODE with given id exists.
/////////////////////////////////////////////////////////////////////////////////
bool checkConstructTreeNode (NODE* node, 
                             unsigned dbID) {
   if (node -> id == dbID) return true;
   if (node -> next != NULL) 
      if (checkConstructTreeNode(node -> next, dbID))
         return true;
   if (node -> sub != NULL) 
      if (checkConstructTreeNode(node -> sub, dbID))
         return true;
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
///  Checks all NODEs on this "next" level, if NODE with given id exists.
/////////////////////////////////////////////////////////////////////////////////
bool checkConstructListNode (NODE* node, 
                             unsigned dbID) {
   if (node -> id == dbID) return true;
   if (node -> next != NULL) return checkConstructListNode(node -> next, dbID); 
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
/// Join PDVL construct
/////////////////////////////////////////////////////////////////////////////////
void joinConstruct (NODE* modNode, 
                    NODE* tmpSubNode, 
                    unsigned clusterId, 
                    unsigned dbID) {
   bool debug = false;
   NODE* dbEntryNode;
   if (modNode -> sub == NULL) {
      dbEntryNode = initNode(dbID);
      modNode -> sub = dbEntryNode;
   } else {
      dbEntryNode = modNode -> sub;
      while (1) {
         if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
         if (dbEntryNode -> id == dbID)
            break;
         if (dbEntryNode -> next == NULL) {
            dbEntryNode = initNode(dbID);
            dbEntryNode -> next = modNode -> sub;
            modNode -> sub = dbEntryNode;
            break;
         }
         dbEntryNode = dbEntryNode -> next;
      }
   }
   NODE* clusterIDNode;
   if (dbEntryNode -> sub == NULL) {
      clusterIDNode = initNode(clusterId);
      dbEntryNode -> sub = clusterIDNode;
   } else {
      clusterIDNode = dbEntryNode -> sub;
      while (1) {
         if (debug) printf("clusterIDNode: %d\n", clusterIDNode -> id);
         if (clusterIDNode -> id == clusterId)
            break;
         if (clusterIDNode -> next == NULL) {
            clusterIDNode = initNode(clusterId);
            clusterIDNode -> next = dbEntryNode -> sub;
            dbEntryNode -> sub = clusterIDNode;
            break;
         }
         clusterIDNode = clusterIDNode -> next;
      }
   }
   ////////////////////////////////
   // check if tree already exists
   ////////////////////////////////
   if (clusterIDNode -> sub != NULL) {
      NODE* subClusterIDNode = clusterIDNode -> sub;
      while (true) {
         if (debug) printf("compare %d %d\n", subClusterIDNode -> id, tmpSubNode -> id);
         if (subClusterIDNode -> id == tmpSubNode -> id) {
            if (subClusterIDNode -> sub == NULL)
            if (tmpSubNode -> sub == NULL) {
               if (debug) printf("match found\n");
               return;
            }
            if (subClusterIDNode -> sub != NULL)
            if (tmpSubNode -> sub != NULL) {
               if (debug) printTree(subClusterIDNode -> sub);
               if (debug) printTree(tmpSubNode -> sub);
               if (checkTree(subClusterIDNode -> sub, tmpSubNode -> sub)) {
                  if (debug) printf("match found\n");
                  return;
               }
            }             
         }
         if (subClusterIDNode -> next == NULL)
            break;
         subClusterIDNode = subClusterIDNode -> next;
      }
   }
   tmpSubNode -> next = clusterIDNode -> sub;
   clusterIDNode -> sub = tmpSubNode;
   if (debug) printf("---------------------------\n");
   if (debug) printTree(tmpSubNode);
}
/////////////////////////////////////////////////////////////////////////////////
/// Searches for cluster (getCluster) and copies it (copyTree).
/// Then calls modifyAllEntriesName to add prefix.
/////////////////////////////////////////////////////////////////////////////////
bool uniquifyCluster (NODE* commandBodyNode, 
                      NODE* targetTree, 
                      NODE* newClustersNode, 
                      unsigned* clCnt) {
   bool debug = false;
   bool cont = false;
   NODE* sourceClusterIdentifierNode = getNode(commandBodyNode, G_SI);
   if (debug) printTree(sourceClusterIdentifierNode);
   NODE* sourceClusterNode = getSITreeNode(sourceClusterIdentifierNode -> sub, dbClusterNode -> sub);
   if (sourceClusterNode == NULL) {
      if (debug) printf("Source cluster not found in dbClusterNode (uniquify).\n");
   } else {
      if (debug) printf("found source cluster in dbClusterNode.\n");
      /////////////////////////////////
      // check if source cluster is in targetTree
      ///////////////////////////////////
      if (targetTree -> sub != NULL) {
         if (checkSITree(sourceClusterIdentifierNode -> sub, targetTree -> sub)) {
            if (debug) printf("found source cluster in targetTree.\n");
         } else
               cont = true;
      } else
            cont = true;
   }
   if (cont) {
      if (debug) printf("cont.\n");
      *clCnt = *clCnt + 1;
      string clusterName = getSI(sourceClusterIdentifierNode);
      if (debug) printf("Uniquify cluster %s (%d).\n", clusterName.c_str(), *clCnt);
      NODE* newCluster = initNode(*clCnt);
      newCluster -> sub = copyTree(sourceClusterNode -> sub);
      string prefix = "";
      string postfix = "";
      printLexNode(prefix, commandBodyNode -> next -> sub);
      if (debug) printf("prefix: %s\n", prefix.c_str());
      NODE* skipTree = initNode(0);
      if (debug) printTree(newCluster);
      modifyAllEntriesName(newCluster, prefix, postfix, skipTree);
      NODE* newClusterNameNode = getNode(newCluster, G_SI);
      addSITree(newClusterNameNode, newCluster, newClustersNode);
      return true;
   }
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
/// Searches for all NODE with specific ids within the complete tree.
/// Then adds pre and postfix to the simple identifier below.
/////////////////////////////////////////////////////////////////////////////////
void modifyAllEntriesName (NODE* node, 
                           string &prefix, 
                           string &postfix, 
                           NODE* skipTree) {
   bool debug = false;
   if (debug) printf("modifyAllEntriesName: %d\n", node -> id);
   if (	(node -> id == G_SV_ATTR_SPEC) |
  		(node -> id == G_SV_NUMBER) 		   	 ) {
      return;
   } else
   if (	(node -> id == G_PDVL_FOREACH_DECLARATION)	|
        (node -> id == G_PDVL_FOREACH_COMMAND)		|
        (node -> id == G_SV_LOOP_FOR_STATEMENT)	) {
      if (node -> sub != NULL) {
         addSITree(node -> sub, NULL, skipTree);
         if (node -> sub -> next != NULL) modifyAllEntriesName(node -> sub -> next, prefix, postfix, skipTree); }
   } else
   if (	
  		(node -> id == G_SI) 						|
  		(node -> id == G_PDVL_EVENT_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_DATA_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME) 	) {
      if (debug) printTree(node);
      string entryName = getSI(node);   
      if (!(checkTree(entryName, skipTree))) { 
         string newEntryName = prefix;
         newEntryName.append(entryName);
         newEntryName.append(postfix);
         deleteTree(node -> sub); 
         NODE* newNode = initNode(0);
         parser_si(newEntryName, 0, newNode);
         node -> sub = newNode -> sub;
         delete newNode; }
   } else
   if (	(node -> id == G_SV_GENVAR_IDENTIFIER) 	) {
      if (debug) printTree(node);
      string entryName = getSI(node);   
      if (!(checkTree(entryName, skipTree))) { 
         string newEntryName = prefix;
         newEntryName.append(entryName);
         newEntryName.append(postfix);
         deleteTree(node -> sub); 
         NODE* newNode = initNode(0);
         parser_si(newEntryName, 0, newNode);
         node -> sub = newNode;
      }
   } else
      if (node -> sub != NULL) modifyAllEntriesName(node -> sub, prefix, postfix, skipTree);
   if (node -> next != NULL) modifyAllEntriesName(node -> next, prefix, postfix, skipTree);
}
/////////////////////////////////////////////////////////////////////////////////
/// Searches for all NODE with specific ids within the complete tree.
/// Then replaces a substring with a given replacement string.
/////////////////////////////////////////////////////////////////////////////////
void replaceIndexName (NODE* node, 
                       bool exact, 
                       string &indexNameString, 
                       string &indexValueString) {
   bool debug = false;
   if (debug) printf("replaceIndexName: %d\n", node -> id);
   ////////////////////////////////////////////
   // no exact match needed, modify:
   // i
   // ...._i
   // ..._i_...
   ////////////////////////////////////////////
   if (!(exact))
   if (	(node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_DATA_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_SI) 						) {
      string entryName = getSI(node);   
      if (debug) printf("replaceIndexName: %s\n", entryName.c_str());
      string testString = "_";
      testString.append(indexNameString);
      size_t pos = 0;
      if (entryName.length() > testString.length())
         pos = entryName.length() - testString.length();
      size_t x = entryName.find(testString, pos);
      
      if (debug) printf("replaceIndexName: %s %s %d\n", entryName.c_str(), testString.c_str(), x);
      if (x != string::npos) {                  
         string newString = "_";
         newString.append(indexValueString);
         entryName.replace(x, x + indexNameString.length(), newString); 
         if (debug) printf("replaceIndexName: %s %s %d\n", entryName.c_str(), testString.c_str(), x);
         deleteTree(node -> sub); 
         NODE* newNode = initNode(0);
         parser_si(entryName, 0, newNode);
         node -> sub = newNode -> sub;
         delete newNode;
      } else {
         testString.append("_");
         pos = 0;
         x = entryName.find(testString, pos);
         if (debug) printf("replaceIndexName: %s %s %d\n", entryName.c_str(), testString.c_str(), x);
         if (x != string::npos)
         while (1) {
            if (entryName.find(testString, x + 1) != string::npos)
               x = entryName.find(testString, x + 1);
            else
               break; 
         }
         if (x != string::npos) {
            // space is added at end of indexValue                  
            entryName.replace(x + 1, indexValueString.length(), indexValueString); //.substr(0, indexValueString.length() - 1)); 
            if (debug) printf("replaceIndexName: %s %s %d\n", entryName.c_str(), testString.c_str(), x);
            deleteTree(node -> sub); 
            NODE* newNode = initNode(0);
            parser_si(entryName, 0, newNode);
            node -> sub = newNode -> sub;
            delete newNode;
         }
      }
   } 
   ////////////////////////////////////////////
   // exact match needed, modify:
   // i
   // sub of G_PDVL_CONSTANT_PRIMARY differs
   ////////////////////////////////////////////
   if (	(node -> id == G_SV_CONSTANT_PRIMARY)   ) {
      string entryName = "";   
      writer_sv_constant_primary(entryName, node -> sub);
      size_t x = entryName.find(indexNameString);

      if (entryName.length() == indexNameString.length() + 1)
      if (x != string::npos) {
         if (debug) printf("replaceIndexName: %s %s %d %d %d\n", entryName.c_str(), indexNameString.c_str(), x, entryName.length(), indexNameString.length());
         NODE* newNode = initNode(0);
         string newString = indexValueString;
         newString.append(" ");
         parser_sv_constant_primary(newString, 0, newNode);
         if (debug) printTree(node);
         if (debug) printf("--------------------\n");
         if (debug) printTree(newNode);
         node -> sub = newNode -> sub; 
      }
   } else
   if (	(node -> id == G_SV_VARIABLE_LVALUE)    |
        (node -> id == G_SV_GENVAR_IDENTIFIER)  |
        (node -> id == G_SV_INDEX_VARIABLE_IDENTIFIER) ) {
      string entryName = "";   
      //writer_sv_primary_identifier(entryName, node -> sub);
      writer_sv_index_variable_identifier(entryName, node -> sub);
      size_t x = entryName.find(indexNameString);
      if (debug) printf("primary replaceIndexName: %s %s %d %d %d\n", entryName.c_str(), indexValueString.c_str(), x, entryName.length(), indexNameString.length());
      ///////////////////////////////
      // exact match
      ///////////////////////////////
      if ( (entryName.length() == indexNameString.length() + 1) &
           (x != string::npos)                                  ) {
         if (debug) printf("primary replaceIndexName: %s %s %d %d %d\n", entryName.c_str(), indexValueString.c_str(), x, entryName.length(), indexNameString.length());
         NODE* newNode = initNode(0);
         string newString = indexValueString;
         newString.append(" ");
         parser_sv_index_variable_identifier(newString, 0, newNode);
         if (debug) printTree(newNode);
         if (newNode -> sub == NULL) {
            parser_sv_primary_literal(newString, 0, newNode);
            node -> id = G_SV_NUMBER;
            node -> sub = newNode -> sub -> sub; 
         } else
            node -> sub = newNode -> sub; 
         if (debug) printf("-------------------- node:\n");
         if (debug) printTree(node);
      } else if (0)
      if (!(exact)) {
         string testString = "_";
         testString.append(indexNameString);
         size_t pos = 0;
         if (entryName.length() > testString.length())
            pos = entryName.length() - testString.length();
         size_t x = entryName.find(testString, pos);
      
         if (debug) printf("replaceIndexName: %s %s %d\n", entryName.c_str(), testString.c_str(), x);
         if (x != string::npos) {                  
            string newString = "_";
            newString.append(indexValueString);
            entryName.replace(x, x + indexNameString.length(), newString); 
            if (debug) printf("replaceIndexName: %s %s %d\n", entryName.c_str(), testString.c_str(), x);
            deleteTree(node -> sub); 
            NODE* newNode = initNode(0);
            parser_si(entryName, 0, newNode);
            node -> sub = newNode;
         }
      }
   } 
   if (node -> sub != NULL) replaceIndexName(node -> sub, exact, indexNameString, indexValueString);
   if (node -> next != NULL) replaceIndexName(node -> next, exact, indexNameString, indexValueString);
}
/////////////////////////////////////////////////////////////////////////////////
/// Add wire to module entry
/////////////////////////////////////////////////////////////////////////////////
void addWire (string &signalName, 
              NODE* typeNode, 
              NODE* topModuleNode) {
   bool debug = false;
   if (debug) printf("addWire %s\n", signalName.c_str());
   if (debug) printf("topModuleNode -> id %d\n", topModuleNode -> id);
   
   string itemDeclaration = "";
   writeDeclaration(itemDeclaration, 1, signalName, typeNode);
   itemDeclaration.append("; ");
   if (debug) printf("%s\n", itemDeclaration.c_str());

   if (debug) printf("addWire: %s\n", itemDeclaration.c_str());
   if (debug) 
   if (typeNode != NULL) {
      printf("---------------------------- typeNode:\n");
      printTree(typeNode);
   }
   
   NODE* itemDeclarationNode = initNode(DB_SIGNAL_DECLARATION);
   maxPtr = 0;
   parser_sv_net_declaration(itemDeclaration, 0, itemDeclarationNode);

   if (itemDeclarationNode -> sub == NULL) { 
      itemDeclaration = "";
      writeDeclaration(itemDeclaration, 3, signalName, typeNode);
      itemDeclaration.append("; ");
      parser_sv_data_declaration(itemDeclaration, 0, itemDeclarationNode);
   }
   
   // wire entry shoule be split into signal name and DB_SIGNAL_TYPE   
   
   if (debug) printTree(itemDeclarationNode);
   if (debug) 
   if (typeNode != NULL) {
      printf("addWire: %s\n", itemDeclaration.c_str());
      printf("---------------------------- itemDeclarationNode: %d\n", maxPtr);
      printTree(itemDeclarationNode);
   }
   // cluster ID not relevant anymore       
   joinConstruct(topModuleNode, itemDeclarationNode, 0x7fffffff, DB_MODULE_WIRES);

}
/////////////////////////////////////////////////////////////////////////////////
/// Add port, simple, level 2
/////////////////////////////////////////////////////////////////////////////////
void addPortSimpleLevel2 (string pathSignalName, 
                          string signalName, 
                          bool trueLHSfalseRHS, 
                          NODE* typeNode, 
                          NODE* modNode, 
                          unsigned *clCntPtr) {
   bool debug = false;
   
   NODE* dbEntryNode = modNode -> sub;
   NODE* dbModuleItemsNode = NULL;
   NODE* dbModuleRegistersNode = NULL;
   NODE* dbModuleLatchesNode = NULL;
   NODE* signalPtrNode = NULL;
   NODE* pathSignalPtrNode = NULL;
   bool isCond = false;
   while (true) {
      if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
      if ( (dbEntryNode -> id == DB_MODULE_ITEMS)      |
           (dbEntryNode -> id == DB_MODULE_REGISTERS)  |
           (dbEntryNode -> id == DB_MODULE_LATCHES)    |
           (dbEntryNode -> id == DB_MODULE_CONDITIONS) ) {
         if (dbEntryNode -> id == DB_MODULE_ITEMS)
            dbModuleItemsNode = dbEntryNode;
         NODE* tmpClNode = dbEntryNode -> sub;
         while (1) {
            if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
            NODE* tmpNode = tmpClNode -> sub;
            while (1) {
               if (debug) printf("tmpNode: %d\n", tmpNode -> id);
               if (tmpNode -> sub != NULL) {
                  string itemName = getSI(tmpNode -> sub);
                  if (pathSignalName.compare(itemName) == 0) {
                     pathSignalPtrNode = tmpNode;
                     if (dbEntryNode -> id == DB_MODULE_CONDITIONS)
                       isCond = true;
                  }
                  if (signalName.compare(itemName) == 0) {
                     signalPtrNode = tmpNode;
                  }
               }
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }                     
            if (tmpClNode -> next == NULL)
               break;
            tmpClNode = tmpClNode -> next;
         }                     
      }
      if (dbEntryNode -> next == NULL)
         break;
      dbEntryNode = dbEntryNode -> next;
   }
   
   /////////////////////////////////////
   //  Check if signal exists
   /////////////////////////////////////
   if (pathSignalPtrNode == NULL) {
      printf("ERR.ROUTE.COMMAND.SIGNAL_NOT_FOUND: %s\n", pathSignalName.c_str());
      exit(-1);
   } else
   /////////////////////////////////////
   //  Pick-up type of driver
   /////////////////////////////////////
   if (typeNode -> sub == NULL) {
      NODE* signalTypeNode = getNodeSubLevel(pathSignalPtrNode, DB_SIGNAL_TYPE);
      if (signalTypeNode != NULL)
         typeNode -> sub = signalTypeNode -> sub;
   }
   /////////////////////////////////////
   //  Generate new item entry for assignment
   //  important: must have new cluster ID
   /////////////////////////////////////
   if (dbModuleItemsNode == NULL) {
      dbModuleItemsNode = initNode(DB_MODULE_ITEMS);
      dbEntryNode -> next = dbModuleItemsNode;
   }
   *clCntPtr = *clCntPtr + 1;
   NODE* clNode = initNode(*clCntPtr);
   if (dbModuleItemsNode -> sub == NULL) {
      dbModuleItemsNode -> sub = clNode;
   } else {
      clNode -> next = dbModuleItemsNode -> sub;
      dbModuleItemsNode -> sub = clNode;
   }
   NODE* itemDeclarationNode = initNode(G_PDVL_ITEM_DECLARATION);
   itemDeclarationNode -> next = clNode -> sub;
   clNode -> sub = itemDeclarationNode;
               
   NODE* signalNameNode = initNode(DB_LIST_ENTRY);
   string tmpSignalName = signalName;
   maxPtr = 0;
   if (trueLHSfalseRHS) {
      int ptr = parser_si(pathSignalName, 0, signalNameNode);
      itemDeclarationNode -> sub = signalNameNode;
   } else {
      int ptr = parser_si(tmpSignalName, 0, signalNameNode);
      itemDeclarationNode -> sub = signalNameNode;
   }
               
   if (typeNode -> sub != NULL) {
      if (debug) printf("----------------------------typeNode:\n");
      if (debug) printTree(typeNode);
      NODE* selectNode = initNode(DB_SIGNAL_TYPE);
      signalNameNode -> next = selectNode;
      signalNameNode = signalNameNode -> next;
      selectNode -> sub = typeNode -> sub;
   }

   /////////////////////////////////////
   //  Connect target
   /////////////////////////////////////
   if (trueLHSfalseRHS) {
      if (debug) printf("Connect target %s and %s rhs: %d\n", pathSignalName.c_str(), signalName.c_str(), trueLHSfalseRHS);
      if (debug) printTree(5, pathSignalPtrNode);
      /////////////////////////////////////
      //  remove old condition's DB_CONE
      /////////////////////////////////////
      if (isCond) {
         if (pathSignalPtrNode != NULL) {
            NODE* tmpNode = pathSignalPtrNode -> sub;
            while (true) {
               if (tmpNode -> id == DB_CONE)
                  tmpNode -> id = 1;
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
         }
         if (debug) printf("---------------------- pathSignalPtrNode: \n");
         if (debug) 
         if (pathSignalPtrNode != NULL)
            printTree(pathSignalPtrNode);
         if (debug) printf("---------------------- signalPtrNode: \n");
         if (debug) 
         if (signalPtrNode != NULL)
            printTree(signalPtrNode);
      }
      string procedureString;
      procedureString = "always_comb begin ";
      procedureString.append(pathSignalName);
      procedureString.append(" = ");
      procedureString.append(signalName);
      procedureString.append (" ; end ");
      maxPtr = 0;
      NODE* subNode = initNode(0);
      parser_sv_always_construct(procedureString, 0, subNode);
      if (debug) printf("%s\n", procedureString.c_str());
      if (debug) printTree(5, subNode);  
      NODE* coneNode = getConstructListFirstNode(itemDeclarationNode -> sub, DB_CONE);
      coneNode -> sub = subNode;
      if (signalPtrNode == NULL) {
         /////////////////////////////////////
         //  Add DB_ROUTED for "output from sub - problem"
         /////////////////////////////////////
         *clCntPtr = *clCntPtr + 1;
         NODE* newClNode = initNode(*clCntPtr); 
         newClNode -> next = clNode -> next;
         clNode -> next = newClNode;
                  
         NODE* newItemDeclarationNode = initNode(G_PDVL_ITEM_DECLARATION);
         newItemDeclarationNode -> next = newClNode -> sub;
         newClNode -> sub = newItemDeclarationNode;
                 
         NODE* newSignalNameNode = initNode(DB_LIST_ENTRY);
         string tmpSignalName = signalName;
         maxPtr = 0;
         int ptr = parser_si(tmpSignalName, 0, newSignalNameNode);

         newItemDeclarationNode -> sub = newSignalNameNode;
         newItemDeclarationNode -> sub -> next = initNode(DB_ROUTED);
         if (debug) printf("---------------------- newItemDeclarationNode: \n");
         if (debug) 
         if (newItemDeclarationNode != NULL)
            printTree(newItemDeclarationNode);
      }
      if (debug) 
      if (signalName.compare("g0") == 0) {
         printf("---------------------- pathSignalPtrNode: \n");
         if (pathSignalPtrNode != NULL)
            printTree(pathSignalPtrNode);
         printf("---------------------- signalPtrNode: \n");
         if (signalPtrNode != NULL)
            printTree(signalPtrNode);
         printf("---------------------- clNode: \n");
         if (clNode != NULL)
            printTree(clNode);
      }
   /////////////////////////////////////
   //  Connect source
   /////////////////////////////////////
   } else 
   if (pathSignalName.compare(signalName) != 0) {
      if (debug) printf("Connect source %s and %s rhs: %d\n", pathSignalName.c_str(), signalName.c_str(), trueLHSfalseRHS);
      if (signalPtrNode != NULL) {
         printf("ERR.ROUTE.COMMAND.SIGNAL_ALREADY_EXISTS: %s\n", signalName.c_str());
         exit(-1);
      }
      if (debug) printTree(5, pathSignalPtrNode);
      string procedureString;
      procedureString = "always_comb begin ";
      procedureString.append(signalName);
      procedureString.append(" = ");
      procedureString.append(pathSignalName);
      procedureString.append (" ; end ");
      maxPtr = 0;
      NODE* subNode = initNode(0);
      parser_sv_always_construct(procedureString, 0, subNode);
      if (debug) printf("%s\n", procedureString.c_str());
      if (debug) printTree(5, subNode);  
      NODE* coneNode = getConstructListFirstNode(itemDeclarationNode -> sub, DB_CONE);
      coneNode -> sub = subNode;
      if (debug) printf("----------------------------dbModuleItemsNode:\n");
      if (debug) printTree(5, dbModuleItemsNode);
   }
}
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
                          unsigned *clCntPtr) {
   bool debug = false;
   if (debug) printf("----------------------- dbSubModuleNode:\n");
   if (debug) printTree(5, node);
   
   if (node -> id == 0) {
      if (trueModuleFalseInstance) {
         if (addPortSimpleLevel1(header, 
                                 instantiationNameString, 
                                 node -> sub,
                                 false, 
                                 hierPathNode, 
                                 trueLHSfalseRHS, 
                                 signalName, 
                                 typeNode, clCntPtr))
           return true;
      } else 
      if (header.compare(instantiationNameString) == 0) {
         if (debug) printf("----------------------- header: %s\n", header.c_str());
         NODE* clNode = node -> sub;
         NODE* dbEntryNode = clNode -> sub;
         NODE* newDBSubModuleNode = NULL;
         NODE* dbNamedPortsNode = NULL;
         NODE* dbPortDeclarationsNode = NULL;
         while (true) {
            if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
            if (dbEntryNode -> id == DB_SUB_MODULES)
               newDBSubModuleNode = dbEntryNode;
            else if (dbEntryNode -> id == DB_NAMED_PORTS)
               dbNamedPortsNode = dbEntryNode;
            else if (dbEntryNode -> id == DB_PORT_DECLARATIONS)
               dbPortDeclarationsNode = dbEntryNode;
            if (dbEntryNode -> next == NULL)
               break;
            dbEntryNode = dbEntryNode -> next;
         }
         if (debug) printf("-------------------------- newDBSubModuleNode:\n");
         if (debug) if (newDBSubModuleNode != NULL) printTree(5, newDBSubModuleNode);

         /////////////////////////////////////
         //  Do sub first to pick up typeNode
         /////////////////////////////////////
         if (hierPathNode -> next -> next != NULL) {
            instantiationNameString = getSI(hierPathNode -> next);
            if (debug) printf("next instantiationNameString: %s\n", instantiationNameString.c_str());
            string tmpHeader = "";
            addPortSimpleLevel1(tmpHeader, instantiationNameString, newDBSubModuleNode, true, hierPathNode -> next, trueLHSfalseRHS, signalName, typeNode, clCntPtr);
         }

         /////////////////////////////////////
         //  Continue on this module
         /////////////////////////////////////
         /////////////////////////////////////
         //  Pick-up source signal
         /////////////////////////////////////
         if (hierPathNode -> next -> next == NULL) {
            string pathSignalName = getSI(hierPathNode -> next -> sub);
            if (debug) printf("pathSignalName: %s\n", pathSignalName.c_str());

            addPortSimpleLevel2(pathSignalName, signalName, trueLHSfalseRHS, typeNode, node -> sub, clCntPtr);
         }
         /////////////////////////////////////
         //  Named port
         /////////////////////////////////////
         NODE* tmpNode = initNode(DB_LIST_ENTRY);
         int ptr = parser_si(signalName, 0, tmpNode);

         if (dbNamedPortsNode == NULL) {
            if (debug) printf("Insert dbNamedPortsNode.\n");
            dbNamedPortsNode = initNode(DB_NAMED_PORTS);
            dbNamedPortsNode -> next = clNode -> sub;
            clNode -> sub = dbNamedPortsNode;
            dbNamedPortsNode -> sub = tmpNode; 
         } else {
            bool add = true;
            NODE* subdbNamedPortsNode = dbNamedPortsNode -> sub;
            while (true) {
               if (subdbNamedPortsNode -> id == tmpNode -> id) {
                  if (subdbNamedPortsNode -> sub == NULL)
                  if (tmpNode -> sub == NULL) {
                     add = false;
                     break;
                  }
                  if (subdbNamedPortsNode -> sub != NULL)
                  if (tmpNode -> sub != NULL)
                  if (checkTree(subdbNamedPortsNode -> sub, tmpNode -> sub)) {
                     add = false;
                     break;
                  }
               }
               if (subdbNamedPortsNode -> next == NULL)
                  break;
               subdbNamedPortsNode = subdbNamedPortsNode -> next;
            }
            if (add) {
               tmpNode -> next = dbNamedPortsNode -> sub;
               dbNamedPortsNode -> sub = tmpNode; 
            }
         }                           
         /////////////////////////////////////
         //  Port Declaration
         /////////////////////////////////////                   
         string portDeclaration = "";
         unsigned identifier = 5; // output
         if (trueLHSfalseRHS)
            identifier = 4;
         writeDeclaration(portDeclaration, identifier, signalName, typeNode);
         portDeclaration.append(";");

         if (debug) printf("insert port: %s\n", portDeclaration.c_str());
  
         tmpNode = initNode(DB_LIST_ENTRY);
         maxPtr = 0;
         parser_sv_port_declaration(portDeclaration, 0, tmpNode);
         if (debug) printTree(tmpNode);
         if (dbPortDeclarationsNode == NULL) {
            dbPortDeclarationsNode = initNode(DB_PORT_DECLARATIONS);
            dbPortDeclarationsNode -> next = clNode -> sub;
            clNode -> sub = dbPortDeclarationsNode;
            dbPortDeclarationsNode -> sub = tmpNode;
         } else {
            bool add = true;
            NODE* subdbPortDeclarationsNode = dbPortDeclarationsNode -> sub; 
            while (true) {
               if (subdbPortDeclarationsNode -> sub == NULL)
               if (tmpNode -> sub == NULL) {
                  add = false;
                  break;
               }
               if (subdbPortDeclarationsNode -> sub != NULL)
               if (tmpNode -> sub != NULL) {
                  // exact match
                  if (checkTree(subdbPortDeclarationsNode -> sub, tmpNode -> sub)) {
                     add = false;
                     break;
                  }
                  // match but different direction, convert to IO
                  if (subdbPortDeclarationsNode -> sub -> sub != NULL)
                  if (tmpNode -> sub -> sub != NULL)
                     if (subdbPortDeclarationsNode -> sub -> sub -> sub != NULL)
                     if (tmpNode -> sub -> sub -> sub != NULL) {
                        if (checkTree(subdbPortDeclarationsNode -> sub -> sub -> sub, tmpNode -> sub -> sub -> sub)) {
                           if (subdbPortDeclarationsNode -> sub -> id != tmpNode -> sub -> id) {
                              subdbPortDeclarationsNode -> sub -> id = G_SV_INOUT_DECLARATION;
                              subdbPortDeclarationsNode -> sub -> sub -> id = G_SV_INOUT_TYPE_DECLARATION;
                        }
                        add = false;
                        break;
                     }
                  }
               }
               if (subdbPortDeclarationsNode -> next == NULL)
                  break;
               subdbPortDeclarationsNode = subdbPortDeclarationsNode -> next;
            }
            if (add) {
               tmpNode -> next = dbPortDeclarationsNode -> sub;
               dbPortDeclarationsNode -> sub = tmpNode; 
            }
         }             
         if (debug) printf("------------------------ clNode:\n");
         if (debug) printTree(6, clNode -> sub -> sub);
         return true;
      }
   } else
   if (node -> sub != NULL) {
      string thisHeader = "";
      thisHeader.append(header);
      if (!trueModuleFalseInstance)
         thisHeader.append(node2String(node));
      if (addPortSimpleLevel1(thisHeader, 
                              instantiationNameString, 
                              node -> sub,
                              trueModuleFalseInstance, 
                              hierPathNode, 
                              trueLHSfalseRHS, 
                              signalName, 
                              typeNode, clCntPtr))
         return true;
   }
   if (node -> next != NULL)
      if (addPortSimpleLevel1(header,
                              instantiationNameString, 
                              node -> next,
                              trueModuleFalseInstance, 
                              hierPathNode, 
                              trueLHSfalseRHS, 
                              signalName, 
                              typeNode, clCntPtr))
         return true;
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
/// Add port, simple, used in user defined route
/////////////////////////////////////////////////////////////////////////////////
void addPortSimple (NODE* hierPathNode, 
                    bool trueLHSfalseRHS, 
                    string signalName, 
                    NODE* typeNode, 
                    NODE* modNode, 
                    unsigned *clCntPtr) {
   bool debug = false;
   if (debug) printf("-------------------------- hierPathNode:\n");
   if (debug) printTree(hierPathNode);
   //////////////////////////////////
   // get submodule
   //////////////////////////////////
   if (debug) printTree(5, modNode);   
   NODE* dbEntryNode = modNode -> sub;
   NODE* dbSubModuleNode = NULL;
   while (true) {
      if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
      if (dbEntryNode -> id == DB_SUB_MODULES)
         dbSubModuleNode = dbEntryNode;
      if (dbEntryNode -> next == NULL)
         break;
      dbEntryNode = dbEntryNode -> next;
   }
   if (debug) printf("-------------------------- dbSubModuleNode:\n");
   if (debug) if (dbSubModuleNode != NULL) printTree(5, dbSubModuleNode);

   //////////////////////////////////
   // get instantiation string
   //////////////////////////////////
   string instantiationNameString = getSI(hierPathNode);
   if (debug) printf("instantiationNameString: %s\n", instantiationNameString.c_str());
   
   //////////////////////////////////
   // pass sub module tree
   //////////////////////////////////
   string tmpHeader = "";
   addPortSimpleLevel1(tmpHeader, instantiationNameString, dbSubModuleNode, true, hierPathNode, trueLHSfalseRHS, signalName, typeNode, clCntPtr);
}
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
                         unsigned *clCntPtr) {
   bool debug = false;
   if (debug) printf("-------------------- node:\n");
   if (debug) printTree(5, node);
   if (node -> id == 0) {
      if (trueModuleFalseInstance) {
         if (routeCommandLevel2(header, fromString, node -> sub, false, fromNode, toNode, signalName, clCntPtr))
            return true;
      } else 
      if (header.compare(fromString) == 0) {
         if (debug) printf("--------------------- found level\n");
         if (debug) printTree(5, node);
         return routeCommandLevel1(fromNode, toNode, signalName, node -> sub, clCntPtr);
         //exit(-1);
      }
   } else
   if (node -> sub != NULL) {
      string thisHeader = "";
      thisHeader.append(header);
      if (!trueModuleFalseInstance)
         thisHeader.append(node2String(node));
      if (routeCommandLevel2(thisHeader, fromString, node -> sub, trueModuleFalseInstance, fromNode, toNode, signalName, clCntPtr))
            return true;
   }
   if (node -> next != NULL)
      if (routeCommandLevel2(header, fromString, node -> next, trueModuleFalseInstance, fromNode, toNode, signalName, clCntPtr))
            return true;
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate route command, level 1
/////////////////////////////////////////////////////////////////////////////////
bool routeCommandLevel1 (NODE* fromNode, 
                         NODE* toNode, 
                         string signalName, 
                         NODE* modNode, 
                         unsigned *clCntPtr) {
   bool debug = false;
   if (debug) printf("--------------------- routeCommandLevel1, fromNode: \n");
   if (debug) printTree(fromNode);
   if (debug) printf("--------------------- routeCommandLevel1, toNode: \n");
   if (debug) printTree(toNode);
   /////////////////////////////
   // find new top level for routing when both paths have sub
   /////////////////////////////
   if ( (fromNode -> next != NULL) &
        (toNode -> next != NULL)   ) {
         string fromString = getSI(fromNode);
         string toString = getSI(toNode);
         if (fromString.compare(toString) == 0) {
            NODE* dbEntryNode = modNode -> sub;
            NODE* dbSubModuleNode = NULL;
            while (true) {
               if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
               if (dbEntryNode -> id == DB_SUB_MODULES)
                  dbSubModuleNode = dbEntryNode;
               if (dbEntryNode -> next == NULL)
                  break;
               dbEntryNode = dbEntryNode -> next;
            }
            if (debug) printf("-------------------------- dbSubModuleNode:\n");
            if (debug) if (dbSubModuleNode != NULL) printTree(5, dbSubModuleNode);
            string header = "";
            return routeCommandLevel2(header, fromString, dbSubModuleNode, true,  fromNode -> next, toNode -> next, signalName, clCntPtr);
         }
   }        
   /////////////////////////////
   // add port rhs and pick-up typeNode
   /////////////////////////////
   NODE* typeNode = initNode(0);
   if (fromNode -> next != NULL)
      addPortSimple(fromNode, false, signalName, typeNode, modNode, clCntPtr);
   else {
      string pathSignalName = getSI(fromNode);
      if (debug) printf("pathSignalName: %s\n", pathSignalName.c_str());

      addPortSimpleLevel2(pathSignalName, signalName, false, typeNode, modNode, clCntPtr);
   }

   /////////////////////////////
   // add port lhs
   /////////////////////////////
   if (toNode -> next != NULL)
      addPortSimple(toNode, true, signalName, typeNode, modNode, clCntPtr);
   else {
      string pathSignalName = getSI(toNode);
      if (debug) printf("pathSignalName: %s\n", pathSignalName.c_str());

      addPortSimpleLevel2(pathSignalName, signalName, true, typeNode, modNode, clCntPtr);
   }
   /////////////////////////////
   // add wire
   /////////////////////////////
   addWire(signalName, typeNode, modNode);

   return true;
}
/////////////////////////////////////////////////////////////////////////////////
/// Elaborate route command
/////////////////////////////////////////////////////////////////////////////////
bool routeCommand (NODE* routeNode, 
                   NODE* modNode, 
                   unsigned *clCntPtr) {
   bool debug = false;
   if (debug) printf("---------------------routeNode: \n");
   if (debug) printTree(routeNode);
   NODE* fromNode = routeNode -> sub;
   NODE* toNode = routeNode -> sub -> next;
   /////////////////////////////
   // get signal name
   /////////////////////////////
   string signalName;
   bool defaultSignalName = true;
   if (toNode -> next != NULL) {
      NODE* signalNode = toNode -> next;
      if (signalNode -> id == G_PDVL_ROUTE_SIGNAL_IDENTIFIER) {
         signalName = getSI(toNode -> next -> sub);
         defaultSignalName = false;
      }
   }
   if (defaultSignalName) { 
      NODE* tmpNode = fromNode -> sub;
      while (1) {
         if (tmpNode -> next == NULL)
            break;
         tmpNode = tmpNode -> next;
      }
      signalName = getSI(tmpNode);
   }
   return routeCommandLevel1(fromNode -> sub, toNode -> sub, signalName, modNode, clCntPtr);
}
/////////////////////////////////////////////////////////////////////////////////
/// Write SystemVerilog declaration
/////////////////////////////////////////////////////////////////////////////////
void writeDeclaration (string &out, 
                       unsigned identifier, 
                       string signalName, 
                       NODE* typeNode) {
   bool debug = false;
   if (debug) printf("----------------------- writeDeclaration: %s\n", signalName.c_str());
   if (debug) printTree(5, typeNode);
   bool enumStructUnionType = false;
   if (typeNode != NULL)
   if (typeNode -> sub != NULL)
   if (typeNode -> sub -> id == G_PDVL_ENUM_DATA_TYPE) {
      out.append("enum "); 
   } else
   if (typeNode -> sub -> id == G_PDVL_STRUCT_OR_UNION_DATA_TYPE) {
      if (typeNode -> sub -> sub -> sub -> id == G_SV_STRUCT)
         out.append("struct "); 
      else
         out.append("union "); 
      enumStructUnionType = true;
   } else
   if (typeNode -> sub -> id == G_PDVL_TYPE_IDENTIFIER_DATA_TYPE) {
      enumStructUnionType = true;
   }
   
   if (!(enumStructUnionType))
   if (identifier == 1) 
      out.append("wire ");
   else if (identifier == 2) 
      out.append("reg ");
   else if (identifier == 3) 
      out.append("logic ");
   
   if (identifier == 4) 
      out.append("input ");
   else if (identifier == 5) 
      out.append("output ");
      
   if (typeNode != NULL)
   if (typeNode -> sub != NULL)
   if (typeNode -> sub -> id == G_PDVL_PACKED_DIMENSION_LIST) {
      writer_pdvl_packed_dimension_list(out, typeNode -> sub -> sub);
      out.append(" "); 
   } else
   if (typeNode -> sub -> id == G_PDVL_ENUM_DATA_TYPE) {
      string tmpOut = "";
      writer_pdvl_enum_data_type(tmpOut, typeNode -> sub -> sub);
      out.append(tmpOut.substr(6));
      out.append(" "); 
   } else
   if (typeNode -> sub -> id == G_PDVL_STRUCT_OR_UNION_DATA_TYPE) {
      string tmpOut = "";
      writer_pdvl_struct_or_union_data_type(tmpOut, typeNode -> sub -> sub);
      if (typeNode -> sub -> sub -> sub -> id == G_SV_STRUCT)
         out.append(tmpOut.substr(8));
      else
         out.append(tmpOut.substr(7));
      out.append(" "); 
   } else
   if (typeNode -> sub -> id == G_PDVL_TYPE_IDENTIFIER_DATA_TYPE) {
      writer_pdvl_type_identifier_data_type(out, typeNode -> sub -> sub);
      out.append(" "); 
   }
   
   out.append(signalName);
   
   if (typeNode != NULL)
   if (typeNode -> sub != NULL)
   if (typeNode -> sub -> id == G_PDVL_UNPACKED_DIMENSION_LIST) {
      writer_pdvl_unpacked_dimension_list(out, typeNode -> sub -> sub);
      out.append(" "); 
   } else
   if (typeNode -> sub -> next != NULL)
   if (typeNode -> sub -> next -> id == G_PDVL_UNPACKED_DIMENSION_LIST) {
      writer_pdvl_unpacked_dimension_list(out, typeNode -> sub -> next -> sub);
      out.append(" "); 
   } 
   if (debug) printf("%s\n", out.c_str());
}
/////////////////////////////////////////////////////////////////////////////////
/// Remove assignment
/////////////////////////////////////////////////////////////////////////////////
bool removeAssignment (NODE* moveNode, 
                       NODE* modNode) {
   bool debug = false;
   if (debug) printf("--------------------- moveNode: \n");
   if (debug) printTree(moveNode); 
   ///////////////////////////////////
   // target instantiation at end of list
   /////////////////////////////////// 
   NODE* hierModuleNameNode = moveNode -> sub -> next;
   while (1)
   {
      if (hierModuleNameNode -> next == NULL)
         break;
      hierModuleNameNode = hierModuleNameNode -> next;
   }
   if (hierModuleNameNode == NULL)
      return false;
   if (debug) printf("---------------------hierModuleNameNode: \n");
   if (debug) printTree(hierModuleNameNode);
   if (debug) printf("---------------------modNode: \n");
   if (debug) printTree(4, modNode);
   ///////////////////////////////////
   // save this dbEntryNode
   // check if module instantiation exists
   /////////////////////////////////// 
   NODE* targetModuleHierNode = hierModuleNameNode -> sub;
   if (targetModuleHierNode != NULL) 
   while (1) { 
       if (debug) printf("---------------------targetModuleHierNode move: \n");
       if (debug) printTree(targetModuleHierNode);
       modNode = getSubModule(targetModuleHierNode, modNode);
       if (modNode == NULL) {
          if (debug) printf("modNode == NULL\n");
          return false;
       }
       if (targetModuleHierNode -> next == NULL)
          break;
       targetModuleHierNode = targetModuleHierNode -> next;
   } 
   
   NODE* removeTransNode = NULL;

   NODE* dbEntryNode = modNode -> sub;
   while (true) {
      if (dbEntryNode -> id == DB_MODULE_TRANSACTIONS_REMOVED) {
         removeTransNode = dbEntryNode;
         break;
      }
      if (dbEntryNode -> next == NULL) {
         removeTransNode = initNode(DB_MODULE_TRANSACTIONS_REMOVED);
         dbEntryNode -> next = removeTransNode;
         break;
      }
      dbEntryNode = dbEntryNode -> next;
   } 
   if (debug) printf("---------------------removeTransNode: \n");
   if (debug) if (removeTransNode != NULL) printTree(removeTransNode);
   if (debug) printf("---------------------moveNode: \n");
   if (debug) if (moveNode != NULL) printTree(moveNode);
   
   NODE* transNameNode = moveNode -> sub;
   while (1) {
      addSITree(transNameNode, NULL, removeTransNode);
      if (transNameNode -> next == NULL)
         break;
      if (transNameNode -> next -> id == G_LIST_OF_SI)
         transNameNode = transNameNode -> next -> sub;
      else
         break;
   }
   if (debug) {
      string removeSiString = getSI(moveNode -> sub);
      printf("--------------------- removeSiString: %s\n", removeSiString.c_str());
   }
   if (debug) printf("---------------------removeTransNode: \n");
   if (debug) printTree(removeTransNode);

   if (debug) printf("---------------------modNode: \n");
   if (debug) printTree(4, modNode);
   
   return true;
}
/////////////////////////////////////////////////////////////////////////////////
/// replace transaction emit entry
/////////////////////////////////////////////////////////////////////////////////
void replaceTransactionEmit (NODE* thisNode, 
                             unsigned level, 
                             NODE* oldSINode, 
                             NODE* newSINode) {
    bool debug = false;
    if (thisNode -> id == 0) {
       if (debug) printTree(thisNode -> sub);
       replaceTransactionEmit(thisNode -> sub, 1, oldSINode, newSINode);
    } else
    if ( (level == 1)                    &
         (thisNode -> id == G_PDVL_EMIT) ) {
       if (debug) printf("-----------------------\n");
       if (debug) printTree(thisNode -> sub -> sub);
       if (debug) printf("-----------------------\n");
       if (debug) printTree(oldSINode -> sub);
       if (checkTree(thisNode -> sub -> sub, oldSINode -> sub)) {
          if (debug) printf("   equal.\n");
          thisNode -> sub -> sub = copyTree(newSINode -> sub);
          if (debug) printTree(thisNode);
       }
    } else
    if ( (thisNode -> id == G_SV_STATEMENT)                             |
         (thisNode -> id == G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT)    |
         (thisNode -> id == G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT) ) {
    } else
    if (thisNode -> sub != NULL)
       replaceTransactionEmit(thisNode -> sub, level, oldSINode, newSINode);
    if (thisNode -> next != NULL)
       replaceTransactionEmit(thisNode -> next, level, oldSINode, newSINode);
}
/////////////////////////////////////////////////////////////////////////////////
/// replace transaction 
/////////////////////////////////////////////////////////////////////////////////
bool replaceTransaction (NODE* replaceNode, 
                         NODE* modNode) {
   bool debug = false;
   if (debug) printf("--------------------- replaceNode: \n");
   if (debug) printTree(replaceNode); 
   ///////////////////////////////////
   // target instantiation at end of list
   /////////////////////////////////// 
   NODE* hierModuleNameNode = replaceNode -> sub -> next;
   while (1)
   {
      if (hierModuleNameNode -> next == NULL)
         break;
      hierModuleNameNode = hierModuleNameNode -> next;
   }
   if (hierModuleNameNode == NULL)
      return false;
   if (debug) printf("--------------------- hierModuleNameNode: \n");
   if (debug) printTree(hierModuleNameNode);
   if (debug) printf("--------------------- modNode: \n");
   if (debug) printTree(4, modNode);
   ///////////////////////////////////
   // save this dbEntryNode
   // check if module instantiation exists
   /////////////////////////////////// 
   NODE* targetModuleHierNode = hierModuleNameNode -> sub;
   if (targetModuleHierNode != NULL) 
   while (1) { 
       if (debug) printf("--------------------- targetModuleHierNode replace: \n");
       if (debug) printTree(targetModuleHierNode);
       modNode = getSubModule(targetModuleHierNode, modNode);
       if (modNode == NULL) {
          if (debug) printf("modNode == NULL\n");
          return false;
       }
       if (targetModuleHierNode -> next == NULL)
          break;
       targetModuleHierNode = targetModuleHierNode -> next;
   } 
   if (debug) printf("--------------------- modNode: \n");
   if (debug) printTree(4, modNode);
   

   NODE* removeTransNode = NULL;

   NODE* dbEntryNode = modNode -> sub;
   while (true) {
      if (dbEntryNode -> id == DB_MODULE_TRANSACTIONS_REMOVED) {
         removeTransNode = dbEntryNode;
         break;
      }
      if (dbEntryNode -> next == NULL) {
         removeTransNode = initNode(DB_MODULE_TRANSACTIONS_REMOVED);
         dbEntryNode -> next = removeTransNode;
         break;
      }
      dbEntryNode = dbEntryNode -> next;
   } 

   NODE* transNameNode = replaceNode -> sub;
   addSITree(transNameNode, NULL, removeTransNode);

   NODE* joinedClustersNode = NULL;

   dbEntryNode = modNode -> sub;
   while (true) {
      if (dbEntryNode -> id == DB_JOINED_CLUSTERS) {
         joinedClustersNode = dbEntryNode;
         break;
      }
      if (dbEntryNode -> next == NULL) {
         return false;
         break;
      }
      dbEntryNode = dbEntryNode -> next;
   } 
   if (debug) printf("--------------------- joinedClustersNode: before\n");
   if (debug) if (joinedClustersNode != NULL) printTree(joinedClustersNode);

   replaceTransactionEmit(joinedClustersNode -> sub, 0, replaceNode -> sub, replaceNode -> sub -> next);

   if (debug) printf("--------------------- joinedClustersNode: after\n");
   if (debug) if (joinedClustersNode != NULL) printTree(joinedClustersNode);

   return true;
}
/////////////////////////////////////////////////////////////////////////////////
/// Move assignment
/////////////////////////////////////////////////////////////////////////////////
bool moveAssignment (NODE* moveNode, 
                     NODE* modNode) {
   bool debug = false;
   ///////////////////////////////////
   // target instantiation at end of list
   /////////////////////////////////// 
   NODE* hierModuleNameNode = moveNode -> sub -> next;
   while (1)
   {
      if (hierModuleNameNode -> next == NULL)
         break;
      hierModuleNameNode = hierModuleNameNode -> next;
   }
   if (hierModuleNameNode == NULL)
      return false;
   if (debug) printf("---------------------hierModuleNameNode: \n");
   if (debug) printTree(hierModuleNameNode);
   if (debug) printf("---------------------modNode: \n");
   if (debug) printTree(4, modNode);
   ///////////////////////////////////
   // save this dbEntryNode
   // check if module instantiation exists
   /////////////////////////////////// 
   NODE* dbEntryNode = modNode -> sub;

   NODE* targetModuleHierNode = hierModuleNameNode -> sub;
   if (targetModuleHierNode != NULL) 
   while (1) { 
       if (debug) printf("---------------------targetModuleHierNode move: \n");
       if (debug) printTree(targetModuleHierNode);
       modNode = getSubModule(targetModuleHierNode, modNode);
       if (modNode == NULL) {
          if (debug) printf("modNode == NULL\n");
          return false;
       }
       if (targetModuleHierNode -> next == NULL)
          break;
       targetModuleHierNode = targetModuleHierNode -> next;
   } 
   
   NODE* targetInstatiationNode = modNode;
   if (debug) printTree(targetInstatiationNode);
   
   NODE* dbModuleRegistersNode = NULL;
   NODE* dbModuleLatchesNode = NULL;
   NODE* dbModuleItemsNode = NULL;
   NODE* dbModuleConditionsNode = NULL;
   while (true) {
      if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
      if (dbEntryNode -> id == DB_MODULE_REGISTERS)
         dbModuleRegistersNode = dbEntryNode;
      if (dbEntryNode -> id == DB_MODULE_LATCHES)
         dbModuleLatchesNode = dbEntryNode;
      if (dbEntryNode -> id == DB_MODULE_ITEMS)
         dbModuleItemsNode = dbEntryNode;
      if (dbEntryNode -> id == DB_MODULE_CONDITIONS)
         dbModuleConditionsNode = dbEntryNode;
      if (dbEntryNode -> next == NULL)
         break;
      dbEntryNode = dbEntryNode -> next;
   } 
   NODE* itemPtrNode = moveNode -> sub;
   bool elementNotFound = false;
   while (1) {
      string itemName = getSI(itemPtrNode);
      NODE* moveNameNode = getNode(itemPtrNode, G_SI);
      NODE* itemNode = NULL; 
      if (dbModuleItemsNode != NULL)
      if (dbModuleItemsNode -> sub != NULL) {
         NODE* lastNode = NULL;
         NODE* clNode = dbModuleItemsNode -> sub;
         while (1) {
            if (debug) printf("clNode: %d\n", clNode -> id);
            NODE* tmpNode = clNode -> sub;
            while (1) {
               if (tmpNode -> sub != NULL) {
                  NODE* itemNameNode = getNode(tmpNode, G_SI);
                  if (checkTree(itemNameNode -> sub, moveNameNode -> sub)) {
                     itemNode = tmpNode;                          
                     if (lastNode == NULL)
                        clNode -> sub = tmpNode -> next;
                     else
                        lastNode -> next = tmpNode -> next;
                     itemNode -> next = NULL;
                     if (reportLevel > 2) {
                        string tmpItemName = getSI(tmpNode);
                        printf("2.8.1: Moving item %s\n", tmpItemName.c_str());
                     }
                     joinConstruct(targetInstatiationNode, tmpNode, clNode -> id, DB_MODULE_ITEMS);
                     break;
                  }
               }   
               lastNode = tmpNode;
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
            if (clNode -> next == NULL)
               break;
            clNode = clNode -> next;
         }
      }
      if (itemNode == NULL)
      if (dbModuleRegistersNode != NULL) 
      if (dbModuleRegistersNode -> sub != NULL) {
         NODE* lastNode = NULL;
         NODE* clNode = dbModuleRegistersNode -> sub;
         while (1) {
            if (debug) printf("clNode: %d\n", clNode -> id);
            NODE* tmpNode = clNode -> sub;
            while (1) {
               if (tmpNode -> sub != NULL) {
                  NODE* itemNameNode = getNode(tmpNode, G_SI);
                  if (checkTree(itemNameNode -> sub, moveNameNode -> sub)) {
                     itemNode = tmpNode;                          
                     if (lastNode == NULL)
                        clNode -> sub = tmpNode -> next;
                     else
                        lastNode -> next = tmpNode -> next;
                     itemNode -> next = NULL;
                     if (reportLevel > 2) {
                        string tmpItemName = getSI(tmpNode);
                        printf("2.8.1: Moving register %s\n", tmpItemName.c_str());
                     }
                     joinConstruct(targetInstatiationNode, tmpNode, clNode -> id, DB_MODULE_REGISTERS);
                     break;
                  }
               }   
               lastNode = tmpNode;
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
            if (clNode -> next == NULL)
               break;
            clNode = clNode -> next;
         } 
      }
      if (itemNode == NULL)
      if (dbModuleLatchesNode != NULL) 
      if (dbModuleLatchesNode -> sub != NULL) {
         NODE* lastNode = NULL;
         NODE* clNode = dbModuleLatchesNode -> sub;
         while (1) {
            if (debug) printf("clNode: %d\n", clNode -> id);
            NODE* tmpNode = clNode -> sub;
            while (1) {
               if (tmpNode -> sub != NULL) {
                  NODE* itemNameNode = getNode(tmpNode, G_SI);
                  if (checkTree(itemNameNode -> sub, moveNameNode -> sub)) {
                     itemNode = tmpNode;                          
                     if (lastNode == NULL)
                        clNode -> sub = tmpNode -> next;
                     else
                        lastNode -> next = tmpNode -> next;
                     itemNode -> next = NULL;
                     if (reportLevel > 2) {
                        string tmpItemName = getSI(tmpNode);
                        printf("2.8.1: Moving latch %s\n", tmpItemName.c_str());
                     }
                     joinConstruct(targetInstatiationNode, tmpNode, clNode -> id, DB_MODULE_LATCHES);
                     break;
                  }
               }   
               lastNode = tmpNode;
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
            if (clNode -> next == NULL)
               break;
            clNode = clNode -> next;
         } 
      }
      if (itemNode == NULL)
      if (dbModuleConditionsNode != NULL) 
      if (dbModuleConditionsNode -> sub != NULL) {
         NODE* lastNode = NULL;
         NODE* clNode = dbModuleConditionsNode -> sub;
         while (1) {
            if (debug) printf("clNode: %d\n", clNode -> id);
            NODE* tmpNode = clNode -> sub;
            while (1) {
               if (tmpNode -> sub != NULL) {
                  NODE* itemNameNode = getNode(tmpNode -> sub, G_PDVL_COND_IDENTIFIER_BY_NAME);
                  if (itemNameNode == NULL)
                     itemNameNode = getNode(tmpNode -> sub, G_PDVL_COND_SI);
                  if (itemNameNode != NULL) {
                     if (itemNameNode -> id == G_PDVL_COND_SI) 
                        itemNameNode = itemNameNode -> sub;
                     if (checkTree(itemNameNode -> sub, moveNameNode -> sub)) {
                        itemNode = tmpNode;                          
                        if (lastNode == NULL)
                           clNode -> sub = tmpNode -> next;
                        else
                           lastNode -> next = tmpNode -> next;
                        itemNode -> next = NULL;
                        if (reportLevel > 2) {
                           string tmpItemName = getSI(tmpNode);
                           printf("2.8.1: Moving condtition %s\n", tmpItemName.c_str());
                        }
                        joinConstruct(targetInstatiationNode, tmpNode, clNode -> id, DB_MODULE_CONDITIONS);
                        break;
                     }
                  }
               }   
               lastNode = tmpNode;
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
            if (clNode -> next == NULL)
               break;
            clNode = clNode -> next;
         } 
      }
      ///////////////////////////////////
      //  datapaths, conditions, events, ...
      if (itemNode == NULL) {
         if (debug) printf("Element %s not found\n", itemName.c_str());
         elementNotFound = true;
      } 
      if (itemPtrNode -> next -> id == G_HIERARCHICAL_NAME)
         break;
      else
         itemPtrNode = itemPtrNode -> next;
   }
   return !elementNotFound;
}
/////////////////////////////////////////////////////////////////////////////////
/// Get top-level module, sub-routine
/////////////////////////////////////////////////////////////////////////////////
NODE* getTopLevelModule_sub (NODE* node, 
                             bool pickUp, 
                             bool compare, 
                             NODE* rootNode, 
                             NODE* leafNode, 
                             NODE* instanciatedModulesNode) {
   bool debug = false;
   if (debug) printf("getTopLevelModule_sub call: %d\n", node -> id);
   while (true) {
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("cont 0, id: %d\n", node -> sub -> id);
         if ( (node -> sub -> id != 0) ) {
            NODE* tmpLeafNode = initNode(node  -> id);
            leafNode -> sub = tmpLeafNode;
            NODE* returnNode = getTopLevelModule_sub(node -> sub, pickUp, compare, rootNode, tmpLeafNode, instanciatedModulesNode);
            delete tmpLeafNode;
            if (returnNode != NULL)
               return returnNode;
         } else {
            if (debug) printf("found step3\n");
            if (debug) printTree(node -> sub);
            if (debug) printf("id: %d\n", node -> sub -> sub -> id); 
            ///////////////////////////////////////////////////
            // compare:
            ///////////////////////////////////////////////////
            if (compare) {
               NODE* thisLeafNode = initNode(node -> id);
               leafNode -> sub = thisLeafNode;
               NODE* tmpLeafNode = initNode(0);
               thisLeafNode -> sub = tmpLeafNode;
               if (debug) printf("----------------------- getTopLevelModule_sub compare rootNode:\n");
               if (debug) printTree(rootNode);
               if (debug) printf("----------------------- getTopLevelModule_sub compare instanciatedModulesNode:\n");
               if (debug) printTree(instanciatedModulesNode);
               if (!(listCoveredInTree(rootNode -> sub, instanciatedModulesNode))) {
                  return node -> sub -> sub -> sub;
               }
               leafNode -> sub = NULL;
               delete tmpLeafNode;
            } else
            ///////////////////////////////////////////////////
            // pick up: add rootNode to instanciatedModulesNode
            ///////////////////////////////////////////////////
            if (pickUp) {
               NODE* thisLeafNode = initNode(node -> id);
               leafNode -> sub = thisLeafNode;
               NODE* tmpLeafNode = initNode(0);
               thisLeafNode -> sub = tmpLeafNode;
               if (debug) printf("----------------------- getTopLevelModule_sub pickup rootNode:\n");
               if (debug) printTree(rootNode);
               mergeTrees(rootNode, instanciatedModulesNode);
               if (debug) printf("----------------------- getTopLevelModule_sub instanciatedModulesNode:\n");
               if (debug) printTree(5, instanciatedModulesNode);
               leafNode -> sub = NULL;
               delete tmpLeafNode;
            } else
            ///////////////////////////////////////////////////
            // no pick up: start pick up submodule
            ///////////////////////////////////////////////////
            if (node -> sub -> sub != NULL) 
            if (node -> sub -> sub -> sub != NULL)  
            if (node -> sub -> sub -> sub -> sub != NULL) { 
               NODE* thisLeafNode = initNode(node -> id);
               leafNode -> sub = thisLeafNode;
               NODE* tmpLeafNode = initNode(0);
               thisLeafNode -> sub = tmpLeafNode;
               
               if (debug) printf("----------------------- getTopLevelModule_sub rootNode:\n");
               if (debug) printTree(rootNode);
               if (debug) printf("----------------------- getTopLevelModule_sub node:\n");
               if (debug) printTree(5, node);
               
               NODE* dbEntryNode = node -> sub -> sub -> sub -> sub;
               while (1) {
                  if (dbEntryNode -> id == DB_SUB_MODULES) {
                     if (debug) printf("----------------------- getTopLevelModule_sub sub module:\n");
                     if (debug) printTree(5, dbEntryNode -> sub);
                     NODE* newRootNode = initNode(0);
                     getTopLevelModule_sub(dbEntryNode -> sub, true, false, newRootNode, newRootNode, instanciatedModulesNode);
                  }
                  if (dbEntryNode -> next == NULL)
                     break;
                  dbEntryNode = dbEntryNode -> next;
               }

               leafNode -> sub = NULL;
               delete tmpLeafNode;
            }
            if (debug) printSITree(node -> sub -> sub);
            if (debug) printf("cont 1\n");
            if (node -> sub != NULL)
            if (node -> sub -> next != NULL) {
               NODE* tmpLeafNode = initNode(node -> sub -> next -> id);
               leafNode -> sub = tmpLeafNode;
               NODE* returnNode = getTopLevelModule_sub(node -> sub -> next, pickUp, compare, rootNode, tmpLeafNode, instanciatedModulesNode);
               leafNode -> sub = NULL;
               delete tmpLeafNode;
               if (returnNode != NULL)
                  return returnNode;
            }
         } 
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
   return NULL;   
}
/////////////////////////////////////////////////////////////////////////////////
/// Get top-level module
/////////////////////////////////////////////////////////////////////////////////
NODE* getTopLevelModule () {
   bool debug = false;
   if (debug) printf("Auto-detect top level module.\n");
   if (debug) printTree(9, dbModuleNode);
   NODE* rootNode = initNode(0);
   NODE* instanciatedModulesNode = initNode(0);
   getTopLevelModule_sub(dbModuleNode, false, false, rootNode, rootNode, instanciatedModulesNode);
   if (debug) printf("----------------------- instanciatedModulesNode:\n");
   if (debug) printTree(instanciatedModulesNode);
   return getTopLevelModule_sub(dbModuleNode, false, true, rootNode, rootNode, instanciatedModulesNode);
}
