//
// Copyright 2024 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

#include <nodesAndTrees.h>
#include <parser.h>
#include <mrphsBasics.h>

/////////////////////////////////////////////////////////////////////////////////
///	mrphsElaborateArguments
/////////////////////////////////////////////////////////////////////////////////
void mrphsElaborateArguments (int argc, char **argv, unsigned tool, NODE* sourceNode, string* outputDir, string* topLevelName)
{
   /////////////////////////////////
   // Show help
   /////////////////////////////////
   for (int i = 1; i < argc; i++)
   {
      string argument = argv[i];
      if ( (argument == "--help") |
           (argument == "-h")    ) {
         if (tool == 0) printf("Usage: MRPHS_D [Options] [Files]\n");
         if (tool == 1) printf("Usage: MRPHS_F [Options] [Files]\n");
         printf("Options:\n");
         printf("   -h, --help:\tDisplay this text and exit\n");
         printf("   -rl:\t\tReport level\n");
         printf("   -s:\t\tSource file (list)\n");
         printf("   -top:\tTop level name\n");
         printf("   -o:\t\tOutput directory\n");
         exit(-1);
      }
   }

   /////////////////////////////////
   // Get report level
   /////////////////////////////////
   reportLevel = 1;
   for (int i = 1; i < argc; i++)
   {
      string argument = argv[i];
      if (argument.length() == 3)
      if (argument.compare("-rl") == 0)
      if (i + 1 < argc) {
         char *pCh;
         reportLevel = strtoul(argv[i + 1], &pCh, 10);
      }
   }

   if (reportLevel > 0)
      printf("MRPHS started.\n1 Reading source files.\n");
   if (reportLevel > 1)
      printf("1.1 Setting report level %d.\n", reportLevel);
      
   /////////////////////////////////
   // Read all sources
   // Get output directory
   // Get top level
   /////////////////////////////////
   for (int i = 1; i < argc; i++)
   {
      string argument = argv[i];
      if (argument.length() == 2) {
         if (argument.compare("-s") == 0) {
            for (i = i + 1; i < argc; i++)
            {               
               argument = argv[i];
               //check for new option;
               if (argument.find("-") == 0)
                  break;
               if (reportLevel > 1)
                  printf("1.2 Initialization: Reading file %s.\n", argument.c_str());

               app = fopen(argv[i],"r");
               if (!app) {
                  printf("ERROR.READING.FILE_DOES_NOT_EXIST: %s\n", argument.c_str());
                  exit(-1);
               }
               fseek(app,0,SEEK_END);
               int size = ftell(app) + 1;
               rewind(app);

               string source;
               readPDVL(source, true);
                
               int pass;
               maxPtr = 0;        
               if (sourceNode -> id == 0) {
                  pass = parser_grammar(source, 0, sourceNode);
               } else {      
                  NODE* tmpSourceNode = new NODE();
                  pass = parser_grammar(source, 0, tmpSourceNode);
                  if (pass > 0)
                  if (sourceNode -> id != 0)
                  {
                     NODE* tmpNode = tmpSourceNode -> sub;
                     while (1) {
                        if (tmpNode -> next == NULL)
                           break;
                        tmpNode = tmpNode -> next;
                     }
                     tmpNode -> next = sourceNode -> sub;
                     sourceNode -> sub = tmpSourceNode -> sub;
                  }
                  delete tmpSourceNode;
               }
            
               if (maxPtr > 0)
               if (pass == 0) {
                  printError();
                  fclose(app);
                  fprintf(stdout, "Exiting converter.\n");
                  exit (-1);
               }
               fclose(app);
            }
         }
      }
   }   
   for (int i = 1; i < argc; i++)
   {
      string argument = argv[i];
      if (argument.length() == 2) {
         if (argument.compare("-o") == 0)
         if (i + 1 < argc) {
            *outputDir = argv[i + 1];
            if (reportLevel > 1)
               printf("1.3 Setting output directory to %s.\n", (*outputDir).c_str());
         }
      }
   }
   for (int i = 1; i < argc; i++)
   {
      string argument = argv[i];
      if (argument.length() == 4)
      if (argument.compare("-top") == 0)
      if (i + 1 < argc) {
         *topLevelName = argv[i + 1];
         if (reportLevel > 1)
            printf("1.4 Setting top level to %s.\n", (*topLevelName).c_str());
      }
   }   
}
/////////////////////////////////////////////////////////////////////////////////
///  Check if NODE exists on this level with the given id.
///  If it exists, return the NODE.
///  If it does not exist, a new one is inserted and returned.
/////////////////////////////////////////////////////////////////////////////////
NODE* getConstructListNode (NODE* node, 
                            unsigned dbID) {
   if (node -> id == dbID) return node;
   if (node -> next != NULL) return getConstructListNode(node -> next, dbID); 
   NODE* returnNode = initNode(dbID);
   node -> next = returnNode;
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Searches for a module with the given name.
/////////////////////////////////////////////////////////////////////////////////
NODE* getModule (string &moduleName) {
   //printTree(0, dbNode); 
   if (dbNode -> next == NULL)
      return NULL;
   if (dbNode -> next -> sub == NULL)
      return NULL;
   NODE* tmpNode = dbNode -> next -> sub;
   while (1) {
     string tmpModuleName = getSI(tmpNode -> sub); //getModuleName(tmpNode -> sub);
     // found, return moduleNode;         
     if (tmpModuleName.compare(moduleName) == 0) {
        return tmpNode; }
     // not found
     if (tmpNode -> next == NULL)
        return NULL;
     tmpNode = tmpNode -> next; }
}
/////////////////////////////////////////////////////////////////////////////////
/// Returns sub-modules
/////////////////////////////////////////////////////////////////////////////////
NODE* getSubModule (NODE* targetModuleHierNode, 
                    NODE* modNode) {
   bool debug = false;
   if (modNode -> sub == NULL)
      return NULL;
         NODE* dbEntryNode = modNode -> sub;
         while (true) {
            if (debug) printf("check dbEntryNode: %d\n", dbEntryNode -> id);
            if (dbEntryNode -> id == DB_SUB_MODULES) {
               NODE* tmpSINode = getNode(targetModuleHierNode, G_SI);
               NODE* targetInstatiationNode = getSITreeNode(1, tmpSINode -> sub, dbEntryNode -> sub);
               return targetInstatiationNode;
            }
            if (dbEntryNode -> next == NULL) {
               break;
            }
            dbEntryNode = dbEntryNode -> next;
         }
  return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
/// Copy tree of joined clusters
/////////////////////////////////////////////////////////////////////////////////
NODE* copyJoinedClusterTree (NODE* node, 
                             NODE* copiedJoinedClusterHashNode, 
                             unsigned *clCntPtr) {
   NODE* returnNode = initNode(node -> id);
   if (node -> id == 0) {
      unsigned thisPtr = 0;
      if (copiedJoinedClusterHashNode -> sub == NULL) {
         *clCntPtr = *clCntPtr + 1;
         thisPtr = *clCntPtr;
         NODE* subNode = initSubNode(copiedJoinedClusterHashNode, node -> sub -> id);
         subNode = initSubNode(subNode, *clCntPtr); 
      } else {
         NODE* tmpNode = copiedJoinedClusterHashNode -> sub;
         while (1) {
            if (tmpNode -> id == node -> sub -> id) {
               thisPtr = tmpNode -> sub -> id;
               break;
            }
            if (tmpNode -> next == NULL) {
               *clCntPtr = *clCntPtr + 1;
               thisPtr = *clCntPtr;
               NODE* subNode = initNode(node -> sub -> id);
               tmpNode -> next = subNode;
               subNode = initSubNode(subNode, *clCntPtr); 
               break;
            }
            tmpNode = tmpNode -> next;
         }
      }
      NODE* newClusterNode = initNode(thisPtr);
      returnNode -> sub = newClusterNode;
      if (node -> sub != NULL)
      if (node -> sub -> sub != NULL)
         newClusterNode -> sub = copyTree(node -> sub -> sub);
   } else
   if (node -> sub != NULL) {
      returnNode -> sub = copyJoinedClusterTree(node -> sub, copiedJoinedClusterHashNode, clCntPtr);
   }
   if (node -> next != NULL)
      returnNode -> next = copyJoinedClusterTree(node -> next, copiedJoinedClusterHashNode, clCntPtr);
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Copy complete tree of a sub-module
/////////////////////////////////////////////////////////////////////////////////
NODE* copySubModuleTree (	NODE* node, 
                            bool trueModuleFalseInstance, 
              				NODE* rootModuleNameNode, 
              				NODE* ptrModuleNameNode, 
              				NODE* copiedJoinedClusterHashNode, 
              				unsigned *clCntPtr, 
              				unsigned *moCntPtr) {
   NODE* returnNode = initNode(node -> id);
   if (node -> id == 0) {
      if (trueModuleFalseInstance) {
         NODE* newModuleNameNode = initNode(node -> id);
         ptrModuleNameNode -> sub = newModuleNameNode;
         ptrModuleNameNode = newModuleNameNode;
         if (node -> sub != NULL)
            returnNode -> sub = copySubModuleTree(node -> sub, false, rootModuleNameNode, ptrModuleNameNode, copiedJoinedClusterHashNode, clCntPtr, moCntPtr);
      } else {
         *moCntPtr = *moCntPtr + 1;
         NODE* newModuleNode = initNode(*moCntPtr);
         returnNode -> sub = newModuleNode;
         NODE* dbListEntryNode = initNode(DB_LIST_ENTRY);
         dbListEntryNode -> sub = newModuleNode;
         ptrModuleNameNode -> sub = dbListEntryNode;
         mergeSITreesSubList(rootModuleNameNode -> sub, dbModuleNode -> sub);
         if (node -> sub != NULL)
         if (node -> sub -> sub != NULL)
            newModuleNode -> sub = copyModuleTree(node -> sub -> sub, copiedJoinedClusterHashNode, clCntPtr, moCntPtr);
      }
   } else
   if (node -> sub != NULL) {
      if (trueModuleFalseInstance) {
         NODE* newModuleNameNode = initNode(node -> id);
         ptrModuleNameNode -> sub = newModuleNameNode; 
         NODE* newptrModuleNameNode = newModuleNameNode;
         returnNode -> sub = copySubModuleTree(node -> sub, trueModuleFalseInstance, rootModuleNameNode, newptrModuleNameNode, copiedJoinedClusterHashNode, clCntPtr, moCntPtr);
         delete ptrModuleNameNode -> sub;
      } else
         returnNode -> sub = copySubModuleTree(node -> sub, trueModuleFalseInstance, rootModuleNameNode, ptrModuleNameNode, copiedJoinedClusterHashNode, clCntPtr, moCntPtr);
   }
   if (node -> next != NULL)
      returnNode -> next = copySubModuleTree(node -> next, trueModuleFalseInstance, rootModuleNameNode, ptrModuleNameNode, copiedJoinedClusterHashNode, clCntPtr, moCntPtr);
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Copy tree of a module
/////////////////////////////////////////////////////////////////////////////////
NODE* copyModuleTree (NODE* node, 
                      NODE* copiedJoinedClusterHashNode, 
                      unsigned *clCntPtr, 
                      unsigned *moCntPtr) {
   bool debug = false;
   if (debug) printf("copyModuleTree:\n");
   if (debug) printTree(node);
   NODE* returnNode = NULL;
   while (true) {
      if (debug) printf("copyModuleTree check: %d\n", node -> id);
      NODE* tmpNode = initNode(node -> id);
      if (node -> sub != NULL)
      if (node -> id == DB_SUB_MODULES) {
         NODE* rootModuleNameNode = initNode(G_SI);
         NODE* ptrModuleNameNode = rootModuleNameNode;
         tmpNode -> sub = copySubModuleTree(node -> sub, true, rootModuleNameNode, ptrModuleNameNode, copiedJoinedClusterHashNode, clCntPtr, moCntPtr);
      } else 
      if (node -> id == DB_JOINED_CLUSTERS) {
         tmpNode -> sub = copyJoinedClusterTree(node -> sub, copiedJoinedClusterHashNode, clCntPtr);
      } else {
         tmpNode -> sub = copyTree(node -> sub);
      }
      if (returnNode != NULL) {
         tmpNode -> next = returnNode;
         returnNode = tmpNode;
      } else
         returnNode = tmpNode;
      if (node -> next == NULL)
         break;
      node = node -> next;
   }
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Get all PDVL_EMIT entries in tree.
/////////////////////////////////////////////////////////////////////////////////
NODE* getLHSTree (NODE* node, 
                  NODE* lhsTree) {
   bool debug = false;
   if (	(node -> id == G_PDVL_EMIT) 	) {
      string lhsString = getSI(node);
      if (debug) printf("getLHSTree: %s\n", lhsString.c_str());
      if (debug) printTree(0, node);
      addSITree(node, NULL, lhsTree);
   } else {                
      if (node -> sub != NULL) getLHSTree(node -> sub, lhsTree);
      if (node -> next != NULL) getLHSTree(node -> next, lhsTree);
   } 
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
/// Return logic cone of a given RHS assignment name.
/////////////////////////////////////////////////////////////////////////////////
NODE* extractTreeLHS (string name, 
                      NODE* datapathRegTree, 
                      NODE* node) {
   bool debug = false;
   if (debug) {
      printf("extractTreeLHS of %s: %d\t", name.c_str(), node -> id);
      printGrammar(node -> id);
      printf("\n");
   }
   NODE* returnNode = NULL;
   if (	(node -> id == G_SV_BLOCKING_ASSIGNMENT) 	|
  		(node -> id == G_SV_BLOCKING_ASSIGNMENT) 	|
  		(node -> id == G_SV_BLOCKING_ASSIGNMENT) 	|
  		(node -> id == G_SV_BLOCKING_ASSIGNMENT) 	) {
      string tmpName = getSI(node);
      if (debug) printf("extractTreeLHS: %s\n", tmpName.c_str());
      if (tmpName.compare(name) == 0)
         return copyTree(node); 
   } else
   if (	(node -> id == G_SV_SEQ_BLOCK) 	) {
      if (node -> sub != NULL) {
         NODE* tmpNode = node -> sub;
         NODE* lastNode = NULL;
         while (true) {
            if (tmpNode -> sub != NULL) {
               NODE* subNode = extractTreeLHS(name, NULL, tmpNode -> sub);
               if (subNode != NULL) {
                  if (returnNode == NULL) {
                     returnNode = initNode(G_SV_SEQ_BLOCK);
                     NODE* statementOrNullNode = initNode(G_SV_STATEMENT_OR_NULL);
                     statementOrNullNode -> sub = subNode;
                     returnNode -> sub = statementOrNullNode;
                     lastNode = subNode;
                  } else {
                     NODE* statementOrNullNode = initNode(G_SV_STATEMENT_OR_NULL);
                     statementOrNullNode -> sub = subNode;
                     lastNode -> next = statementOrNullNode;
                  }
               }
            }
            if (tmpNode -> next == NULL)
               break;
            tmpNode = tmpNode -> next;
         }
      }
   } else
   if (	(node -> id == G_SV_CASE_STATEMENT) 	) {
      if (node -> sub != NULL) {
         bool found = false;
         returnNode = initNode(G_SV_CASE_STATEMENT);
         NODE* subNode = node -> sub;
         NODE* returnPtrNode = NULL;
         while (1) {
            NODE* newSubNode = initNode(subNode -> id);
            if (debug) printf("---------------------- subNode\n");
            if (debug) printTree(5, subNode);
            if (subNode -> id != G_SV_CASE_ITEM) {
               if (subNode -> sub != NULL)
                  newSubNode -> sub = copyTree(subNode -> sub);
            } else {
               newSubNode -> sub = initNode(subNode -> sub -> id);
               newSubNode -> sub -> sub = initNode(subNode -> sub -> sub -> id);
               newSubNode -> sub -> sub -> sub = copyTree(subNode -> sub -> sub -> sub);
               newSubNode -> sub -> sub -> next = initNode(subNode -> sub -> sub -> next -> id);
               if (debug) printf("---------------------- newSubNode\n");
               if (debug) printTree(5, newSubNode);
               NODE* statementNode = extractTreeLHS(name, NULL, subNode -> sub -> sub -> next -> sub);
               if (statementNode == NULL)
                  newSubNode -> sub -> sub -> next -> sub = initNode(G_SV_NULL_STATEMENT);
               else {
                  newSubNode -> sub -> sub -> next -> sub = statementNode;
                  found = true;
               }
            }
            if (returnNode -> sub == NULL) {
               returnNode -> sub = newSubNode;
               returnPtrNode = newSubNode;
            } else {
               returnPtrNode -> next = newSubNode;
               returnPtrNode = returnPtrNode -> next;
            }
            if (subNode -> next == NULL)
               break;
            subNode = subNode -> next;
         }
         if (!found) {
            deleteTree(returnNode);
            returnNode = NULL;
         }
      }
      if (debug) {
         printf("---------------------- returnNode\n");
         if (returnNode != NULL)
            printTree(returnNode);
         if (returnNode != NULL)
         if (name == "g")
            exit(-1);
      }
   } else
   if (	(node -> id == G_SV_IF_CONDITIONAL_STATEMENT) 	) {
      if (node -> sub != NULL) {
         NODE* trueSubNode = extractTreeLHS(name, NULL, node -> sub -> next -> sub);
         if ( (trueSubNode != NULL)  ) {
            returnNode = initNode(G_SV_IF_CONDITIONAL_STATEMENT);
            NODE* condNode = initNode(G_SV_COND_PREDICATE);
            condNode -> sub = node -> sub -> sub;
            returnNode -> sub = condNode;
            NODE* trueNode = initNode(G_SV_STATEMENT_OR_NULL);
            trueNode -> sub = trueSubNode;
            returnNode -> sub -> next = trueNode;
         }
      }
   } else
   if (	(node -> id == G_SV_IF_ELSE_CONDITIONAL_STATEMENT) 	) {
      if (node -> sub != NULL) {
         NODE* trueSubNode = extractTreeLHS(name, NULL, node -> sub -> next -> sub);
         NODE* falseSubNode = extractTreeLHS(name, NULL, node -> sub -> next -> next -> sub);
         if ( (trueSubNode != NULL)  | 
              (falseSubNode != NULL) ) {
            returnNode = initNode(G_SV_IF_ELSE_CONDITIONAL_STATEMENT);
            NODE* condNode = initNode(G_SV_COND_PREDICATE);
            condNode -> sub = node -> sub -> sub;
            returnNode -> sub = condNode;
            NODE* trueNode = initNode(G_SV_STATEMENT_OR_NULL);
            trueNode -> sub = trueSubNode;
            returnNode -> sub -> next = trueNode;
            NODE* falseNode = initNode(G_SV_STATEMENT_OR_NULL);
            falseNode -> sub = falseSubNode;
            returnNode -> sub -> next -> next = falseNode;
         }
      }
   } else
   if (node -> id == G_SV_LOOP_WHILE_STATEMENT) 	{
      printf("ERR.LOGIC_CONE_EXTRACT.WHILE_LOOP_NOT_SUPPORTED.\n");
      string tmpOut = "";
      writer_sv_loop_while_statement(tmpOut, node -> sub);
      prettyPrint(tmpOut);
      printf("%s\n", tmpOut.c_str());
      exit(-1);
   } else
   if (node -> id == G_SV_LOOP_DO_STATEMENT) 	{
      printf("ERR.LOGIC_CONE_EXTRACT.DO_LOOP_NOT_SUPPORTED.\n");
      string tmpOut = "";
      writer_sv_loop_do_statement(tmpOut, node -> sub);
      prettyPrint(tmpOut);
      printf("%s\n", tmpOut.c_str());
      exit(-1);
   } else
   if (	(node -> id == G_SV_LOOP_REPEAT_STATEMENT) 	|
   		(node -> id == G_SV_LOOP_FOREACH_STATEMENT) 	|
   		(node -> id == G_SV_LOOP_FOR_STATEMENT) 	) {
      if (node -> sub != NULL) {
         NODE* tmpNode = node -> sub;
         NODE* lastNode = tmpNode;
         while (true) {
            if (tmpNode -> next == NULL) {
               lastNode = tmpNode;
               break;
            }
            tmpNode = tmpNode -> next;
         }
         NODE* subNode = extractTreeLHS(name, NULL, tmpNode -> sub);
         if (subNode != NULL) 
         if (node -> id == G_SV_LOOP_FOREACH_STATEMENT) {
            returnNode = initNode(G_SV_LOOP_FOREACH_STATEMENT);
            NODE* arrayIdentifierNode = initNode(G_SV_PS_OR_HIERARCHICAL_ARRAY_IDENTIFIER);
            arrayIdentifierNode -> sub = node -> sub -> sub;
            returnNode -> sub = arrayIdentifierNode;
            NODE* loopVariablesNode = initNode(G_SV_LOOP_VARIABLES);
            loopVariablesNode -> sub = node -> sub -> next -> sub;
            returnNode -> sub -> next = loopVariablesNode;
            NODE* statementNode = initNode(G_SV_STATEMENT_OR_NULL);
            statementNode -> sub = subNode;
            returnNode -> sub -> next -> next = statementNode;
         } else
         if (node -> id == G_SV_LOOP_REPEAT_STATEMENT) {
            returnNode = initNode(G_SV_LOOP_REPEAT_STATEMENT);
            NODE* expNode = initNode(G_SV_EXPRESSION);
            expNode -> sub = node -> sub -> sub;
            returnNode -> sub = expNode;
            NODE* statementNode = initNode(G_SV_STATEMENT_OR_NULL);
            statementNode -> sub = subNode;
            returnNode -> sub -> next = statementNode;
         } else {
            returnNode = initNode(G_SV_LOOP_FOR_STATEMENT);
            NODE* forInitNode = initNode(G_SV_FOR_INITIALIZATION);
            forInitNode -> sub = node -> sub -> sub;
            returnNode -> sub = forInitNode;
            NODE* exprNode = initNode(G_SV_EXPRESSION);
            exprNode -> sub = node -> sub -> next -> sub;
            returnNode -> sub -> next = exprNode;
            NODE* stepNode = initNode(G_SV_FOR_STEP);
            stepNode -> sub = node -> sub -> next -> next -> sub;
            returnNode -> sub -> next -> next = stepNode;
            NODE* statementNode = initNode(G_SV_STATEMENT_OR_NULL);
            statementNode -> sub = subNode;
            returnNode -> sub -> next -> next -> next = statementNode;
            if (debug) {
               printf("--------------------------------\n");
               printTree(returnNode);
               printf("--------------------------------\n");
            }
         }
      }
   } else
   if (node -> sub != NULL) {
      NODE* subNode = extractTreeLHS(name, NULL, node -> sub);
      if (subNode != NULL) {
         returnNode = initNode(node -> id);
         returnNode -> sub = subNode;
      }
   }
   if (node -> next != NULL) {
      NODE* subNode = extractTreeLHS(name, NULL, node -> next);
      if (returnNode == NULL)
         returnNode = subNode;
      else
         returnNode -> next = subNode;
   }
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Returns the first LIST_ENTRY NODE below the NODE with the given id.
/// If NODE with id does not exist on this level, then it is inserted.
/////////////////////////////////////////////////////////////////////////////////
NODE* getConstructListFirstNode (NODE* referenceModuleNode, 
                                 unsigned dbID) {
   if (referenceModuleNode -> id == dbID) {
      if (referenceModuleNode -> sub -> id == DB_LIST_ENTRY) 
         return referenceModuleNode -> sub;
      NODE* returnNode = initNode(DB_LIST_ENTRY);
      referenceModuleNode -> sub = returnNode;
      return returnNode;
   }
   if (referenceModuleNode -> next != NULL) 
      return getConstructListFirstNode(referenceModuleNode -> next, dbID); 
   NODE* dbIDNode = initNode(dbID);
   referenceModuleNode -> next = dbIDNode;
   NODE* returnNode = initNode(DB_LIST_ENTRY);
   dbIDNode -> sub = returnNode;
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Inserts LIST_ENTRY NODE below NODE with given id.
/// If NODE with given id does not exist on the this level, 
/// then an additional NODE is inserted as well.
/// Retruns the inserterd LIST_ENTRY NODE.
/////////////////////////////////////////////////////////////////////////////////
NODE* insertConstructListNode (NODE* referenceModuleNode, 
                               unsigned dbID) {
   if (referenceModuleNode -> id == dbID) {
      NODE* returnNode = initNode(DB_LIST_ENTRY);
      if (referenceModuleNode -> sub != NULL)
         returnNode -> next = referenceModuleNode -> sub;
      referenceModuleNode -> sub = returnNode;
      return returnNode;
   }
   if (referenceModuleNode -> next != NULL) 
      return insertConstructListNode(referenceModuleNode -> next, dbID); 
   NODE* dbIDNode = initNode(dbID);
   referenceModuleNode -> next = dbIDNode;
   NODE* returnNode = initNode(DB_LIST_ENTRY);
   dbIDNode -> sub = returnNode;
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Return all RHS entries from a given conde.
/////////////////////////////////////////////////////////////////////////////////
NODE* getRHSTree (bool postAssignment, 
                  NODE* node, 
                  NODE* rhsTree) {
   bool debug = false;
   if (	(node -> id == G_SV_VARIABLE_ASSIGNMENT) 	|
  		(node -> id == G_SV_NONBLOCKING_ASSIGNMENT) 	|
  		(node -> id == G_SV_BLOCKING_ASSIGNMENT) 	) {
      if (node -> sub != NULL)
      if (node -> sub -> sub != NULL) {
         NODE* selectNode = getNode(node -> sub -> sub, G_SV_SELECT);
         if (selectNode != NULL)
            getRHSTree(true, selectNode, rhsTree);
      }
      if (node -> sub != NULL)
      if (node -> sub -> next != NULL) 
         return getRHSTree(true, node -> sub -> next, rhsTree);
      return node; 
   } else               
   if (	(node -> id == G_SV_GENVAR_IDENTIFIER)					|
  		(node -> id == G_SI) 								|
  		(node -> id == G_PDVL_EVENT_IDENTIFIER_BY_NAME) 			|
  		(node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) 			|
  		(node -> id == G_PDVL_DATA_IDENTIFIER_BY_NAME) 			|
  		(node -> id == G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_THEOREM_IDENTIFIER_BY_NAME) 	) {
      string rhsString = getSI(node);
      if (postAssignment) {
         if (debug) printTree(0, node);
         addSITree(node, NULL, rhsTree);
      }
      if (node -> next != NULL) return getRHSTree(postAssignment, node -> next, rhsTree);
   } else               
   if (	(node -> id == G_SV_NUMBER) 			) {
   } else                
   if (	(node -> id == G_SV_CASE_EXPRESSION) 			) {
      if (node -> sub != NULL) getRHSTree(true, node -> sub, rhsTree);
      if (node -> next != NULL) return getRHSTree(postAssignment, node -> next, rhsTree);
   } else                
   if (	(node -> id == G_PDVL_TRANSACTION_AT_STATEMENT) 	) {
      if (node -> sub != NULL) return getRHSTree(postAssignment, node -> sub, rhsTree);
   } else                
   if (	(node -> id == G_SV_COND_PREDICATE)            |
        (node -> id == G_SV_PROCEDURAL_TIMING_CONTROL) ) {
      if (node -> sub != NULL) /* return */ getRHSTree(true, node -> sub, rhsTree);
      if (node -> next != NULL) return getRHSTree(postAssignment, node -> next, rhsTree);
   } else                
   if (	(node -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) 	) {
      if (debug) printTree(0, node);
      addSITree(node, NULL, rhsTree);
      if (node -> sub -> next != NULL) {
         return getRHSTree(postAssignment, node -> sub -> next, rhsTree);
      }
   } else                
   if (	(node -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) 	) {
      if (debug) printTree(0, node);
      addSITree(node, NULL, rhsTree);
      if (node -> sub -> next != NULL) {
         getRHSTree(postAssignment, node -> sub -> next, rhsTree);
      }
      if (node -> sub -> next -> next != NULL) {
         getRHSTree(postAssignment, node -> sub -> next -> next, rhsTree);
      }
   } else                
   if (	(node -> id == G_SV_VARIABLE_LVALUE) 	) {
      if (debug) printTree(0, node);
      addSITree(node, NULL, rhsTree);
      if (node -> sub -> next != NULL) {
         return getRHSTree(postAssignment, node -> sub -> next, rhsTree);
      }
   } else {                
      if (node -> sub != NULL) /* return */ getRHSTree(postAssignment, node -> sub, rhsTree);
      if (node -> next != NULL) return getRHSTree(postAssignment, node -> next, rhsTree);
   } 
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
//	Pretty print CPP output
/////////////////////////////////////////////////////////////////////////////////
void prettyPrintCPP (string &out)
{
   bool returned = true;
   bool returnAfterClosing = false;
   unsigned tab = 0;
   unsigned brakets_level = 0;
   unsigned comm_level = 0;
   for (unsigned i = 0; i < out.length(); i++) {                              
        char c = out.at(i);
        if ( (out.find("\ncase (", i - 1) == i - 1) |
             (out.find("\nunique case (", i - 1) == i - 1) |
             (out.find("\nunique0 case (", i - 1) == i - 1) |
             (out.find("\npriority case (", i - 1) == i - 1) ) {
           returnAfterClosing = true;
        }
        if (	(c == '{')			&
        		(comm_level == 0)	&
        		(brakets_level == 0)) {
           out.insert(i + 1,1,'\n');
           tab += 1;
        } else 
        if (	(c == '}')			&
        		(comm_level == 0)	&
        		(brakets_level == 0)) {
           tab -= 1;
           if (returned) {
              if (tab > 0) {
                 for (unsigned n = 0; n < tab; n++) {
                    out.insert(i,3,' '); }
                 i += tab * 3; }
              returned = false; }                    
           if (	(out.find("}", i + 1) != i + 2)	&
                (out.find(";", i + 1) != i + 2) )
              out.insert(i + 1,1,'\n');
           else 
           if ( (tab == 0) &
                (out.find(";", i + 1) != i + 2) )         
              out.insert(i + 1,1,'\n');
        } else
        if (	(c == '/')			&
        		(comm_level == 0)	) {        
            i++;
            c = out.at(i);
            if (c == '*') comm_level ++; 
        } else
        if (	(c == '*')			&
        		(comm_level == 1)	) {        
            i++;
            c = out.at(i);
            if (c == '/') comm_level --;
        } else 
        if (	(c == ';')		&
        		(comm_level == 0)	)
        {
           if (out.find("}", i) != i + 2)
              out.insert(i + 1,1,'\n');
        } else 
        if (c == '(')
        {
           brakets_level += 1;
        } else 
        if (c == ')')
        {
           if (brakets_level > 0)
           	  brakets_level -= 1;
           if (returnAfterClosing)
           if (brakets_level == 0)
           {
              out.insert(i + 1,1,'\n');
              returnAfterClosing = false;
           }
        } else 
        if (c == '\n') {             
           returned = true;
        } else if (returned) {             
           if (c == ' ') {
              out.erase(i,1);
              i -= 1;             
           } else {
              if (	(c == 'e')			&
             		(comm_level == 0)	&
             		(brakets_level == 0)) {
                 if (out.find("\nend ", i - 1) == i - 1) {
                    tab -= 1;
                    out.insert(i + 3,1,'\n');
                    for (unsigned n = 0; n < tab; n++)
                       out.insert(i,3,' ');
                    i += 3 * tab + 2;
                 } else 
                 if (out.find("endcase ", i) == i) {
                    out.insert(i + 7,1,'\n');
                    for (unsigned n = 0; n < tab; n++)
                       out.insert(i,3,' ');
                    i += 3 * tab + 6;
                 } else {
                    for (unsigned n = 0; n < tab; n++)
                       out.insert(i,3,' ');
                    i += 3 * tab; 
                    returned = false; }
              } else {
                 for (unsigned n = 0; n < tab; n++)
                    out.insert(i,3,' ');
                 returned = false; } } } }
    size_t pos; 
    while ((pos = out.find(" . ")) != std::string::npos) {
        out.replace(pos, 3, ".");
    } 
    while ((pos = out.find(" , ")) != std::string::npos) {
        out.replace(pos, 3, ", ");
    } 
    size_t pos0x = out.find("0x ");
    while (pos0x != std::string::npos) {
       pos0x += 1;
       size_t posS = out.find(" ", pos0x);
       size_t posU = out.find("U", pos0x);
       while (posU > posS) {
          out.replace(posS, 1, "");
          posS = out.find(" ", pos0x);
          posU = out.find("U", pos0x);
       }
       pos0x = out.find("0x ", pos0x);
    }
}
/////////////////////////////////////////////////////////////////////////////////
//	Pretty print Gallina output
/////////////////////////////////////////////////////////////////////////////////
void prettyPrintGA (string &out)
{
   unsigned tab = 0;
   unsigned withinMatch = 0;
   bool postDefinition = false;
   for (unsigned i = 0; i < out.length(); i++) {                              
      char c = out.at(i);
      if (c == '.') {            
         if (i + 1 < out.length())
            out.replace(i+1,1,"\n");
         i = i + 1; 
         tab = 0;
         postDefinition = false;
         withinMatch = 0;
      } else
      if (c == ':') {
         c = out.at(i + 1);
         if (c == '=') {            
            c = out.at(i + 3);
            if (1) { //c == '|') {            
               out.insert(i + 3,1,'\n');
               out.insert(i + 4,1,' ');
               out.insert(i + 4,1,' ');
               out.insert(i + 4,1,' ');
               i += 7;
               tab = 1;
               postDefinition = true;
            }
         }
      } else
      if (c == '|') {
         out.insert(i,1,'\n');
         for (int n = 0; n < tab; n++) {
           out.insert(i + 1,1,' ');
           out.insert(i + 1,1,' ');
           out.insert(i + 1,1,' ');
         }
         i += 1 + (3 * tab);
      } else
      if ( (c == 'f')         &
           (postDefinition)   &
           (withinMatch == 0) ) {
         if ( (out.find("f_", i) == i) ) { 
            out.insert(i,1,'\n');
            tab = 1;
            for (int n = 0; n < tab; n++) {
              out.insert(i + 1,1,' ');
              out.insert(i + 1,1,' ');
              out.insert(i + 1,1,' ');
            }
            i += 4 + (3 * tab);
         }
      } else
      if (c == 'm') {
         if ( (out.find("match ", i) == i) ) { 
            out.insert(i,1,'\n');
            tab += 1;
            for (int n = 0; n < tab; n++) {
              out.insert(i + 1,1,' ');
              out.insert(i + 1,1,' ');
              out.insert(i + 1,1,' ');
            }
            i += 4 + (3 * tab);
            withinMatch += 1;
         }
      } else
      if (c == 'e') {
         if ( (out.find("end ", i) == i) ) { 
            out.insert(i,1,'\n');
            for (int n = 0; n < tab; n++) {
              out.insert(i + 1,1,' ');
              out.insert(i + 1,1,' ');
              out.insert(i + 1,1,' ');
            }
            i += 4 + (3 * tab);
            tab -= 1;
            withinMatch -= 1;
         }
      }
   }
}
/////////////////////////////////////////////////////////////////////////////////
//	Pretty print output
/////////////////////////////////////////////////////////////////////////////////
void prettyPrint (string &out)
{
   bool returned = true;  
   bool returnAfterClosing = false;
   bool returnAfterComma = false;
   bool returnAfterOpening = false;
   unsigned tab = 0;
   unsigned brakets_level = 0;
   unsigned comm_level = 0;
   unsigned structUnionLevel = 0;
   for (unsigned i = 0; i < out.length(); i++) {                              
        char c = out.at(i);
        if (c == 'c') {            
           if ( (out.find("\ncase (", i - 1) == i - 1) )
              returnAfterClosing = true;
        } else
        if (c == 'u') {
           if ( (out.find("\nunique case (", i - 1) == i - 1) |
                (out.find("\nunique0 case (", i - 1) == i - 1) )
              returnAfterClosing = true;
           else
           if (out.substr(i - 1, 7) == " union ")
              structUnionLevel += 1;
           if (out.substr(i - 1, 7) == "\nunion ")
              structUnionLevel += 1;
        } else
        if (c == 'p') {
           if ( (out.find("\npriority case (", i - 1) == i - 1) )
              returnAfterClosing = true;
        } else
        if (c == 's') {
           if (out.substr(i - 1, 8) == " struct ")
              structUnionLevel += 1;
           if (out.substr(i - 1, 8) == "\nstruct ")
              structUnionLevel += 1;
        } else
        if (c == 'm') {
           if ( (out.find("module ", i) == i) ) {
              returnAfterComma = true;
              returnAfterOpening = true;
           }
        }
        // no else here
        if (	(c == 'b')			&
        		(comm_level == 0)	&
        		(brakets_level == 0)) {
           if ( (out.find(" begin ", i - 1) == i - 1)  |
                (out.find("\nbegin ", i - 1) == i - 1) ) {
              out.insert(i + 5,1,'\n');
              tab += 1;
              i += 4;
           } else
           if (returned) {             
              for (unsigned n = 0; n < tab; n++)
                 out.insert(i,3,' ');
              i += 3 * tab;
              returned = false; 
           }
        /////////////////////////////////////
        // curly brackets
        } else 
        if (	(c == '{')			    &
        		(structUnionLevel > 0)) {
           out.insert(i + 1,1,'\n');
           tab += 1;
        } else 
        if (	(c == '}')			&
        		(structUnionLevel > 0)) {
           i = out.find(";", i);
           out.insert(i + 1,1,'\n');
           structUnionLevel -= 1;
           tab -= 1;
           //i++;
        /////////////////////////////////////
        } else
        if (	(c == '/')			&
        		(comm_level == 0)	) {        
            i++;
            c = out.at(i);
            if (c == '*') comm_level ++; 
        } else
        if (	(c == '*')			&
        		(comm_level == 1)	) {        
            i++;
            c = out.at(i);
            if (c == '/') comm_level --;
        } else 
        if (	(c == ',')			&
        		(returnAfterComma)	) {        
           out.insert(i + 1,1,'\n');
        } else 
        if (	(c == ';')		&
        		(brakets_level == 0) &
        		(comm_level == 0)	)
        {
           if (out.find("}", i) != i + 2)
              out.insert(i + 1,1,'\n');
           if (returned) {
              for (unsigned n = 0; n < tab; n++)
                 out.insert(i,3,' ');
              i += 3 * tab;
              returned = false; 
           }
           if (returnAfterComma) {
              tab -= 1;
              returnAfterComma = false;
           }
        } else 
        if (c == '(')
        {
           brakets_level += 1;
           if (returnAfterOpening) {
              if (out.find(")", i) == i + 1) {
                 returnAfterComma = false;
              } else {
                 out.insert(i + 1,1,'\n');
                 tab += 1;
              }
              returnAfterOpening = false;
           }
        } else 
        if (c == ')')
        {
           if (brakets_level > 0)
           	  brakets_level -= 1;
           if (returnAfterClosing)
           if (brakets_level == 0)
           {
              out.insert(i + 1,1,'\n');
              returnAfterClosing = false;
           }
           
        } else 
        if (c == '\n') {             
           returned = true;
        } else 
        if (returned) {             
           if (c == ' ') {
              out.erase(i,1);
              i -= 1;             
           } else {
              if (	(c == 'e')			&
             		(comm_level == 0)	&
             		(brakets_level == 0)) {
                 if (out.find("\nend ", i - 1) == i - 1) {
                    if (tab > 0)
                       tab -= 1;
                    out.insert(i + 3,1,'\n');
                    for (unsigned n = 0; n < tab; n++)
                       out.insert(i,3,' ');
                    i += 3 * tab + 2;
                 } else 
                 if (out.find("endfunction", i) == i) {
                    out.insert(i + 11,1,'\n');
                    for (unsigned n = 0; n < tab; n++)
                       out.insert(i,3,' ');
                    i += 3 * tab + 10;
                 } else 
                 if (out.find("endcase ", i) == i) {
                    out.insert(i + 7,1,'\n');
                    for (unsigned n = 0; n < tab; n++)
                       out.insert(i,3,' ');
                    i += 3 * tab + 6;
                 } else {
                    for (unsigned n = 0; n < tab; n++)
                       out.insert(i,3,' ');
                    i += 3 * tab; 
                    returned = false; 
                 }
              } else {
                 for (unsigned n = 0; n < tab; n++)
                    out.insert(i,3,' ');
                 i += 3 * tab;
                 returned = false; } } } }
   for (unsigned i = 0; i < out.length(); i++) {                              
      if (out.at(i) == ' ') {
         if (i + 1 < out.length()) {
            if ( (out.at(i + 1) == '.') ) {
               if (i + 2 < out.length()) {
                  if (out.at(i + 2) == ' ') {
                     out.replace(i, 1, "");
                     out.replace(i + 1, 1, "");
                  }
               }
            } else
            if ( (out.at(i + 1) == ',') |
                 (out.at(i + 1) == ';') |
                 (out.at(i + 1) == ')') |
                 (out.at(i + 1) == ']') |
                 (out.at(i + 1) == '}') ) {
                     out.replace(i, 1, "");
            } else
            if ( (out.at(i + 1) == ':') ) {
               if (i + 2 < out.length()) {
                  if (out.at(i + 2) == ':') {
                     if (i + 3 < out.length()) {
                        if (out.at(i + 3) == ' ') {
                           out.replace(i, 1, "");
                           out.replace(i + 2, 1, "");
                        }
                     }
                  }
               }
            }
         }
      } else
      if ( (out.at(i) == '(') |
           (out.at(i) == '[') |
           (out.at(i) == '{') |
           (out.at(i) == '!') |
           (out.at(i) == '~') ) {
         if (i + 1 < out.length()) {
            if ( (out.at(i + 1) == ' ') ) {
               out.replace(i + 1, 1, "");
            }
         }
      }
   }
}
/////////////////////////////////////////////////////////////////////////////////
///	Read a PDVL file
/////////////////////////////////////////////////////////////////////////////////
void readPDVL (string &out, bool pdvl)
{         
   bool debug = false;
   char c;  
   bool commentLine = false;
   bool commentString = false;
   unsigned commentStringLevel = 0;
   bool outsidePDVL = pdvl;
   while (1) {
      c = getc(app);
      if (c == -1) {
         out.append(1u, c);
         break; }
      if (   (c == '\n') |
             (c == 10)   |
             (c == 13)   ) {                  
         commentLine = false;
         if (debug) 
            if (   (c == '\n') |
                   (c == 10)   )
               if (!commentString)
                  if (!outsidePDVL)
                     printf("\n");
         out.append(1u, ' ');
      } else
      if (c == '\t') {                  
         out.append(1u, ' ');
      } else
      if (   (c == '/')   		&
             (!outsidePDVL)     &
             (!commentLine)    	) { 
         char cc = getc(app);
         if (cc == -1) {
            out.append(1u, cc);
            break; }
         if (cc == '/') {  
            commentLine = true;
            out.append(1u, ' ');
            out.append(1u, ' ');
         } else
         if (cc == '*') {  
            commentString = true;
            commentStringLevel += 1;
            out.append(1u, ' ');
            out.append(1u, ' ');
         } else {  
            out.append(1u, c);
            if (   (cc == '\n') |
                   (cc == '\t') |
                   (cc == 10)   |
                   (cc == 13)   )
               out.append(1u, ' ');
            else
               out.append(1u, cc);
         }
      } else
      if (   (c == '*')   	&
             (!outsidePDVL) )
      { 
         char cc = getc(app);
         if (cc == -1) {
            out.append(1u, c);
            out.append(1u, cc);
            break;
         } else
         if (cc == '/') {
            if (commentStringLevel > 0)
               commentStringLevel -= 1;
            if (commentStringLevel == 0)  
               commentString = false;
            out.append(1u, ' ');
            out.append(1u, ' ');
         } else
      	 if (commentLine | commentString | outsidePDVL) {
            out.append(1u, ' ');
            if (   (cc == '\n') |
                   (cc == 10)   |
                   (cc == 13)   )
              commentLine = false;
            out.append(1u, ' ');
      	 } else {  
            out.append(1u, c);
            if (   (cc == '\n') |
                   (cc == '\t') |
                   (cc == 10)   |
                   (cc == 13)   )
               out.append(1u, ' ');
            else
               out.append(1u, cc);
         }
      } else
      if (   (c == '<')   	&
             (outsidePDVL) 	) { 
         char cc = getc(app);
         if (cc == -1) {
            out.append(1u, cc);
            break; }
         if (   (cc == '\"')   ) {
            outsidePDVL = false;
            out.append(1u, c);
            out.append(1u, cc);
         } else {
            out.append(1u, ' ');
            out.append(1u, ' ');
         }
      } else
      if (   (c == '\"')	  &
             (pdvl)			  &
             (!commentLine)   &
             (!commentString) &
             (!outsidePDVL)	  ) { 
         out.append(1u, c);
         char cc = getc(app);
         if (cc == -1) {
            out.append(1u, cc);
            break; }
         if (   (cc == '>')   )
            outsidePDVL = true;
         if (   (cc == '\n') |
                (cc == '\t') |
                (cc == 10)   |
                (cc == 13)   )
            out.append(1u, ' ');
         else
            out.append(1u, cc);
      } else { 
      	 if (commentLine | commentString | outsidePDVL) {
            out.append(1u, ' ');
      	    if (debug) printf(" ");
      	 } else {
            out.append(1u, c);
      	    if (debug) printf("%c", c); 
      	 }
      } 
   }
}

/////////////////////////////////////////////////////////////////////////////////
/// printError
/////////////////////////////////////////////////////////////////////////////////
void printError ()
{
   rewind(app); 
   int preLine = 5;
   int line = 1;
   if (maxPtr > 0)
   for (int n = 0; n <= maxPtr; n++)  {
       char c = getc(app);
       if (   (c == '\n') |
              (c == 10)   )
       line ++; }    
   fprintf(stdout, "Error in line %d\n", line);
   if (line < preLine)       
      fprintf(stdout, "%d:\t", line);
   rewind(app); 
   int line2 = 1;
   int line2Offset = 0;
   for (int n = 0; n <= maxPtr; n++) {
       char c = getc(app);
       if (line2 + preLine > line)
       if (c == '\t')
          fprintf(stdout, " "); // compromise
       else
          fprintf(stdout, "%c", c);
       if (   (c == '\n') |
              (c == 10)   ) {
          line2 ++;
          line2Offset = n + 1;
          if (line2 + preLine > line)
             fprintf(stdout, "%d:\t", line2); } }           
   fprintf(stdout, "\n\t");
   for (int n = line2Offset; n < maxPtr; n++) {
      fprintf(stdout, "-"); }
   fprintf(stdout, "|\n%d:\t", line2);
   for (int n = line2Offset; n <= maxPtr; n++) {
      fprintf(stdout, " "); }
   while (1) {
       char c = getc(app);
       fprintf(stdout, "%c", c);
       if (   (c == -1) |
              (c == '\n') |
              (c == 13)   ) {
          break; } }
   fprintf(stdout, "\n");
}
/////////////////////////////////////////////////////////////////////////////////
/// Report unfinished command
/////////////////////////////////////////////////////////////////////////////////
bool reportUnfinishedCommands (NODE* node) {
   bool debug = false;
   bool returnBool = false;
   NODE* clusterNode = dbNode -> sub;
   while (true) {
      if (debug) printf("cont 0\n");
      if (node -> sub != NULL) {
         if (debug) printf("reportUnfinishedCommands, id: %d\n", node -> sub -> id);
         if (node -> sub -> id != 0) {
            if (reportUnfinishedCommands(node -> sub))
               returnBool = true;
         } else
         if (node -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub != NULL) 
         if (node -> sub -> sub -> sub -> sub != NULL) {
            NODE* buildNode = node -> sub -> sub -> sub -> sub;
            if (debug) printTree(5, buildNode);
            if (buildNode -> id == DB_MODULE_BUILDS)
            if (buildNode -> sub != NULL) 
            if (buildNode -> sub -> next != NULL) {
               if (debug) printf("-----------------------------------\n");
               if (debug) printTree(5, buildNode);
               NODE* tmpSubNode = buildNode -> sub -> next;
               bool found = false;
               if (debug) printf("-----------------------------------\n");
               if (debug) printTree(5, tmpSubNode);
               if (tmpSubNode != NULL)
               while (true) {
                  NODE* paramNode = getNode(tmpSubNode -> sub, G_SV_PARAMETER_DECLARATION);
                  if (paramNode == NULL) {
                     found = true;
                     break;
                  }
                  if (tmpSubNode -> next == NULL)
                     break;
                  tmpSubNode = tmpSubNode -> next;
               }
               if (found) {
                  printf("\nMRPHS wasn't able to execute the following command(s):\n\n");
                  string tmpOut = "";
                  writer_pdvl_build_command(tmpOut, buildNode -> sub);
                  prettyPrintCPP(tmpOut);
                  printf("%s\n", tmpOut.c_str());
                  returnBool = true;
               }
            }
         } 
         if (debug) printf("cont 1\n");
         if (node -> sub != NULL)
         if (node -> sub -> next != NULL)
         if (reportUnfinishedCommands(node -> sub -> next))
            returnBool = true;
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
   return returnBool;
}
