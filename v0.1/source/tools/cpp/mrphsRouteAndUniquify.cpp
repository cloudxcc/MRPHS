//
// Copyright 2024 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

#include <mrphsRouteAndUniquify.h>

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
              NODE* rootToTopLeafNode) {
   bool debug = false;
   if (debug) printf("addPort compare: %d %d\n", node -> id, dbSubModuleNode -> id);
   if (debug)
   if (rootToTopNode -> sub != NULL) {
      printTree(rootToTopNode -> sub);
      printf("addPort: rootToTopNode^\n");
   }
   NODE* givenDBSubModuleNode = dbSubModuleNode;
   while (true) {
      dbSubModuleNode = givenDBSubModuleNode;
      //////////////////////////////////
      // identical id
      //////////////////////////////////
      while (true) {
         if (debug) printf("addPort check: %d %d\n", node -> id, dbSubModuleNode -> id);
         if (node -> id == dbSubModuleNode -> id) {
            rootToTopLeafNode -> sub = initNode(node -> id); 
            rootToTopLeafNode = rootToTopLeafNode -> sub;
            if (node -> id == 0)
            {
               if (trueModuleFalseInstance) {
                  if (debug) printf("found first 0.\n");
                  if (debug) printTree(2, dbSubModuleNode);
                  while (true) {
                     if (debug) printf("addPort check sub: %d %d\n", node -> sub -> id, dbSubModuleNode -> sub -> id);
                     if (dbSubModuleNode -> sub -> id == node -> sub -> id) {
                        break;
                     }
                     if (dbSubModuleNode -> next == NULL) {
                        break;
                     }
                     dbSubModuleNode = dbSubModuleNode -> next;
                  }                    
                  addPort(node -> sub, dbSubModuleNode -> sub, signalName, !trueModuleFalseInstance, trueLHSfalseRHS, typeNode, rootToTopNode, rootToTopLeafNode);
               } else {
                  if (debug) printf("found second 0.\n");
                  if (debug) printf("id: %d\n", dbSubModuleNode -> sub -> id); 
                  NODE* clNode = dbSubModuleNode -> sub;
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
                  NODE* tmpNode = initNode(DB_LIST_ENTRY);
                  if (debug) printf("-------------------------- signalName: %s\n", signalName.c_str());
                  int ptr = parser_si(signalName, 0, tmpNode);
                  if (debug) printTree(tmpNode);
                  /////////////////////////////////////
                  //  Named port
                  /////////////////////////////////////
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
                  if (debug) printf("-------------------------- %s.\n", signalName.c_str());
                  if (debug) printTree(dbNamedPortsNode);
                  /////////////////////////////////////
                  //  Port Declaration
                  /////////////////////////////////////                   
                  string portDeclaration = ""; 
                  unsigned identifier = 5; // output
                  if (trueLHSfalseRHS)
                      identifier = 4;
                  writeDeclaration(portDeclaration, identifier, signalName, typeNode);

                  portDeclaration.append(" ;");
                  if (debug) printf("%s\n", portDeclaration.c_str());

                  tmpNode = initNode(DB_LIST_ENTRY);
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
                  if (debug) printTree(dbPortDeclarationsNode);
                  if (node -> sub != NULL) {
                     addPort(node -> sub, newDBSubModuleNode -> sub, signalName, true, trueLHSfalseRHS, typeNode, rootToTopNode, rootToTopLeafNode);
                  }
               }
            } else {
               addPort(node -> sub, dbSubModuleNode -> sub, signalName, trueModuleFalseInstance, trueLHSfalseRHS, typeNode, rootToTopNode, rootToTopLeafNode);
            }
            break;
         } else
         if (dbSubModuleNode -> next == NULL)
            break;
         dbSubModuleNode = dbSubModuleNode -> next;
      }
      if (node -> next == NULL)
         break;
      node = node -> next;
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Get module name and update type
/////////////////////////////////////////////////////////////////////////////////
void getModuleNameAndUpdateType (NODE* node, 
                                 NODE* dbSubModuleNode, 
                                 bool isTop, 
                                 bool trueModuleFalseInstance, 
                                 string &classString, 
                                 string signalName, 
                                 NODE* typeLHSNode) {
   bool debug = false;
   if (debug) printf("getModuleNameAndUpdateType compare: %d %d\n", node -> id, dbSubModuleNode -> id);
   NODE* givenDBSubModuleNode = dbSubModuleNode;
   while (true) {
      dbSubModuleNode = givenDBSubModuleNode;
      //////////////////////////////////
      // identical id
      //////////////////////////////////
      while (true) {
         if (debug) printf("getModuleNameAndUpdateType check: %d %d\n", node -> id, dbSubModuleNode -> id);
         if ( (isTop)                               |
              (node -> id == dbSubModuleNode -> id) ) {
            if ( (isTop)           |
                 (node -> id == 0) )
            {
               if (trueModuleFalseInstance) {
                  if (debug) printf("found first 0.\n");
                  if (debug) printTree(2, dbSubModuleNode);
                  while (true) {
                     if (debug) printf("getModuleNameAndUpdateType check sub: %d %d\n", node -> sub -> id, dbSubModuleNode -> sub -> id);
                     if (dbSubModuleNode -> sub -> id == node -> sub -> id) {
                        break;
                     }
                     if (dbSubModuleNode -> next == NULL) {
                        break;
                     }
                     dbSubModuleNode = dbSubModuleNode -> next;
                  }                    
                  getModuleNameAndUpdateType(node -> sub, dbSubModuleNode -> sub, false, !trueModuleFalseInstance, classString, signalName, typeLHSNode);
               } else {
                  if (debug) printf("found second 0.\n");
                  if (debug) printf("id: %d\n", dbSubModuleNode -> sub -> id);
                  NODE* clNode = dbSubModuleNode -> sub;
                  if (isTop)
                     clNode = dbSubModuleNode;
                  NODE* dbEntryNode = clNode -> sub;
                  NODE* dbModuleNameNode = NULL;
                  NODE* newDBSubModuleNode = NULL;
                  NODE* dbModuleTypesNode = NULL;
                  if (debug) printTree(5, dbSubModuleNode);
                  while (true) {
                     if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
                     if (dbEntryNode -> id == DB_SUB_MODULES)
                        newDBSubModuleNode = dbEntryNode;
                     else if (dbEntryNode -> id == DB_MODULE_NAME)
                        dbModuleNameNode = dbEntryNode;
                     else if (dbEntryNode -> id == DB_MODULE_TYPES)
                        dbModuleTypesNode = dbEntryNode;
                     if (dbEntryNode -> next == NULL)
                        break;
                     dbEntryNode = dbEntryNode -> next;
                  }
                  if (node -> sub == NULL) {
                     //////////////////////////////
                     // set class name = module name
                     //////////////////////////////
                     if (dbModuleNameNode != NULL) {
                        classString.append(getSI(dbModuleNameNode));
                     } else {
                        classString.append("class");
                     }
                     classString.append("_pkg_");
                     if (isTop)
                        classString.append(to_string(dbSubModuleNode -> id));
                     else
                        classString.append(to_string(dbSubModuleNode -> sub -> id));
                     NODE* classNameNode = initNode(0);
                     parser_si(classString, 0, classNameNode);
                     //////////////////////////////
                     // write to package
                     //////////////////////////////
                     if (debug) printf("---------------------- typeLHSNode:\n");
                     if (debug) printTree(5, typeLHSNode); 
                     NODE* typeIdentifier = getNode(typeLHSNode, G_SV_TYPE_IDENTIFIER);
                     if (debug) printf("---------------------- dbModuleTypesNode:\n");
                     if (debug) printTree(5, dbModuleTypesNode -> sub);
                     NODE* tmpClTypeNode = dbModuleTypesNode -> sub;
                     bool found = false;
                     while (1) {
                        if (debug) printf("\tRegister cluster: %d\n", tmpClTypeNode -> id);
                        if (tmpClTypeNode -> sub != NULL) {
                           NODE* tmpTypeNode = tmpClTypeNode -> sub;
                           if (debug) printf("\t\tRegister id: %d\n", tmpClTypeNode -> id);
                           while (1) {
                              if (tmpTypeNode -> sub != NULL) {
                                 if (debug) printf("---------------------- tmpTypeNode -> sub:\n");
                                 if (debug) printTree(5, tmpTypeNode -> sub);
                                 NODE* thisTypeIdentifier = getNodeSubLevel(tmpTypeNode, G_SV_TYPE_IDENTIFIER);
                                 if (debug) printf("---------------------- thisTypeIdentifier:\n");
                                 if (debug) printTree(5, thisTypeIdentifier);                                 
                                 if (checkTree(typeIdentifier -> sub, thisTypeIdentifier -> sub)) {
                                    NODE* enumType = getNode(tmpTypeNode -> sub, G_SV_INTEGER_ENUM_TYPE);
                                    if (enumType != NULL) {
                                       printf("ERR.AUTOROUTE.ENUMARATION_TYPES_NOT_SUPPORTED: %s\n", signalName.c_str());
                                       string out = "";
                                       writer_sv_type_declaration(out, tmpTypeNode -> sub);
                                       prettyPrint(out);
                                       printf("%sPlease consider using a vector and parameters instead.\n\n", out.c_str());
                                       exit(-1);
                                    }
                                    //////////////////////////////////
                                    // add typedefs to dbPackageNode
                                    // first entry of list must point to this modNode
                                    //////////////////////////////////
                                    NODE* tmpNode = initNode(DB_LIST_ENTRY);
                                    if (dbPackageNode -> sub == NULL) {
                                       if (debug) printf("add to empty package.\n");
                                       tmpNode -> sub = clNode;
                                       tmpNode -> next = initNode(DB_LIST_ENTRY); 
                                       tmpNode -> next -> sub = initNode(G_SV_TYPE_DECLARATION);
                                       tmpNode -> next -> sub -> sub = tmpTypeNode -> sub;
                                       addSITree(classNameNode, tmpNode, dbPackageNode); 
                                    } else {
                                       NODE* listEntryNode = getSITreeNode(classNameNode -> sub, dbPackageNode -> sub);
                                       if (listEntryNode == NULL) {
                                          if (debug) printf("add to empty list.\n");
                                          tmpNode -> sub = clNode;
                                          tmpNode -> next = initNode(DB_LIST_ENTRY); 
                                          tmpNode -> next -> sub = initNode(G_SV_TYPE_DECLARATION);
                                          tmpNode -> next -> sub -> sub = tmpTypeNode -> sub;
                                          addSITree(classNameNode, tmpNode, dbPackageNode); 
                                       } else {
                                          if (debug) printf("append to list.\n");
                                          if (debug) printf("---------------------- dbPackageNode:\n");
                                          if (debug) printTree(dbPackageNode);
                                          if (debug) printf("---------------------- listEntryNode:\n");
                                          if (debug) printTree(listEntryNode);
                                          tmpNode -> sub = initNode(G_SV_TYPE_DECLARATION);
                                          tmpNode -> sub -> sub = tmpTypeNode -> sub;
                                          while (1) {
                                             if (listEntryNode -> next == NULL)
                                                break;
                                             listEntryNode = listEntryNode -> next;
                                          }
                                          listEntryNode -> next = tmpNode;
                                       }
                                    }
                                    found = true;
                                  }
                              }
                              if (found)
                                  break;
                              if (tmpTypeNode -> next == NULL)
                                 break;
                              tmpTypeNode = tmpTypeNode -> next;
                           }
                        }
                        if (found)
                           break;
                        if (tmpClTypeNode -> next == NULL)
                          break;
                        tmpClTypeNode = tmpClTypeNode -> next;
                     }
                     if (debug) printf("---------------------- dbPackageNode:\n");
                     if (debug) printSITree(dbPackageNode);
                     if (debug) printTree(dbPackageNode);
                     if (debug) {
                        string typeNameString = getSI(typeIdentifier);
                     }
                     //////////////////////////////
                     // update signal type of driving signal
                     //////////////////////////////
                     unsigned typeUsed = 0;
                     dbEntryNode = clNode -> sub;
                     while (true) {
                        if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
                        if ( (dbEntryNode -> id == DB_MODULE_ITEMS) |
                             (dbEntryNode -> id == DB_MODULE_REGISTERS) |
                             (dbEntryNode -> id == DB_MODULE_LATCHES) ) {
                           if (debug) printf("---------------------- dbEntryNode -> sub:\n");
                           if (debug) printTree(5, dbEntryNode -> sub);
                           NODE* tmpClRegNode = dbEntryNode -> sub;
                           while (1) {
                              if (debug) printf("\tRegister cluster: %d\n", tmpClRegNode -> id);
                              if (tmpClRegNode -> sub != NULL) {
                                 NODE* tmpRegNode = tmpClRegNode -> sub;
                                 if (debug) printf("\t\tRegister id: %d\n", tmpRegNode -> id);
                                 while (1) {
                                    if (tmpRegNode -> sub != NULL) {
                                       if (debug) printf("---------------------- tmpRegNode -> sub:\n");
                                       if (debug) printTree(5, tmpRegNode -> sub);
                                       string thisSignalName = getSI(tmpRegNode -> sub);
                                       if (signalName == thisSignalName) {
                                          NODE* tmpTypeNode = getNodeSubLevel(tmpRegNode, DB_SIGNAL_TYPE); // -> sub -> next -> sub;
                                          if (debug) printf("---------------------- compare a:\n");
                                          if (debug) printTree(5, tmpTypeNode);
                                          if (debug) printf("---------------------- compare b:\n");
                                          if (debug) printTree(5, typeLHSNode -> sub);
                                          if (tmpTypeNode != NULL)
                                          if (checkTree(tmpTypeNode -> sub, typeLHSNode -> sub)) {
                                             if (debug) printf("Type found\n");
                                             tmpTypeNode = tmpTypeNode -> sub;
                                             NODE* classScopeNode = initNode(G_SV_CLASS_SCOPE);
                                             NODE* classTypeNode = initNode(G_SV_CLASS_TYPE);
                                             classScopeNode -> sub = classTypeNode;
                                             classTypeNode -> sub = initNode(G_SV_CLASS_IDENTIFIER);
                                             classTypeNode -> sub -> sub = classNameNode;
                                             classScopeNode -> next = tmpTypeNode -> sub;
                                             tmpTypeNode -> sub = classScopeNode;
                                             if (debug) printf("---------------------- tmpTypeNode:\n");
                                             if (debug) printTree(5, tmpTypeNode);
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
                        if (dbEntryNode -> next == NULL)
                           break;
                        dbEntryNode = dbEntryNode -> next;
                     }
                     //////////////////////////////
                     // remove type if not used somewhere else
                     ////////////////////////////// 
                     if (typeUsed == 1) {
                        if (debug) printf("---------------------- dbModuleTypesNode:\n");
                        if (debug) printTree(5, dbModuleTypesNode);
                     }
                  } 
                  if (node -> sub != NULL) {
                     getModuleNameAndUpdateType(node -> sub, newDBSubModuleNode -> sub, false, true, classString, signalName, typeLHSNode);
                  }
               }
            } else {
               getModuleNameAndUpdateType(node -> sub, dbSubModuleNode -> sub, false, trueModuleFalseInstance, classString, signalName, typeLHSNode);
            }
            break;
         } else
         if (dbSubModuleNode -> next == NULL)
            break;
         dbSubModuleNode = dbSubModuleNode -> next;
      }
      if (node -> next == NULL)
         break;
      node = node -> next;
   }
}
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
                              NODE* dbSubModuleNode) {
   bool debug = false;
   if (debug) printf("findSignalTopRouteStep2 route Signal: %d topModuleNode: %d\n", rhsNode -> id, topModuleNode -> id);
   //////////////////////////////////////////
   // continue pass through RHS Tree sub
   //////////////////////////////////////////
   if (rhsNode -> sub != NULL) {
      bool thisIsTri = isTri;
      if (isTop) {
         if (debug) printf("check for tristate %s, rhsNode:\n", signalName.c_str());
         if (debug) printTree(rhsNode);
         if (debug) printf("check for tristate, lhsNode:\n");
         if (debug) printTree(lhsNode);
         NODE* lhsClNode = lhsNode;
         while (1) {
            if (lhsClNode -> id == rhsNode -> id) {
               if (checkTree(lhsClNode -> sub, rhsNode -> sub)) {
                  thisIsTri = true;
               }
            }
            lhsClNode = lhsClNode -> next;
            if (lhsClNode -> next == NULL)
               break;
            lhsClNode = lhsClNode -> next;
         }
      }
      NODE* passHierarchyListNode = initNode(rhsNode -> id);
      hierarchyListNode -> sub = passHierarchyListNode;
      findSignalTopRouteStep2(signalName, rhsNode -> sub, lhsNode, false, thisIsTri, hierarchyListRootNode, passHierarchyListNode, 
                              topModuleNode, dbSubModuleNode);
      delete passHierarchyListNode;
      hierarchyListNode -> sub == NULL;
   } else {
   //////////////////////////////////////////
   // found leaf
   //////////////////////////////////////////
      if (debug) printf("findSignalTopRouteStep2 found leave: %s\n", signalName.c_str());
      if (debug) printTree(hierarchyListRootNode);
      NODE* thisRHSNode = hierarchyListRootNode -> sub;
      bool route = true;
      bool sameCluster = false;
      if (route) {
         NODE* thisLHSNode = lhsNode;
         NODE* rootToTopNode = initNode(0);
         NODE* rootToTopLeafNode = initSubNode(rootToTopNode, 0);
         NODE* rootToTopLeafTmpNode = rootToTopLeafNode;
         NODE* passHierarchyListNode = initNode(0);
         hierarchyListNode -> sub = passHierarchyListNode;

         if (debug) {
              printf("------------------- hierarchyListRootNode:\n");
              printTree(hierarchyListRootNode);
              printf("------------------- thisRHSNode:\n");
              printTree(thisRHSNode);
              printf("------------------- thisLHSNode:\n");
              printTree(thisLHSNode);
         }
         ///////////////////////////////////////////
         // Find same cluster and update lhs merged Tree
         ///////////////////////////////////////////
         NODE* thisMergedLHSNode = initNode(0);
         NODE* sameClusterTypeNode = NULL;
         bool nonTrivialTypeFound = false;
         if (1) {
            NODE* tmpNode = lhsNode;
            while (true) {
               if (debug) printf("------------------ checking tmpNode:\n");
               if (debug) printTree(tmpNode);
               if (thisRHSNode -> id == tmpNode -> id) {
                  thisLHSNode = tmpNode;
                  sameCluster = true;
                  mergeTrees(true, tmpNode, thisMergedLHSNode);
                  if (tmpNode -> next -> sub != NULL)
                     nonTrivialTypeFound = true;
                  sameClusterTypeNode = tmpNode -> next;
                  break;
               }
               tmpNode = tmpNode -> next;
               if (tmpNode -> sub != NULL)
                  nonTrivialTypeFound = true;
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
         }
         ///////////////////////////////////////////
         // Generate mergedLHSNode if not same cluster
         ///////////////////////////////////////////
         if (!(sameCluster))
         if (thisLHSNode -> next != NULL)
         if (thisMergedLHSNode -> sub == NULL) { 
            NODE* tmpNode = thisLHSNode;
            while (true) {
               mergeTrees(true, tmpNode, thisMergedLHSNode);
               if (debug) printf("thisMergedLHSNode:\n");
               if (debug) printTree(thisMergedLHSNode);
               tmpNode = tmpNode -> next;
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
         }
         if (debug) {
            printf("compare b cluster ids: %d %d = %d nonTrivialTypeFound: %d\n", thisLHSNode -> id, thisRHSNode -> id, sameCluster, nonTrivialTypeFound);
            printf("thisMergedLHSNode:\n");
            printTree(thisMergedLHSNode);
            printf("thisLHSNode:\n");
            printTree(thisLHSNode);
         }
         ///////////////////////////////////////////
         // Get top level
         ///////////////////////////////////////////
         NODE* rhsCmpPtrNode = hierarchyListRootNode -> sub -> sub;
         if (debug) {
            printf("------------------- rhsCmpPtrNode:\n");
            printTree(5, rhsCmpPtrNode);
         }
         NODE* rhsTopPtrNode = hierarchyListRootNode -> sub -> sub;
         NODE* lhsCmpPtrNode = thisLHSNode -> sub;
         NODE* lhsTopPtrNode = thisLHSNode -> sub;
         if (!(sameCluster)) 
         if (thisMergedLHSNode -> sub != NULL) {
            lhsCmpPtrNode = thisMergedLHSNode -> sub;
            lhsTopPtrNode = thisMergedLHSNode -> sub;
         }
         NODE* thisTopModuleNode = topModuleNode;
         if (debug) printf("findSignalTopRouteStep2 route Signal: thisTopModuleNode: %d <-- a\n", thisTopModuleNode -> id);
         if (debug) {
            printf("------------------- dbSubModuleNode:\n");
            printTree(5, dbSubModuleNode);
         }
         NODE* thisdbSubModuleNode = dbSubModuleNode;
         NODE* tmpdbSubModuleNode = dbSubModuleNode -> sub;
         bool trueModuleFalseInstance = true;
         bool stop = false;
         if (debug) printf("thisdbSubModuleNode id: %d\n", thisdbSubModuleNode -> id);
         while (true) {
            while (true) {
               if (debug) printf("rhs id: \t%d\nlhs id: \t%d\n", rhsCmpPtrNode -> id, lhsCmpPtrNode -> id);
               if (rhsCmpPtrNode -> id != lhsCmpPtrNode -> id) {
                  if (lhsCmpPtrNode -> next != NULL) {
                     if (isTri)
                     if (sameCluster) {
                        if (debug) printf("multiple lhs in same cluster\n");
                        stop = true;
                        break;
                     }
                     lhsCmpPtrNode = lhsCmpPtrNode -> next;
                  } else {
                     if (debug) printf("mismatch\n", rhsCmpPtrNode -> id);
                     stop = true;
                     break;
                  }
               } else {
                  break;
               }
            }
            if (stop)
                break;
            if (isTri)
            if (lhsCmpPtrNode -> next != NULL) {
               if (sameCluster) {
                  if (debug) printf("multiple lhs in same cluster\n");
                  break;
               }
            }
            while (true) {
               if (debug) printf("comp: \t\t%d %d\n", tmpdbSubModuleNode -> id, rhsCmpPtrNode -> id);
               if (tmpdbSubModuleNode -> id == rhsCmpPtrNode -> id) {
                  if (tmpdbSubModuleNode -> sub == NULL) {
                     if (debug) printf("Can't follow hierarchy tree c.\n");
                     break;
                  }
                  if (tmpdbSubModuleNode -> id == 0) {
                     if (debug) printTree(tmpdbSubModuleNode);
                     rootToTopLeafTmpNode -> sub = initNode(0);
                     rootToTopLeafTmpNode = rootToTopLeafTmpNode -> sub;
                     if (trueModuleFalseInstance) {
                        if (debug) printf("set trueModuleFalseInstance true\n");
                        trueModuleFalseInstance = false;
                        if (debug) printTree(2, tmpdbSubModuleNode);
                        while (true) {
                           if (debug) printf("check tmpdbSubModuleNode %d %d %d\n", tmpdbSubModuleNode -> id, tmpdbSubModuleNode -> sub -> id, rhsCmpPtrNode -> sub -> id);
                           if (tmpdbSubModuleNode -> sub -> id == rhsCmpPtrNode -> sub -> id) {
                              tmpdbSubModuleNode = tmpdbSubModuleNode -> sub;
                              break;
                           }
                           if (tmpdbSubModuleNode -> next == NULL) {
                              tmpdbSubModuleNode = tmpdbSubModuleNode -> sub;
                              break;
                           }
                           tmpdbSubModuleNode = tmpdbSubModuleNode -> next;
                        }
                     } else {
                        rootToTopLeafNode = rootToTopLeafTmpNode;
                        tmpdbSubModuleNode = tmpdbSubModuleNode -> sub;
                        if (debug) printf("set new thisTopModuleNode %d\n", tmpdbSubModuleNode -> id);
                        thisTopModuleNode = tmpdbSubModuleNode;
                        tmpdbSubModuleNode = thisTopModuleNode -> sub;
                        if (debug) printf("set new tmpdbSubModuleNode %d\n", tmpdbSubModuleNode -> id);
                        rhsTopPtrNode = rhsCmpPtrNode -> sub;
                        lhsTopPtrNode = lhsCmpPtrNode -> sub;
                        while (true) {
                           if (debug) printf("tmpdbSubModuleNode: %d\n", tmpdbSubModuleNode -> id);
                           if (tmpdbSubModuleNode -> id == DB_SUB_MODULES) {
                              thisdbSubModuleNode = tmpdbSubModuleNode;
                              break;
                           }
                           if (tmpdbSubModuleNode -> next == NULL) {
                              if (debug) printf("System hierarchy not found! e\n");
                              break;
                           }
                           tmpdbSubModuleNode = tmpdbSubModuleNode -> next;
                        } 
                        if (debug) printTree(thisdbSubModuleNode);
                        trueModuleFalseInstance = true;
                        tmpdbSubModuleNode = tmpdbSubModuleNode -> sub;
                     }
                  } else {
                     rootToTopLeafTmpNode -> sub = initNode(tmpdbSubModuleNode -> id);
                     rootToTopLeafTmpNode = rootToTopLeafTmpNode -> sub;
                     tmpdbSubModuleNode = tmpdbSubModuleNode -> sub;
                  }
                  break;
               }
               if (tmpdbSubModuleNode -> next == NULL) {
                  if (debug) printf("Can't follow hierarchy tree d.\n");
                  break;
               } else
                  tmpdbSubModuleNode = tmpdbSubModuleNode -> next;
            }
            if (isTri)
            if (lhsCmpPtrNode -> next != NULL) {
               if (sameCluster) {
                  if (debug) printf("multiple lhs in same cluster\n");
                  break;
               }
            }
            if (rhsCmpPtrNode -> sub == NULL)
               break;
            if (lhsCmpPtrNode -> sub == NULL)
               break;
            rhsCmpPtrNode = rhsCmpPtrNode -> sub;
            lhsCmpPtrNode = lhsCmpPtrNode -> sub;
         }
         if (debug) printf("findSignalTopRouteStep2 route Signal: thisTopModuleNode: %d <-- b\n", thisTopModuleNode -> id);
         if (debug) printf("------------------- lhsTopPtrNode:\n");
         if (lhsTopPtrNode != NULL)
            if (debug) printTree(lhsTopPtrNode);
         ///////////////////////////////////////////
         //  simplify LHS list using chopTree
         ///////////////////////////////////////////
         if (!isTri)
         if (lhsTopPtrNode != NULL) {
            if (chopTree(lhsTopPtrNode) < 0) {
                printf("ERR.AUTOROUTE.HIERARCHICAL_PATH_NOT_CLEAR: %s\n", signalName.c_str());
                //return; 
                string preFix = "RHS: ";
                printSITree(preFix, true, true, true, thisRHSNode);
                preFix = "LHS: ";
                printSITree(preFix, true, true, true, lhsTopPtrNode);
                exit(-1);
            }
         }
         ///////////////////////////////////////////
         // find type in original DB_LHS
         ///////////////////////////////////////////
         if (debug) printf("nonTrivialTypeFound: %d sameCluster: %d\n", nonTrivialTypeFound, sameCluster);
         NODE* typeLHSNode = NULL;
         if ( (nonTrivialTypeFound) &
              (sameCluster)         ) {
            if (sameClusterTypeNode != NULL)
            if (sameClusterTypeNode -> sub != NULL)
               typeLHSNode = initNode(DB_SIGNAL_TYPE);
               typeLHSNode -> sub = sameClusterTypeNode -> sub;
            if (debug) printf("------------------- typeLHSNode:\n");
            if (typeLHSNode != NULL)
               if (debug) printTree(typeLHSNode);
         } else
         if (nonTrivialTypeFound)
         if (lhsTopPtrNode != NULL) {
            if (debug) printf("------------------- lhsTopPtrNode:\n");
            if (lhsTopPtrNode != NULL)
               if (debug) printTree(5, lhsTopPtrNode);
            if (debug) printf("------------------- rootToTopNode:\n");
            if (rootToTopNode != NULL)
               if (debug) printTree(5, rootToTopNode);
            if (debug) printf("------------------- lhsNode:\n");
            if (debug) printTree(lhsNode);
            NODE* tmpNode = lhsNode;
            while (true) {
               if (debug) printf("------------------- check:\n");
               if (debug) printTree(5, tmpNode);
               bool cont = false;
               if (rootToTopNode -> sub -> sub == NULL)
                  cont = true;
               else
               if (listCoveredInTree(rootToTopNode -> sub -> sub, tmpNode -> sub))
                  cont = true;
               if (cont)
               if (listCoveredInTree(lhsTopPtrNode, tmpNode -> sub, true)) {
                  if (debug) printf("found\n");
                  typeLHSNode = initNode(DB_SIGNAL_TYPE);
                  typeLHSNode -> sub = tmpNode -> next -> sub;
                  if (debug) printf("------------------- typeLHSNode:\n");
                  if (debug) printTree(typeLHSNode);
                  break;
               }
               tmpNode = tmpNode -> next;
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
         }
         if (typeLHSNode != NULL) 
         if (typeLHSNode -> sub != NULL) 
         if (typeLHSNode -> sub -> id == G_PDVL_TYPE_IDENTIFIER_DATA_TYPE) {
            if (debug) printf("isTop: %d\n", lhsTopPtrNode -> sub == NULL);
            if (debug) printf("------------------- thisTopModuleNode:\n");
            if (debug) 
               if (thisTopModuleNode != NULL)
                  printTree(5, thisTopModuleNode);
            string classString = "";
            if (lhsTopPtrNode -> sub == NULL)
               getModuleNameAndUpdateType(lhsTopPtrNode, thisTopModuleNode, true, false, classString, signalName, typeLHSNode);
            else
               getModuleNameAndUpdateType(lhsTopPtrNode, thisdbSubModuleNode -> sub, false, true, classString, signalName, typeLHSNode);
            NODE* classTypeNode = initNode(0);
            parser_sv_class_type(classString, 0, classTypeNode);
            if (debug) printTree(classTypeNode);
            NODE* classScopeNode = initNode(G_SV_CLASS_SCOPE);
            classScopeNode -> sub = classTypeNode;
            classScopeNode -> next = typeLHSNode -> sub -> sub;
            typeLHSNode -> sub -> sub = classScopeNode;
         }
         ///////////////////////////////////////////
         // Route lhs and add wire
         ///////////////////////////////////////////
         if (lhsTopPtrNode != NULL) {
            if (debug) printf("addWire\n");
            addWire(signalName, typeLHSNode, thisTopModuleNode);

            if (debug) printf("route lhs\n");
            addPort(lhsTopPtrNode, thisdbSubModuleNode -> sub, signalName, true, false, typeLHSNode, rootToTopNode, rootToTopLeafNode);
         }  

         ///////////////////////////////////////////
         // Route rhs
         ///////////////////////////////////////////
         if (debug) printf("route rhs\n");         
         if (signalName.compare("c_sys_rst") == 0) {
            if (debug) printf("------------------- rhsTopPtrNode:\n");
            if (debug) printTree(rhsTopPtrNode);
         }
         if (debug)
         if (rhsTopPtrNode != NULL) {
            if (debug) printf("------------------- hierarchyListRootNode:\n");
            if (debug) printTree(hierarchyListRootNode);
            if (debug) printf("------------------- rootToTopNode:\n");
            if (debug) printTree(rootToTopNode);
            if (debug) printf("------------------- rootToTopLeafNode:\n");
            if (debug) printTree(rootToTopLeafNode);
            if (debug) printf("------------------- rhsTopPtrNode:\n");
            if (debug) printTree(rhsTopPtrNode);
         }
         if (rhsTopPtrNode != NULL) {
            addPort(rhsTopPtrNode, thisdbSubModuleNode -> sub, signalName, true, true, typeLHSNode, rootToTopNode, rootToTopLeafNode);
         }
         delete hierarchyListNode -> sub;
         hierarchyListNode -> sub = NULL;
      }
   }
   //////////////////////////////////////////
   // continue pass through RHS Tree next
   //////////////////////////////////////////
   if (rhsNode -> next != NULL)
      findSignalTopRouteStep2(signalName, rhsNode -> next, lhsNode, isTop, isTri, hierarchyListRootNode, hierarchyListNode, 
                              topModuleNode, dbSubModuleNode);   
}
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
                              NODE* dbSubModuleNode) {
   bool debug = false;
   if (debug) printf("findSignalTopRouteStep1 route id: %d\n", node -> id);
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      thisHeader.append(node2String(node));                              
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0) {
            NODE* thisHierarchyListNode = hierarchyListNode;
            NODE* passHierarchyListNode = hierarchyListNode;
            if (hierarchyListNode != NULL) {
               passHierarchyListNode = initNode(node -> id);
               hierarchyListNode -> sub = passHierarchyListNode;
            }
            findSignalTopRouteStep1(level, thisHeader, node -> sub, signalName, typeNode, lhsNode, hierarchyListRootNode, passHierarchyListNode, topModuleNode, dbSubModuleNode);
            if (thisHierarchyListNode != NULL) {
               delete passHierarchyListNode;
               thisHierarchyListNode -> sub = NULL;
            }
         } else {
            if (debug) {
               printf("findSignalTopRouteStep1 route signal: %s\n", thisHeader.c_str());
               printTree(5, node -> sub);
            }
            NODE* thisHierarchyListNode = hierarchyListNode;
            NODE* passHierarchyListNode = hierarchyListNode;
            if (hierarchyListNode != NULL) {
               passHierarchyListNode = initNode(node -> id);
               hierarchyListNode -> sub = passHierarchyListNode;
               hierarchyListNode = passHierarchyListNode;
               passHierarchyListNode = initNode(0);
               hierarchyListNode -> sub = passHierarchyListNode;
               hierarchyListNode = passHierarchyListNode;
            }
            if (node -> sub -> sub != NULL) {
               if (level == 0) {
                  signalName = thisHeader;
                  NODE* lhsNode = NULL;
                  NODE* rhsNode = NULL;
                  NODE* parameterAssignmentNode = NULL;
                  /////////////////////////////////////////////////////////////
                  //	The first two sub nodes are either DB_LHS or DB_RHS
                  /////////////////////////////////////////////////////////////
                  NODE* tmpNode = node -> sub -> sub;
                  while (true) {
                     if (tmpNode -> id == DB_LHS)
                        lhsNode = tmpNode;
                     if (tmpNode -> id == DB_RHS)
                        rhsNode = tmpNode;
                     if (tmpNode -> id == DB_PAS)
                        parameterAssignmentNode = tmpNode;
                     if (tmpNode -> next == NULL)
                        break;
                     tmpNode = tmpNode -> next;
                  }
                  /////////////////////////////////////////////////////////////
                  //	At level 0, continue only when RHS and LHS exist, continue RHS
                  /////////////////////////////////////////////////////////////
                  if (lhsNode != NULL)
                  if (lhsNode -> sub != NULL)
                  if (lhsNode -> sub -> sub != NULL)
                  if (rhsNode != NULL)
                  if (rhsNode -> sub -> sub != NULL)
                  if (rhsNode -> sub != NULL) {
                     if (debug) printTree(node -> sub);
                     if (debug) printf("\tRHS: %d\n", rhsNode -> sub -> id);
                     if (debug) printf("------------------- rhsNode -> sub:\n");
                     if (debug) printTree(5, rhsNode -> sub);
                     if (debug) printf("------------------- lhsNode -> sub:\n");
                     if (debug) printTree(5, lhsNode -> sub);
                     /////////////////////////////////////////////
                     // Route all rhs clusters
                     /////////////////////////////////////////////
                     NODE* thisRHSNode = rhsNode -> sub;
                     NODE* thisLHSNode = lhsNode -> sub;
                     if (debug) printf("------------------- thisLHSNode -> id: %d thisRHSNode -> id: %d\n", thisLHSNode -> id, thisRHSNode -> id);
                     if (debug) printTree(lhsNode -> sub);
                     /////////////////////////////////////////////
                     // found top level LHS, only one LHS allowed so far
                     /////////////////////////////////////////////
                     if (0) { //thisLHSNode -> sub -> id == 0) {
                        if (debug) printf("Route top level lhs.\n");
                        while (true) { 
                           if (thisRHSNode -> next == NULL)
                              break;
                           thisRHSNode = thisRHSNode -> next;
                        }
                     /////////////////////////////////////////////
                     // else, continue RHS
                     /////////////////////////////////////////////
                     } else {
                        hierarchyListRootNode = initNode(0);
                        hierarchyListNode = hierarchyListRootNode;
                        findSignalTopRouteStep2(signalName, thisRHSNode, thisLHSNode, true, false, hierarchyListRootNode, hierarchyListNode, 
                                                topModuleNode, dbSubModuleNode);
                     }
                  }
               /////////////////////////////////////////////////////////////
               //	Level != 0 => continue
               /////////////////////////////////////////////////////////////
               } else {
                  string tmpHeader = "";
                  findSignalTopRouteStep1(level + 1, tmpHeader, node -> sub -> sub, signalName, typeNode, lhsNode, hierarchyListRootNode, passHierarchyListNode, topModuleNode, dbSubModuleNode);
               }
            }
            if (debug) printf("\n\n");
            if (node -> sub -> next != NULL) {
               findSignalTopRouteStep1(level, thisHeader, node -> sub -> next, signalName, typeNode, lhsNode, hierarchyListRootNode, passHierarchyListNode, topModuleNode, dbSubModuleNode);
            }
            if (thisHierarchyListNode != NULL) {
               thisHierarchyListNode -> sub = NULL;
               hierarchyListNode = thisHierarchyListNode;
            }
         } 
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Place new parameter type, step 2
/////////////////////////////////////////////////////////////////////////////////
bool placeNewParameterTypeStep2 (NODE* hierPathNode,
                                 bool trueTypeFalseParameter,
                                 bool trueModuleFalseInstance,
                                 bool isTop, 
                                 NODE* hierDesignNode, 
                                 NODE* assignmentNode) {
   bool debug = false;
   bool returnBool = false;
   if (debug) {
      printf("hierPathNode:\n");
      printTree(hierPathNode);
      printf("hierDesignNode:\n");
      printTree(6, hierDesignNode);
   }
   ////////////////////////////////////////////
   //  traverse through parameter name SI tree
   ////////////////////////////////////////////
   while (1) {
      if (debug) printf("isTop %d hierPathNode: %d hierDesignNode: %d hierDesignNode -> next: %d\n", isTop, hierPathNode -> id, hierDesignNode -> id, hierDesignNode -> next);
      if ( (isTop)                                      |
           (hierDesignNode -> id == hierPathNode -> id) ) {
         if ( (isTop)                          |
              ( (hierPathNode -> id == 0)    &
                (!(trueModuleFalseInstance)) ) ) {
            if (debug) {
               printf("hierDesignNode:\n");
               printTree(6, hierDesignNode);
               printf("assignmentNode:\n");
               printTree(assignmentNode);
            }
            ////////////////////////////////////////////
            //  End of hierPathNode
            ////////////////////////////////////////////
            if (hierPathNode -> sub == NULL) {
               returnBool = true;
               unsigned entryId = DB_MODULE_PARAMETER;
               if (assignmentNode -> sub != NULL) 
               if (assignmentNode -> sub -> id == G_SV_FUNCTION_BODY_DECLARATION)
                  entryId = DB_MODULE_FUNCTIONS;
               else
               if (assignmentNode -> sub -> id == G_SV_DATA_TYPE)
                  entryId = DB_MODULE_TYPES;
               ////////////////////////////////////////////
               //  Check if parameter already exists
               //  Get DB_MODULE_PARAMETER node
               ////////////////////////////////////////////
               bool found = false;
               NODE* hierClDesignNode = hierDesignNode -> sub;
               if (isTop)
                  hierClDesignNode = hierDesignNode;
               NODE* foundDBEntryNode = NULL;
               while (1) {
                  NODE* dbEntryNode = hierClDesignNode -> sub;
                  while (1) {
                     if (dbEntryNode -> id == entryId) {
                        if (debug) printf("set foundDBEntryNode\n");
                        foundDBEntryNode = dbEntryNode;
                        ////////////////////////////////////////////
                        //  Check in sub cluster id node
                        ////////////////////////////////////////////
                        NODE* tmpClNode = dbEntryNode -> sub;
                        while (1) {
                           ////////////////////////////////////////////
                           //  Check in parameter list
                           ////////////////////////////////////////////
                           NODE* parameterListNode = tmpClNode -> sub;
                           if (debug) printTree(parameterListNode);
                           while (1) {
                              if (checkTree(parameterListNode -> sub, assignmentNode -> sub)) {
                                 found = true;
                                 if (debug) printf("found parameter!\n");
                              }
                              if (parameterListNode -> next == NULL)
                                 break;
                              parameterListNode = parameterListNode -> next;
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
                  if (hierClDesignNode -> next == NULL)
                     break;
                  hierClDesignNode = hierClDesignNode -> next;
               }
               if (debug) printf("found parameter\\type: %d\n", found);
               if (debug) printTree(assignmentNode);
               ////////////////////////////////////////////
               //  Add if parameter does not already exists
               ////////////////////////////////////////////
               if (!(found)) {
                  ////////////////////////////////////////////
                  //  Add in last dbEntryNode or generate on 
                  ////////////////////////////////////////////
                  NODE* dbEntryNode;
                  if (foundDBEntryNode != NULL) {
                     if (debug) printf("foundDBEntryNode:\n");
                     if (debug) printTree(foundDBEntryNode);
                     dbEntryNode = foundDBEntryNode;
                  } else if (isTop) {
                     dbEntryNode = initNode(entryId);
                     if (debug) printf("dbEntryNode:\n");
                     if (debug) printTree(dbEntryNode);
                     dbEntryNode -> next = hierDesignNode -> sub;
                     hierDesignNode -> sub = dbEntryNode;
                  } else if (hierDesignNode -> sub != NULL) {
                     NODE* hierClDesignNode = hierDesignNode -> sub;
                     dbEntryNode = hierClDesignNode -> sub;
                     while (dbEntryNode -> next != NULL) dbEntryNode = dbEntryNode -> next;
                     dbEntryNode -> next = initNode(entryId);
                     dbEntryNode = dbEntryNode -> next;
                  } else {
                     NODE* hierClDesignNode = initNode(-1);
                     NODE* hierDesignSubNode = hierDesignNode -> sub;
                     while (hierDesignNode -> next != NULL) hierDesignNode = hierDesignNode -> next;
                     hierDesignNode -> next = hierClDesignNode;
                     dbEntryNode = initSubNode(hierClDesignNode, entryId);
                  }
                  NODE* subClNode = initNode(-1);
                  subClNode -> next = dbEntryNode -> sub;
                  dbEntryNode -> sub = subClNode;
                  unsigned subEntryId = G_SV_PARAMETER_DECLARATION;
                  if (assignmentNode -> sub != NULL)
                  if (assignmentNode -> sub -> id == G_SV_FUNCTION_BODY_DECLARATION)
                     subEntryId = G_SV_FUNCTION_DECLARATION;
                  if (trueTypeFalseParameter)
                     subEntryId = G_SV_TYPE_DECLARATION;
                  NODE* paraDeclarationNode = initSubNode(subClNode, subEntryId);
                  paraDeclarationNode -> sub = assignmentNode -> sub;
                  if (debug) printf("paraDeclarationNode:\n");
                  if (debug) printTree(paraDeclarationNode);
               }
               if (debug) {
                  printf("hierDesignNode:\n");
                  printTree(6, hierDesignNode);
               }
            } else
            ////////////////////////////////////////////
            //  continue next hierarchy level
            ////////////////////////////////////////////
            if (hierDesignNode -> sub != NULL) {
               if (debug) printf("next hierarchy level:\n"); 
               NODE* hierClDesignNode = hierDesignNode -> sub;
               if (debug) printf("hierPathNode:\n");
               if (debug) printTree(4, hierPathNode);
               if (debug) printf("hierClDesignNode:\n");
               if (debug) printTree(4, hierClDesignNode);
               while (1) {
                  NODE* dbEntryNode = hierClDesignNode -> sub;
                  while (1) {
                     if (dbEntryNode -> id == DB_SUB_MODULES)
                        break;
                     if (dbEntryNode -> next == NULL)
                        break;
                     dbEntryNode = dbEntryNode -> next;
                  }
                  if (dbEntryNode -> id == DB_SUB_MODULES)
                  if (hierPathNode -> sub != NULL)
                     if (placeNewParameterTypeStep2(hierPathNode -> sub, trueTypeFalseParameter, true, false, dbEntryNode -> sub, assignmentNode))
                        returnBool = true;
                  if (hierClDesignNode -> next == NULL)
                     break;
                  hierClDesignNode = hierClDesignNode -> next;
               }
               if (debug) printf("continue placeNewParameterTypeStep2.\n"); 
            }
            break;
         } else
         if (hierDesignNode -> sub != NULL) {
            bool tmpBool = trueModuleFalseInstance;
            if (hierPathNode -> id == 0)
               tmpBool = false;
            if (hierPathNode -> sub != NULL)
               if (placeNewParameterTypeStep2(hierPathNode -> sub, trueTypeFalseParameter, tmpBool, false, hierDesignNode -> sub, assignmentNode))
                  returnBool = true;
         }
      }
      if (isTop)
         break;
      if (returnBool)
         break;
      if (hierDesignNode -> next == NULL)
         break;
      hierDesignNode = hierDesignNode -> next;
   }
   return returnBool;
}
/////////////////////////////////////////////////////////////////////////////////
/// Place new parameter type, step 1
/////////////////////////////////////////////////////////////////////////////////
void placeNewParameterTypeStep1 (unsigned level, 
                                 string &header,
                                 bool trueTypeFalseParameter, 
                                 NODE* node,
                                 NODE* topModuleNode,
                                 NODE* dbParameterNode,
                                 NODE* dbFunctionNode) {
   bool debug = false;
   if (debug) printf("placeNewParameterTypeStep1 place id: %d\n", node -> id);
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      thisHeader.append(node2String(node));                              
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0) {
            placeNewParameterTypeStep1(level + 1, thisHeader, trueTypeFalseParameter, node -> sub, topModuleNode, dbParameterNode, dbFunctionNode);
         } else {
            if (debug)
               printf("placeNewParameterTypeStep1 place signal: %s\n", thisHeader.c_str());
            if (debug) printTree(5, node -> sub);
            NODE* dbRHSNode = node -> sub -> sub -> sub;
            if (debug) printf("dbRHSNode: \n");
            if (debug) printTree(dbRHSNode);
            if (dbRHSNode -> next != NULL) {
               NODE* dbLHSNode = dbRHSNode -> next;
               if (debug) printf("dbLHSNode: \n");
               if (debug) printTree(dbLHSNode);
               NODE* tmpNode = dbRHSNode -> sub;
               while (1) {
                  if (debug) printf("place at: \n");
                  if (debug) printTree(tmpNode -> sub);

                  NODE* lhsPtrNode = dbLHSNode -> sub;
                  if (lhsPtrNode -> next != NULL) 
                  if (lhsPtrNode -> next -> next != NULL) {
                     NODE* tmpEventDevNode = lhsPtrNode; 
                     unsigned minDist = 10000;
                     while (1) {
                        if (debug) printf("---------------------\n");
                        if (debug) printTree(tmpNode -> sub);
                        if (debug) printf("---------------------\n");
                        if (debug) printTree(tmpEventDevNode -> sub -> sub);
                        unsigned dist = (unsigned)getDist(tmpNode -> sub, tmpEventDevNode -> sub -> sub);
                        if (debug) printf("dist: %d\n", dist);
                        if (dist == 0) {
                           lhsPtrNode = tmpEventDevNode;
                              break;
                        }
                        if (dist < minDist) {
                           lhsPtrNode = tmpEventDevNode;
                           minDist = dist;
                        }
                        if (tmpEventDevNode -> next -> next == NULL)
                           break;
                        tmpEventDevNode = tmpEventDevNode -> next -> next;
                     }
                  }
                  NODE* assignmentNode = lhsPtrNode -> next; 
                  if (debug) printf("-------------------------- tmpNode:\n");
                  if (debug) printTree(tmpNode);


                  if (tmpNode -> sub -> sub == NULL) {
                     if (debug) printf("topModuleNode: \n");
                     if (debug) printTree(5, topModuleNode);
                     placeNewParameterTypeStep2(tmpNode -> sub, trueTypeFalseParameter, true, true, topModuleNode, assignmentNode);
                  } else {
                     NODE* dbEntryNode = topModuleNode -> sub;
                     while (1) {
                        if (dbEntryNode -> id == DB_SUB_MODULES) {
                           placeNewParameterTypeStep2(tmpNode -> sub -> sub, trueTypeFalseParameter, true, false, dbEntryNode -> sub, assignmentNode);
                           break;
                        }
                        if (dbEntryNode -> next == NULL)
                           break;
                        dbEntryNode = dbEntryNode -> next;
                     }
                  }
                  ///////////////////////////////////////
                  // add new parameters in assignment to rhs
                  ///////////////////////////////////////
                  if (debug) {
                     printf("checking: \n");
                     printTree(tmpNode);
                     printf("assignmentNode: \n");
                     printTree(assignmentNode);
                  }
                  NODE* rhsTree = initNode(0);
                  NODE* paramAssignmentNode = getNode(assignmentNode -> sub, G_SV_PARAM_ASSIGNMENT);
                  if (paramAssignmentNode != NULL) {
                     getRHSTree(true, paramAssignmentNode -> sub -> next, rhsTree);
                  } else
                     getRHSTree(true, assignmentNode -> sub, rhsTree);
                  if (rhsTree -> sub != NULL) {
                     if (debug) printf("rhsTree: \n");
                     if (debug) printTree(rhsTree);
                     if (1) {
                        NODE* givenSIRootNode = initNode(G_SI);
                        NODE* thisRootToTopNode = copyTree(tmpNode);
                        if (addToParameterRHSNode(rhsTree -> sub, 
                                                  givenSIRootNode,
                                                  givenSIRootNode,
                                                  thisRootToTopNode,
                                                  dbParameterNode))
                           dbParameterNode -> id = 1;
                     }
                     if (1) {
                        NODE* givenSIRootNode = initNode(G_SI);
                        NODE* thisRootToTopNode = copyTree(tmpNode);
                        if (addToParameterRHSNode(rhsTree -> sub, 
                                                  givenSIRootNode,
                                                  givenSIRootNode,
                                                  thisRootToTopNode,
                                                  dbFunctionNode))
                           dbFunctionNode -> id = 1;
                     }
                  }
                  if (debug) printf("continue: \n");
                  if (tmpNode -> next == NULL)
                     break;
                  tmpNode = tmpNode -> next;
               }
            }
            if (node -> sub -> next != NULL) {
               placeNewParameterTypeStep1(level + 1, thisHeader, trueTypeFalseParameter, node -> sub -> next, topModuleNode, dbParameterNode, dbFunctionNode);
            }
         } 
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
   if (debug) printf("return placeNewParameterTypeStep1\n");
}
////////////////////////////////////////////////////////////////////////////////
/// Route all signals in module hierarchy
/////////////////////////////////////////////////////////////////////////////////
void routeSignalsInModuleHierarchy (NODE* topModuleNode) {
   bool debug = false;
   if (debug) printTree(3, topModuleNode);
   // Get dbSubModuleNode once for top level signals
   NODE* dbEntryNode = topModuleNode -> sub;
   NODE* dbSubModuleNode = NULL;
   while (true) {
      if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
      if (dbEntryNode -> id == DB_SUB_MODULES) {
         dbSubModuleNode = dbEntryNode;
         break;
      }
      if (dbEntryNode -> next == NULL) {
         break;
         printf("System hierarchy not found! b\n");
         exit(-1);
      }
      dbEntryNode = dbEntryNode -> next;
   } 

   if (dbSubModuleNode == NULL) {
      if (reportLevel >= 2)
         printf("Design hierarchy not found!\n");
      return;
   }

   ////////////////////////////////////////////
   // Collect types in global dbTypeNode
   ////////////////////////////////////////////
   if (reportLevel > 1)
      printf("3.1 Locate type definitions.\n");
   NODE* dbParameterNode = initNode(0);
   NODE* dbTypeNode = initNode(0);
   NODE* dbFunctionNode = initNode(0);
   if (1) {
      NODE* rootNode = initNode(0);
      NODE* leafNode = rootNode; 
      NODE* leafSubNode = initSubNode(leafNode, 0);
      NODE* leafSubSubNode = initSubNode(leafSubNode, 0);
      getGlobalSignalTreeStep1(topModuleNode, rootNode, 
                               true, // trueType, 
                               true, // trueFullFalseParameterLHS,
                               dbParameterNode, dbTypeNode, dbFunctionNode, leafNode);
   }

   if (debug) printf("dbTypeNode: \n");
   if (debug) printSITree(dbTypeNode);
   if (debug) printTree(dbTypeNode);
   if (debug) printf("dbFunctionNode: \n");
   if (debug) printSITree(dbFunctionNode);
   if (debug) printTree(dbFunctionNode);
   
   if (dbTypeNode -> sub != NULL) {
      string tmpHeader = "";
      placeNewParameterTypeStep1(0, tmpHeader, true, dbTypeNode -> sub, topModuleNode, dbTypeNode, dbFunctionNode);
   }

   ////////////////////////////////////////////
   // Collect signals in global dbSignalNode
   ////////////////////////////////////////////
   if (reportLevel > 1)
      printf("3.2 Locate signals.\n");
   if (1) {
      NODE* rootNode = initNode(0);
      NODE* leafNode = rootNode; 
      NODE* leafSubNode = initSubNode(leafNode, 0);
      NODE* leafSubSubNode = initSubNode(leafSubNode, 0);
      getGlobalSignalTreeStep1(topModuleNode, rootNode, false, true, dbParameterNode, dbTypeNode, dbFunctionNode, leafNode);
   }
   if (debug) printf("dbSignalNode: \n");
   if (debug) printSITree(dbSignalNode);
   if (debug) printTree(dbSignalNode);

   if (debug) printf("dbParameterNode: \n");
   if (debug) printSITree(dbParameterNode);
   if (debug) printTree(5, dbParameterNode);
   if (debug) printf("dbFunctionNode: \n");
   if (debug) printSITree(dbFunctionNode);
   if (debug) printTree(dbFunctionNode);
      
   if (dbSignalNode -> sub == NULL) {
      if (reportLevel >= 2)
         printf("Signal hierarchy not found!\n");
      return;
   }

   ////////////////////////////////////////////
   // Automatic routing
   ////////////////////////////////////////////
   if (reportLevel > 1)
      printf("3.3 Execute automatic routing.\n");
   string tmpHeader = "";   
   string signalName = "";   
   findSignalTopRouteStep1(0, tmpHeader, dbSignalNode -> sub, signalName, NULL, NULL, NULL, NULL, topModuleNode, dbSubModuleNode);
   
   ////////////////////////////////////////////
   // Parameter and function handling
   ////////////////////////////////////////////
   if (reportLevel > 1)
      printf("3.4 Handle parameters and functions.\n");
   if (1) {
      NODE* rootNode = initNode(0);
      NODE* leafNode = rootNode; 
      NODE* leafSubNode = initSubNode(leafNode, 0);
      NODE* leafSubSubNode = initSubNode(leafSubNode, 0);
      getGlobalSignalTreeStep1(topModuleNode, rootNode, false, false, dbParameterNode, dbTypeNode, dbFunctionNode, leafNode);
   }
   if (dbParameterNode -> sub != NULL) {
      if (debug) printf("dbParameterNode: \n");
      if (debug) printSITree(dbParameterNode);
      if (debug) printTree(5, dbParameterNode);
      
      for (int i = 0; i < 4; i += 1) {
         if (debug) printf("parameterLoop: %d\n", i);
         if (dbFunctionNode -> sub != NULL) {
            dbFunctionNode -> id = 0;
            string tmpHeader = "";
            placeNewParameterTypeStep1(0, tmpHeader, true, dbFunctionNode -> sub, topModuleNode, dbParameterNode, dbFunctionNode);
            if (debug) printf("dbFunctionNode -> id: %d\n", dbFunctionNode -> id);
         }
         
         if (dbParameterNode -> sub != NULL) {
            dbParameterNode -> id = 0;
            string tmpHeader = "";
            placeNewParameterTypeStep1(0, tmpHeader, false, dbParameterNode -> sub, topModuleNode, dbParameterNode, dbFunctionNode);
         }
         if (dbParameterNode -> id == 0)
         if (dbFunctionNode -> id == 0)
            break;
      }
   }
}
