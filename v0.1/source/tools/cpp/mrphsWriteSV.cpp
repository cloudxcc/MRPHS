//
// Copyright 2024 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

#include <mrphsWriteSV.h>

/////////////////////////////////////////////////////////////////////////////////
/// Write SystemVerilog sub-module
/////////////////////////////////////////////////////////////////////////////////
string writeSubModule (string &header, 
                       NODE* dbSubModuleNode, 
                       bool trueModuleFalseInstance) {
   bool debug = false;
   if (debug) printf("writeSubModule: %d\n", dbSubModuleNode -> id);
   string returnString = "";
   while (true) {
      if (dbSubModuleNode -> id == 0)
      {
         if (trueModuleFalseInstance) {
            if (debug) printf("found first 0.\n");
            string thisHeader = "";
            returnString.append(writeSubModule(thisHeader, dbSubModuleNode -> sub, !trueModuleFalseInstance));
         } else {
            if (debug) printf("found second 0.\n");
            if (debug) printf("instantiation: %s\n", header.c_str()); 
            if (debug) printTree(dbSubModuleNode);
            NODE* dbNamedPortsNode = NULL;
            NODE* dbPrintNode = NULL;
            if (dbSubModuleNode -> sub != NULL)
            if (dbSubModuleNode -> sub -> sub != NULL) {
               NODE* moduleNode = dbSubModuleNode -> sub;
               NODE* dbEntryNode = moduleNode -> sub;
               while (true) {
                  if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
                  if (dbEntryNode -> id == DB_NAMED_PORTS)
                     dbNamedPortsNode = dbEntryNode;
                  if (dbEntryNode -> id == DB_PRINT)
                     dbPrintNode = dbEntryNode;
                  if (dbEntryNode -> next == NULL)
                     break;
                  dbEntryNode = dbEntryNode -> next;
               }
            } 
            if (dbPrintNode == NULL)
               return "";
            string thisModuleName = getSI(dbPrintNode -> sub);
            returnString.append(thisModuleName);
            returnString.append(" ");
            returnString.append(header);
            returnString.append(" (");
            if (dbNamedPortsNode != NULL) 
            if (dbNamedPortsNode -> sub != NULL) {
               if (debug) printf("id: %d\n", dbNamedPortsNode -> sub -> id);
               NODE* tmpNode = dbNamedPortsNode -> sub;
               bool first = true;
               while (true) {
                  if (!first)
                     returnString.append(",");
                  first = false;
                  returnString.append("\n\t.");
                  returnString.append(getSI(tmpNode));
                  returnString.append("(");
                  returnString.append(getSI(tmpNode));
                  returnString.append(") ");
                  if (tmpNode -> next == NULL)
                     break;
                  tmpNode = tmpNode -> next;
               }
            }
            returnString.append("); ");
         }
      } else {
         string thisHeader = "";
         thisHeader.append(header);
         thisHeader.append(node2String(dbSubModuleNode));
         returnString.append(writeSubModule(thisHeader, dbSubModuleNode -> sub, trueModuleFalseInstance));
      }
      if (dbSubModuleNode -> next == NULL)
         break;
      dbSubModuleNode = dbSubModuleNode -> next;
   }
   return returnString;
}
/////////////////////////////////////////////////////////////////////////////////
/// Clean SystemVerilog "always" logic cone
///////////////////////////////////////////////////////////////////////////////// 
NODE* cleanSVConeAlways (NODE* tmpNode) {
   bool debug = false;
   if (tmpNode -> id == G_SV_ALWAYS_KEYWORD)
   if (tmpNode -> sub != NULL)
   if (tmpNode -> sub -> id == G_SV_ALWAYS_COMB_IDENTIFIER)
   if (tmpNode -> next != NULL)
   if (tmpNode -> next -> id == G_SV_STATEMENT) {
      tmpNode = tmpNode -> next;
      if (tmpNode -> next == NULL)
      if (tmpNode -> sub != NULL)
      if (tmpNode -> sub -> id == G_SV_STATEMENT_ITEM) {
         tmpNode = tmpNode -> sub;
         if (tmpNode -> next == NULL)
         if (tmpNode -> sub != NULL)
         if (tmpNode -> sub -> id == G_SV_SEQ_BLOCK) {
            tmpNode = tmpNode -> sub;
            if (tmpNode -> next == NULL)
            if (tmpNode -> sub != NULL)
            if (tmpNode -> sub -> id == G_SV_STATEMENT_OR_NULL) {
               if (debug) printf("---------------------- 1\n");
               if (debug) printTree(tmpNode);
               tmpNode = tmpNode -> sub;
               ////////////////////////////////////////////////////////
               // single statement => assign
               ////////////////////////////////////////////////////////
               if (tmpNode -> next == NULL) {
                  if (tmpNode -> sub != NULL)
                  if (tmpNode -> sub -> id == G_SV_STATEMENT) {
                     tmpNode = tmpNode -> sub;
                     if (tmpNode -> next == NULL)
                     if (tmpNode -> sub != NULL)
                     if (tmpNode -> sub -> id == G_SV_STATEMENT_ITEM) {
                        tmpNode = tmpNode -> sub;
                        if (tmpNode -> next == NULL)
                        if (tmpNode -> sub != NULL)
                        if ( (tmpNode -> sub -> id == G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT)    |
                             (tmpNode -> sub -> id == G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT) ) {
                           tmpNode -> id = G_SV_ASSIGN_LIST_OF_VARIABLE_ASSIGNMENTS;
                           tmpNode -> sub -> id = G_SV_LIST_OF_VARIABLE_ASSIGNMENTS;
                           tmpNode -> sub -> sub -> id = G_SV_VARIABLE_ASSIGNMENT;
                           return tmpNode;
                        }
                     }
                  }
               } else
               ////////////////////////////////////////////////////////
               // dual statement => assign ? : ;
               ////////////////////////////////////////////////////////
               if (tmpNode -> next -> next == NULL) {
                  NODE* nextNode = tmpNode -> next;
                  NODE* variableLvalueNode = NULL;
                  NODE* defaultExpressionNode = NULL;
                  ////////////////////////////////////////////////////////
                  // first statement assignment
                  ////////////////////////////////////////////////////////
                  if (tmpNode -> sub -> id == G_SV_STATEMENT) {
                     tmpNode = tmpNode -> sub;
                     if (tmpNode -> next == NULL)
                     if (tmpNode -> sub != NULL)
                     if (tmpNode -> sub -> id == G_SV_STATEMENT_ITEM) {
                        tmpNode = tmpNode -> sub;
                        if (tmpNode -> next == NULL)
                        if (tmpNode -> sub != NULL)
                        if ( (tmpNode -> sub -> id == G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT)    |
                             (tmpNode -> sub -> id == G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT) ) {
                           if (tmpNode -> sub -> sub == NULL) return NULL;
                           if (tmpNode -> sub -> sub -> sub == NULL) return NULL;
                           variableLvalueNode = tmpNode -> sub -> sub -> sub;
                           if (variableLvalueNode -> next == NULL) return NULL;
                           if (variableLvalueNode -> next -> sub == NULL) return NULL;
                           defaultExpressionNode = variableLvalueNode -> next -> sub;
                        } else
                           return NULL;
                     }
                  }
                  ////////////////////////////////////////////////////////
                  // second statement condition
                  ////////////////////////////////////////////////////////
                  if (nextNode -> sub != NULL)
                  if (nextNode -> sub -> id == G_SV_STATEMENT) {
                     tmpNode = nextNode -> sub;
                     if (tmpNode -> next == NULL)
                     if (tmpNode -> sub != NULL)
                     if (tmpNode -> sub -> id == G_SV_STATEMENT_ITEM) {
                        tmpNode = tmpNode -> sub;
                        if (tmpNode -> next == NULL)
                        if (tmpNode -> sub != NULL)
                        if ( (tmpNode -> sub -> id == G_SV_CONDITIONAL_STATEMENT) ) { 
                           tmpNode = tmpNode -> sub;
                           if (tmpNode -> next == NULL)
                           if (tmpNode -> sub != NULL)
                           if ( (tmpNode -> sub -> id == G_SV_IF_CONDITIONAL_STATEMENT) ) { 
                              if (tmpNode -> sub -> sub == NULL) return NULL;
                              if (tmpNode -> sub -> sub -> sub == NULL) return NULL;
                              ////////////////////////////////////////////////////////
                              // enable mutiple conditions
                              ////////////////////////////////////////////////////////
                              if (debug) printf("---------------------- 2\n");
                              if (debug) printTree(tmpNode);
                              NODE* bracketExpression = getNode(tmpNode, G_SV_BRACKET_EXPRESSION); //tmpNode -> sub -> sub -> sub;
                              string conditionString = "";
                              writer_sv_bracket_expression(conditionString, bracketExpression -> sub);
                              bool multipleConditions = false;
                              while (1) {
                                 if (debug) printf("start id: %d\n", tmpNode -> id);
                                 if (tmpNode -> sub -> sub == NULL) return NULL;
                                 if (tmpNode -> sub -> sub -> next == NULL) return NULL;
                                 tmpNode = tmpNode -> sub -> sub -> next;
                                 if (tmpNode -> sub == NULL) return NULL;
                                 if (tmpNode -> sub -> sub == NULL) return NULL;
                                 if (tmpNode -> sub -> sub -> sub == NULL) return NULL;
                                 tmpNode = tmpNode -> sub -> sub -> sub;
                                 if (tmpNode -> id == G_SV_SEQ_BLOCK) {
                                    tmpNode = tmpNode -> sub -> sub -> sub -> sub;
                                    ////////////////////////////////////////////////////////
                                    // put everything together
                                    ////////////////////////////////////////////////////////
                                    if ( (tmpNode -> id == G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT)    |
                                         (tmpNode -> id == G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT) ) {
                                       if (debug) printf("cleanSVCone always.\n");
                                       if (debug) printTree(10, tmpNode);
                                       string assignString = "assign ";
                                       writer_sv_variable_lvalue(assignString, variableLvalueNode -> sub);
                                       assignString.append(" = ");
                                       if (multipleConditions)
                                          conditionString.append(" )");
                                       assignString.append(conditionString);
                                       string trueString = "";
                                       NODE* trueExpressionNode = getNode(tmpNode -> sub, G_SV_EXPRESSION);
                                       writer_sv_expression(trueString, trueExpressionNode -> sub);
                                       string falseString = "";
                                       writer_sv_expression(falseString, defaultExpressionNode -> sub);
                                       if (	(trueString != " 1'b1")  |
                                            (falseString != " 1'b0") ) {
                                          if (debug) printf("trueString: .%s.\n", trueString.c_str());
                                          if (debug) printf("falseString: .%s.\n", falseString.c_str());
                                          assignString.append(" ? ");
                                          assignString.append(trueString);
                                          assignString.append(" : ");
                                          assignString.append(falseString);
                                       }
                                       assignString.append(" ; ");
                                       if (debug) printf("assignString: %s\n", assignString.c_str());
                                       maxPtr = 0;
                                       NODE* returnNode = initNode(0);
                                       parser_sv_continuous_assign(assignString, 0, returnNode);
                                       return returnNode -> sub;
                                    } else
                                    ////////////////////////////////////////////////////////
                                    // check for next seq_block / condition
                                    ////////////////////////////////////////////////////////
                                    if ( (tmpNode -> id == G_SV_SEQ_BLOCK) ) {
                                       tmpNode = tmpNode -> sub -> sub -> sub -> sub;
                                       if ( (tmpNode -> id == G_SV_CONDITIONAL_STATEMENT) ) {
                                          if (tmpNode -> sub -> id != G_SV_IF_CONDITIONAL_STATEMENT)
                                             return NULL;
                                          if (!multipleConditions) {
                                             conditionString.insert(0, "( ");
                                             multipleConditions = true;
                                          }
                                          if (tmpNode -> sub == NULL) return NULL;
                                          if (tmpNode -> sub -> sub == NULL) return NULL;
                                          if (tmpNode -> sub -> sub -> sub == NULL) return NULL;
                                          NODE* bracketExpression = getNode(tmpNode, G_SV_BRACKET_EXPRESSION); //tmpNode -> sub -> sub -> sub;
                                          conditionString.append(" & ");
                                          writer_sv_bracket_expression(conditionString, bracketExpression -> sub);
                                       } else
                                          return NULL;
                                       if (debug) printf("continue id: %d\n", tmpNode -> id);
                                    } else
                                    ////////////////////////////////////////////////////////
                                    // check for next condition
                                    ////////////////////////////////////////////////////////
                                    if ( (tmpNode -> id == G_SV_CONDITIONAL_STATEMENT) ) {
                                       if (tmpNode -> sub -> id != G_SV_IF_CONDITIONAL_STATEMENT)
                                          return NULL;
                                       if (!multipleConditions) {
                                          conditionString.insert(0, "( ");
                                          multipleConditions = true;
                                       }
                                       if (tmpNode -> sub == NULL) return NULL;
                                       if (tmpNode -> sub -> sub == NULL) return NULL;
                                       if (tmpNode -> sub -> sub -> sub == NULL) return NULL;
                                       NODE* bracketExpression = getNode(tmpNode, G_SV_BRACKET_EXPRESSION); //tmpNode -> sub -> sub -> sub;
                                       conditionString.append(" & ");
                                       writer_sv_bracket_expression(conditionString, bracketExpression -> sub);
                                       if (debug) printf("continue id: %d\n", tmpNode -> id);
                                    } else
                                       return NULL;
                                 } else
                                    return NULL;
                              }
                           }
                        }
                     }
                  }
               }
            } 
         }
      }
   }
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
/// Clean SystemVerilog "unique" logic cone
///////////////////////////////////////////////////////////////////////////////// 
void cleanSVConeUnique (NODE* node) {
   bool debug = false;
   if (node -> id == G_SV_STATEMENT_OR_NULL)
   if (node -> next != NULL)
   if (node -> next -> id == G_SV_STATEMENT_OR_NULL) {
      NODE* ptrNode = node;
      bool allUnique = true;
      while (1) {
         bool isUnique = false;
         if (ptrNode -> sub != NULL)
         if (ptrNode -> sub -> sub != NULL)
         if (ptrNode -> sub -> sub -> sub != NULL)
         if (ptrNode -> sub -> sub -> sub -> sub != NULL)
         if (ptrNode -> sub -> sub -> sub -> sub -> sub != NULL)
         if (ptrNode -> sub -> sub -> sub -> sub -> sub -> sub != NULL)
         if (ptrNode -> sub -> sub -> sub -> sub -> sub -> sub -> id == G_SV_UNIQUE_PRIORITY_UNIQUE) {
            isUnique = true;
         }
         if (!isUnique) {
            allUnique = false;
            break;
         }
         if (ptrNode -> next == NULL) 
            break;
          ptrNode = ptrNode -> next;
      }
      if (allUnique) {
         if (debug) printTree(node);
         ptrNode = node;
         string resultString = "";
         bool init = true;
         while (1) {
            string statementString = "";
            writer_sv_statement_or_null(statementString, ptrNode -> sub);
            if (debug) printf("%s\n", statementString.c_str());
            if (init) {
               resultString = statementString;
               init = false;
            } else {
               statementString.replace(0, 7, " else");
               resultString.append(statementString);
            }
            if (ptrNode -> next == NULL) 
               break;
             ptrNode = ptrNode -> next;
         }
         if (debug) printf("%s\n", resultString.c_str());
         parser_sv_statement_or_null(resultString, 0, node);
         node -> next = NULL;
         if (debug) printTree(node);
      }
   }
   if (node -> sub != NULL)
      cleanSVConeUnique(node -> sub);
   if (node -> next != NULL)
      cleanSVConeUnique(node -> next);
}
/////////////////////////////////////////////////////////////////////////////////
/// Clean SystemVerilog loop index
///////////////////////////////////////////////////////////////////////////////// 
string cleanSVConeLoopIndex (NODE* tmpNode, 
                             NODE* signalTree) { 
   bool debug = false;
   string returnString = "";
   if (tmpNode == NULL) return "";
   ////////////////////////////////////////////////////////
   // handle for loop index uniquification
   ////////////////////////////////////////////////////////
   if (tmpNode -> id == G_SV_LOOP_FOR_STATEMENT) {
      if (tmpNode -> sub -> sub -> id == G_SV_LIST_OF_VARIABLE_ASSIGNMENTS) {
         if (debug) printTree(tmpNode); 
         string initString = "int ";
         writer_sv_for_initialization(initString, tmpNode -> sub -> sub);
         size_t pos = initString.find(", ");
         while (pos != std::string::npos) {
            initString.replace(pos + 1, 0, " int");
            pos = initString.find(", ", pos + 3);
         } 
         if (debug) printf("initString: %s\n", initString.c_str());
         NODE* newNode = initNode(0);
         parser_sv_for_initialization(initString, 0, newNode);
         if (debug) printf("---------------------\n");
         if (debug) printTree(newNode);
         tmpNode -> sub -> sub = newNode -> sub;
      }
   } else
   if (tmpNode -> id == G_SV_LOOP_FOREACH_STATEMENT) {
      NODE* indexVAriableIdentifierNode = getNode(tmpNode -> sub, G_SV_INDEX_VARIABLE_IDENTIFIER);
      if (indexVAriableIdentifierNode != NULL)
      while (1) {
         if (debug) printTree(tmpNode);
         string indexNameString = getSI(indexVAriableIdentifierNode -> sub);
         int i = 0;
         while (1) {
            string indexNewNameString = indexNameString;
            indexNewNameString.append("_");
            indexNewNameString.append(to_string(i));
            indexNewNameString.append(" ");
            NODE* signalNode = initNode(0);
            parser_si(indexNewNameString, 0, signalNode);
            bool found = false;
            if (signalTree -> sub != NULL)
            if (checkSITree(signalNode -> sub, signalTree -> sub)) 
               found = true;
            if (!(found)) {
               if (debug) printTree(signalNode);
               addSITree(signalNode, NULL, signalTree);
               indexNewNameString = indexNameString;
               indexNewNameString.append("_");
               indexNewNameString.append(to_string(i));
               replaceIndexName(tmpNode -> sub, true, indexNameString, indexNewNameString);
               if (debug) printf("---------------------------- new: %s -> %s.\n", indexNameString.c_str(), indexNewNameString.c_str());
               if (debug) printTree(tmpNode);
               returnString.append("integer ");
               returnString.append(indexNewNameString);
               returnString.append(" ; ");
               break;
            }
            i += 1;
         }
         if (indexVAriableIdentifierNode -> next == NULL)
            break;
         indexVAriableIdentifierNode = getNode(indexVAriableIdentifierNode -> next, G_SV_INDEX_VARIABLE_IDENTIFIER);
         if (indexVAriableIdentifierNode == NULL)
            break;
      }
   }
   if (tmpNode -> sub != NULL)
     returnString.append(cleanSVConeLoopIndex(tmpNode -> sub, signalTree)); 
   if (tmpNode -> next != NULL)
     returnString.append(cleanSVConeLoopIndex(tmpNode -> next, signalTree)); 
   return returnString;
}
/////////////////////////////////////////////////////////////////////////////////
/// Add SystemVerilog loop entry
///////////////////////////////////////////////////////////////////////////////// 
string addLoop (string signalName, 
                string loopVar) {
   string returnString = "";
   returnString.append("for (integer ");
   returnString.append(loopVar);
   returnString.append(" = 0; ");
   returnString.append(loopVar);
   returnString.append("  < $size(");
   returnString.append(signalName); 
   returnString.append("); ");
   returnString.append(loopVar);
   returnString.append(" = ");
   returnString.append(loopVar);
   returnString.append("  + 1) begin ");
   return returnString;
}
/////////////////////////////////////////////////////////////////////////////////
/// Insert X assignment in lowest dimension
///////////////////////////////////////////////////////////////////////////////// 
string insertXAssignmentDim (string signalName,
                             NODE* dim0TypeNode,
                             unsigned loopDim,
                             NODE* nextTypeNode,
                             NODE* dbModuleTypesNode) {
   bool debug = false;
   string returnString = "";
   //////////////////////////////////////////
   // Handle multidimensions (array, ...) UNPACKED first
   // nextTypeNode != NULL => multidimensions UNPACKED (array, ...)
   //////////////////////////////////////////
   if (nextTypeNode != NULL) {
      if (debug) printf("--------------------------- nextTypeNode:\n");
      if (debug) printTree(nextTypeNode);
      //////////////////////////////////////////
      // array UNPACKED dimensions
      //////////////////////////////////////////
      if (1) {
         string loopVar = "";
         for (int i = 0; i < loopDim; i++) loopVar.append("i");
         string forString = "";
         forString.append(addLoop(signalName, loopVar));

         string newSignalName = "";
         newSignalName.append(signalName); 
         newSignalName.append("[");
         newSignalName.append(loopVar);
         newSignalName.append("]");

         //////////////////////////////////////////
         // next dim: SV_UNPACKED_DIMENSION
         // no next dim: NULL
         //////////////////////////////////////////
         nextTypeNode = nextTypeNode -> next;
         string subString = "";
         subString.append(insertXAssignmentDim(newSignalName, dim0TypeNode, loopDim + 1, nextTypeNode, dbModuleTypesNode));
         if (subString != "") {
            returnString.append(forString);
            returnString.append(subString);
            returnString.append(" end ");
         }   
         return returnString;   
      }
   } else 
   //////////////////////////////////////////
   // not explicitly defined type => 1'bx
   //////////////////////////////////////////
   if (dim0TypeNode == NULL) {
      returnString.append(signalName); 
      returnString.append(" = 1'bx; "); 
      return returnString;   
   } else
   //////////////////////////////////////////
   // enumeration
   //////////////////////////////////////////
   if ( (dim0TypeNode -> id == G_SV_INTEGER_ENUM_TYPE) |
        (dim0TypeNode -> id == G_PDVL_ENUM_DATA_TYPE)  ) {
      while(!signalName.empty() && std::isspace(*signalName.begin()))
          signalName.erase(signalName.begin());
      if (reportLevel >= 2)
         printf("WARNING.DATAPATH.SET_ENUM_TYPE_SIGNAL_TO_UNDEFINED_NOT_POSSIBLE: %s\n", signalName.c_str());
   } else
   //////////////////////////////////////////
   // struct called from type definition
   //////////////////////////////////////////
   if ( (dim0TypeNode -> id == G_PDVL_STRUCT_OR_UNION_DATA_TYPE) |
        (dim0TypeNode -> id == G_SV_INTEGER_STRUCT_UNION_TYPE)   ) {
      NODE* tmpNode = dim0TypeNode -> sub -> next;
      if (tmpNode -> id == G_SV_PACKED_KEYWORD)
         tmpNode = tmpNode -> next;
      while (1) {
         string structName = getSI(tmpNode -> sub -> next);
         if (debug) printf("structName: %s\n", structName.c_str());
         string newSignalName = " ";
         newSignalName.append(signalName);
         newSignalName.append(".");
         newSignalName.append(structName);
         //////////////////////////////////////////
         // thisDim0TypeNode
         ////////////////////////////////////////// 
         NODE* thisTypeNode = tmpNode -> sub -> sub -> sub;
         // union's subtype
         if (thisTypeNode -> id == G_SV_INTEGER_STRUCT_UNION_TYPE) {
            nextTypeNode = tmpNode -> sub -> next -> next; // UNPACKED
            returnString.append(insertXAssignmentDim(newSignalName, thisTypeNode, loopDim, nextTypeNode, dbModuleTypesNode));
         } else
         // sub type:
         if (thisTypeNode -> id == G_SV_INTEGER_TYPE_IDENTIFIER_TYPE) {
            nextTypeNode = tmpNode -> sub -> next -> next; // UNPACKED
            returnString.append(insertXAssignmentDim(newSignalName, thisTypeNode -> sub, loopDim, nextTypeNode, dbModuleTypesNode));
            if (debug) printf("returnString: %s\n", returnString.c_str());
         } else {
            // struct's subtype
            thisTypeNode = thisTypeNode -> next;
            // undefined type
            if (thisTypeNode == NULL) {
               returnString.append(newSignalName); 
               returnString.append(" = 1'bx; ");
            } else {
               NODE* thisDim0TypeNode = initNode(0);
               thisDim0TypeNode -> sub = thisTypeNode;
               if (debug) printf("--------------------------- thisDim0TypeNode:\n");
               if (debug) printTree(thisDim0TypeNode);
               //////////////////////////////////////////
               // next dim: SV_UNPACKED_DIMENSION
               // no next dim: NULL
               //////////////////////////////////////////
               nextTypeNode = tmpNode -> sub -> next -> next; // UNPACKED
               returnString.append(insertXAssignmentDim(newSignalName, thisDim0TypeNode, loopDim, nextTypeNode, dbModuleTypesNode));
            }
         }
         if (tmpNode -> next == NULL)
            break;
         tmpNode = tmpNode -> next;
      }
      return returnString;
   } else
   //////////////////////////////////////////
   // vetor called from type definition
   //////////////////////////////////////////
   if (dim0TypeNode -> id == G_SV_INTEGER_VECTOR_TYPE) {
      return insertXAssignmentDim(signalName, dim0TypeNode -> next, loopDim, NULL, dbModuleTypesNode);
   } else
   //////////////////////////////////////////
   // packed array type definition
   //////////////////////////////////////////
   if ( (dim0TypeNode -> id == G_SV_PACKED_DIMENSION_LIST)   ) {
      if (debug) printf("--------------------------- dim0TypeNode:\n");
      if (debug) printTree(dim0TypeNode);
      //////////////////////////////////////////
      // upper dim
      //////////////////////////////////////////
      if (dim0TypeNode -> sub -> next != NULL) {
         if (debug) printf("upper dim found:\n");
         string loopVar = "";
         for (int i = 0; i < loopDim; i++) loopVar.append("i");
         string forString = "";
         forString.append(addLoop(signalName, loopVar));

         string newSignalName = "";
         newSignalName.append(signalName); 
         newSignalName.append("[");
         newSignalName.append(loopVar);
         newSignalName.append("]");

         //////////////////////////////////////////
         // next dim: SV_UNPACKED_DIMENSION
         // no next dim: NULL
         //////////////////////////////////////////
         string subString = "";
         subString.append(insertXAssignmentDim(newSignalName, dim0TypeNode -> sub -> next, loopDim + 1, NULL, dbModuleTypesNode));
         if (subString != "") {
            returnString.append(forString);
            returnString.append(subString);
            returnString.append(" end ");
         }   
         return returnString;   
      } else {
      //////////////////////////////////////////
      // lowest dim
      //////////////////////////////////////////
         if (debug) printf("lowest dim found:\n");
         NODE* thisDim0TypeNode = initNode(0);
         thisDim0TypeNode -> sub = dim0TypeNode;
         returnString.append(insertXAssignmentDim(signalName, thisDim0TypeNode, loopDim, nextTypeNode, dbModuleTypesNode));
         return returnString;
      }
   } else 
   //////////////////////////////////////////
   // type definition
   //////////////////////////////////////////
   if ( (dim0TypeNode -> id == G_SV_TYPE_IDENTIFIER)             |
        (dim0TypeNode -> id == G_PDVL_TYPE_IDENTIFIER_DATA_TYPE) ) {
      string typeName = getSI(dim0TypeNode -> sub);
      if (debug) printf("typeName: %s\n", typeName.c_str());
      if (dbModuleTypesNode -> sub != NULL) {
         NODE* tmpNode = dbModuleTypesNode -> sub;
         while (1)  {
            NODE* tmp2Node = tmpNode -> sub;
            while (1) { 
               if (tmp2Node -> id == G_SV_TYPE_DECLARATION) {
                  NODE* thisTypeDefNode = tmp2Node -> sub;
                  NODE* tmpTypeNameNode = thisTypeDefNode -> next;
                  NODE* thisNextTypeNode = thisTypeDefNode -> next -> next; // UNPACKED
                  string tmpTypeName = getSI(tmpTypeNameNode);
                  if (debug) printf("tmpTypeName: %s\n", tmpTypeName.c_str());
                  if (tmpTypeName == typeName) {
                     if (thisTypeDefNode -> id == G_SV_DATA_TYPE) {
                        if (debug) printf("--------------------------- tmp2Node:\n");
                        if (debug) printTree(tmp2Node);
                        if (debug) printf("--------------------------- calling dim0TypeNode:\n");
                        if (debug) printTree(thisTypeDefNode -> sub -> sub);
                        returnString = insertXAssignmentDim(signalName, thisTypeDefNode -> sub -> sub, loopDim, thisNextTypeNode, dbModuleTypesNode);
                        return returnString;
                     }
                  }
               }
               if (tmp2Node -> next == NULL)
                  break;
               tmp2Node = tmp2Node -> next;
            }
            if (tmpNode -> next == NULL)
               break;
            tmpNode = tmpNode -> next;
         }
      }
      return returnString;
   } else {
   //////////////////////////////////////////
   // (final) vector
   //////////////////////////////////////////
      if (debug) printf("--------------------------- dim0TypeNode:\n");
      if (debug) printTree(dim0TypeNode);
      //////////////////////////////////////////
      // upper dim PACKED LIST
      //////////////////////////////////////////
      if (dim0TypeNode -> id == G_PDVL_PACKED_DIMENSION_LIST)
      if (dim0TypeNode -> sub -> next != NULL) {
         if (debug) printf("upper dim found:\n");
         string loopVar = "";
         for (int i = 0; i < loopDim; i++) loopVar.append("i");
         string forString = "";
         forString.append(addLoop(signalName, loopVar));

         string newSignalName = "";
         newSignalName.append(signalName); 
         newSignalName.append("[");
         newSignalName.append(loopVar);
         newSignalName.append("]");

         //////////////////////////////////////////
         // next dim: SV_UNPACKED_DIMENSION
         // no next dim: NULL
         //////////////////////////////////////////
         string subString = "";
         subString.append(insertXAssignmentDim(newSignalName, dim0TypeNode -> sub -> next, loopDim + 1, NULL, dbModuleTypesNode));
         if (subString != "") {
            returnString.append(forString);
            returnString.append(subString);
            returnString.append(" end ");
         }   
         return returnString;   
      }
      //////////////////////////////////////////
      // upper dim UNPACKED LIST
      //////////////////////////////////////////
      if (dim0TypeNode -> id == G_PDVL_UNPACKED_DIMENSION_LIST) {
         if (debug) printf("upper dim found:\n");
         string loopVar = "";
         for (int i = 0; i < loopDim; i++) loopVar.append("i");
         string forString = "";
         forString.append(addLoop(signalName, loopVar));

         string newSignalName = "";
         newSignalName.append(signalName); 
         newSignalName.append("[");
         newSignalName.append(loopVar);
         newSignalName.append("]");

         //////////////////////////////////////////
         // next dim: SV_UNPACKED_DIMENSION
         // no next dim: NULL
         //////////////////////////////////////////
         string subString = "";
         subString.append(insertXAssignmentDim(newSignalName, dim0TypeNode -> sub -> next, loopDim + 1, NULL, dbModuleTypesNode));
         if (subString != "") {
            returnString.append(forString);
            returnString.append(subString);
            returnString.append(" end ");
         }   
         return returnString;   
      }
      NODE* rangeNode = dim0TypeNode -> sub -> sub -> sub;
      string lBitString = "";
      writer_sv_constant_expression(lBitString, rangeNode -> sub -> sub);
      string rBitString = "";
      NODE* exprNode = getNode(rangeNode -> sub -> next, G_SV_CONSTANT_EXPRESSION);
      writer_sv_constant_expression(rBitString, rangeNode -> sub -> next -> sub);
      if (debug) printf("lBitString: .%s.\n", lBitString.c_str());
      //////////////////////////////////////////
      // buswidth defined
      //////////////////////////////////////////
      if ( (is_number(lBitString.substr(1))) &
           (is_number(rBitString.substr(1))) ) {      
         unsigned lB = std::stoul(lBitString.substr(1, lBitString.length()),nullptr,0);
         unsigned rB = std::stoul(rBitString.substr(1, rBitString.length()),nullptr,0);
         unsigned buswidth = std::max(lB, rB) + 1;
         returnString.append(signalName); 
         returnString.append(" = ");
         returnString.append(std::to_string(buswidth));
         returnString.append("'h");
         for (unsigned i = 0; i < (unsigned)(buswidth / 4); i += 1)
            returnString.append("x");
         if ((buswidth % 4) > 0)
            returnString.append("x");
         returnString.append(";");
         return returnString;
      } else {
      //////////////////////////////////////////
      // undefined buswidth
      //////////////////////////////////////////
         string loopVar = "";
         for (int i = 0; i < loopDim; i++) loopVar.append("i");
         returnString.append(addLoop(signalName, loopVar));

         returnString.append(signalName); 
         returnString.append("[");
         returnString.append(loopVar);
         returnString.append("] = 1'bx; ");

         returnString.append("end ");
         return returnString;
      }
   }
   return returnString;
}
/////////////////////////////////////////////////////////////////////////////////
/// Insert X assignment
///////////////////////////////////////////////////////////////////////////////// 
string insertXAssignment (string signalName,
                          NODE* typeNode,
                          NODE* dbModuleTypesNode) {
   bool debug = false;
   string returnString = "";
   //////////////////////////////////////////
   // not explicitly defined type => 1'bx
   //////////////////////////////////////////
   if (typeNode == NULL) {
      returnString.append(signalName); 
      returnString.append(" = 1'bx; ");
   } else {
   //////////////////////////////////////////
   // explicitly defined type
   //////////////////////////////////////////
      if (debug) {
         printf("--------------------------- dbModuleTypesNode:\n");
         if (dbModuleTypesNode != NULL)
         if (dbModuleTypesNode -> sub != NULL)
            printTree(dbModuleTypesNode -> sub);
         printf("--------------------------- typeNode:\n");
         printTree(typeNode -> sub);
      }
      ///////////////////////////////////////////////////////////////////////////////
      // check for inline type definition
      // 					dim0TypeNode					nextTypeNode
      // inline vector:		PDVL_PACKED_DIMENSION_LIST
      // inline array:      PDVL_PACKED_DIMENSION_LIST   	SV_UNPACKED_DIMENSION
      // type:		   		PDVL_TYPE_IDENTIFIER_DATA_TYPE
      ///////////////////////////////////////////////////////////////////////////////
      NODE* dim0TypeNode = typeNode -> sub;
      NODE* nextTypeNode = NULL;
      if (typeNode -> sub -> next != NULL)
         nextTypeNode = typeNode -> sub -> next -> sub;
      returnString.append(insertXAssignmentDim(signalName, dim0TypeNode, 1, nextTypeNode, dbModuleTypesNode));
      if (debug) printf("returnString: %s\n", returnString.c_str());
      return returnString;
   }
   return returnString;
}
/////////////////////////////////////////////////////////////////////////////////
/// Clean SystemVerilog logic cone
///////////////////////////////////////////////////////////////////////////////// 
string cleanSVCone (NODE* coneNode, 
                    bool trueBlockingFalseNonBlocking, 
                    bool insertX,
                    string signalName,
                    NODE* typeNode,
                    NODE* dbModuleTypesNode,
                    NODE* signalTree) {
   bool debug = false;
   if (debug) printTree(12, coneNode);
   string tmpOut = "";
   NODE* listEntryNode = coneNode -> sub;
   unsigned assign = 0;       
   unsigned always = 0;
   while (true) {
      if (debug) printf("listEntryNode -> sub %d\n", listEntryNode -> sub -> id);
      if (listEntryNode -> sub -> id == G_SV_CONTINUOUS_ASSIGN) {
         assign += 1;
         printTree(listEntryNode -> sub);
         printf("assignment. exiting.\n");
         exit(-1);
      } else {
         always += 1;       
      }
      if (listEntryNode -> next == NULL)
         break;
      listEntryNode = listEntryNode -> next;
   }
   if ( (assign > 0) &
        (always > 0) ) {
      printf("multiple assignments and always procedures. exiting.\n");
      exit(-1);
   }
   if ( (assign > 1) ) {
      printf("multiple assignments. exiting.\n");
      exit(-1);
   }
   if (debug) printf("assign %d always %d\n", assign, always);
   listEntryNode = coneNode -> sub;
   //////////////////////////////////////////////////////
   // single assignment
   //////////////////////////////////////////////////////
   if (assign == 1) {
      writer_sv_continuous_assign(tmpOut, listEntryNode -> sub -> sub);        
      tmpOut.append(" ");
      if (debug) printf("Result: %s\n", tmpOut.c_str());
   } else
   //////////////////////////////////////////////////////
   // single always
   //////////////////////////////////////////////////////
   if (always == 1) {
      NODE* tmpNode = cleanSVConeAlways(listEntryNode -> sub -> sub);
      if (tmpNode != NULL) {
         if (debug) printTree(10, tmpNode);
         writer_sv_continuous_assign(tmpOut, tmpNode);        
      } else {
         if (trueBlockingFalseNonBlocking) {
            modifyNode(listEntryNode -> sub -> sub, G_SV_NONBLOCKING_ASSIGN_EXPRESSION, G_SV_BLOCKING_ASSIGN_EXPRESSION);
            modifyNode(listEntryNode -> sub -> sub, G_SV_NONBLOCKING_ASSIGNMENT, G_SV_BLOCKING_ASSIGNMENT);
            modifyNode(listEntryNode -> sub -> sub, G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT, G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT);
         } else
            modifyNode(listEntryNode -> sub -> sub, G_SV_BLOCKING_ASSIGN_EXPRESSION, G_SV_NONBLOCKING_ASSIGN_EXPRESSION);
         NODE* alwaysNode = copyTree(listEntryNode -> sub -> sub);
         string newIntegerString = cleanSVConeLoopIndex(alwaysNode, signalTree);
         tmpOut.append(newIntegerString); 
         if (alwaysNode -> sub -> id == G_SV_ALWAYS_COMB_IDENTIFIER) {
            if (debug) printf("----------------------------- alwaysNode:\n");
            if (debug) printTree(7, alwaysNode);
            string insertXString = insertXAssignment(signalName, typeNode, dbModuleTypesNode);
            if (insertXString != "") {
               string newXAssignString = "begin ";
               newXAssignString.append(insertXString);
               newXAssignString.append("end ");
               NODE* newXAssignNode = initNode(0);
               parser_sv_seq_block(newXAssignString, 0, newXAssignNode); 
               if (debug) printf("newXAssignString: %s\n", newXAssignString.c_str());
               if (debug) printf("----------------------------- newXAssignNode:\n");
               if (debug) printTree(7, newXAssignNode);
               /////////////////////////////////
               // insert new assignment node
               NODE* ptrNode = newXAssignNode -> sub;
               while (ptrNode -> next != NULL) ptrNode = ptrNode -> next;
               ptrNode -> next = alwaysNode -> next -> sub -> sub -> sub;
               alwaysNode -> next -> sub -> sub -> sub = newXAssignNode -> sub;
               string thisOut = "";
               writer_sv_always_construct(thisOut, alwaysNode);
               if (debug) prettyPrint(thisOut);
               if (debug) printf("thisOut:\n%s\n", thisOut.c_str());
            }
         }
         writer_sv_always_construct(tmpOut, alwaysNode);
      }
      tmpOut.append(" ");
      if (debug) printf("Result: %s\n", tmpOut.c_str());
   } else {
   //////////////////////////////////////////////////////
   // merging always
   //////////////////////////////////////////////////////
      if (debug) printf("Start merging always.\n");
      if (debug) printTree(listEntryNode -> sub);
      NODE* alwaysNode = NULL;
      NODE* subSeqBlockNode = NULL;
      while (true) {
         if (trueBlockingFalseNonBlocking) {
            modifyNode(listEntryNode -> sub -> sub, G_SV_NONBLOCKING_ASSIGN_EXPRESSION, G_SV_BLOCKING_ASSIGN_EXPRESSION);
            modifyNode(listEntryNode -> sub -> sub, G_SV_NONBLOCKING_ASSIGNMENT, G_SV_BLOCKING_ASSIGNMENT);
            modifyNode(listEntryNode -> sub -> sub, G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT, G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT);
         } else
            modifyNode(listEntryNode -> sub -> sub, G_SV_BLOCKING_ASSIGN_EXPRESSION, G_SV_NONBLOCKING_ASSIGN_EXPRESSION);
         if (alwaysNode == NULL) {
            alwaysNode = listEntryNode -> sub -> sub;
            subSeqBlockNode = getNode(alwaysNode, G_SV_SEQ_BLOCK) -> sub;
            while (subSeqBlockNode -> next != NULL) 
               subSeqBlockNode = subSeqBlockNode -> next;
         } else {
            NODE* thisSeqBlockNode = getNode(listEntryNode -> sub -> sub, G_SV_SEQ_BLOCK);
            subSeqBlockNode -> next = thisSeqBlockNode -> sub;
            while (subSeqBlockNode -> next != NULL) 
               subSeqBlockNode = subSeqBlockNode -> next;
            if (debug) printTree(alwaysNode);
         }
         if (listEntryNode -> next == NULL)
            break;
         listEntryNode = listEntryNode -> next;
      }
      //////////////////////////////////////////////////////
      // call cleanSVConeAlways with new always node
      //////////////////////////////////////////////////////
      if (debug) printf("Resulting alwaysNode:\n");
      if (debug) printTree(alwaysNode);
      NODE* tmpNode = cleanSVConeAlways(alwaysNode);
      cleanSVConeUnique(alwaysNode);
      if (debug) printf("Resulting alwaysNode:\n");
      if (debug) printTree(alwaysNode);
      if (tmpNode != NULL) {
         if (debug) printTree(10, tmpNode);
         writer_sv_continuous_assign(tmpOut, tmpNode);        
      } else {
         alwaysNode = copyTree(alwaysNode);
         writer_sv_always_construct(tmpOut, alwaysNode);
      }
      tmpOut.append(" ");
   }
   return tmpOut;
}
/////////////////////////////////////////////////////////////////////////////////
/// Check type dependency, 
/// gets individual SV_DATA_TYPE node, 
/// returns false if sub-type not printed yet.
///////////////////////////////////////////////////////////////////////////////// 
bool checkTypeDependency (NODE* dataTypeNode, 
                          NODE* doneSiNode) {
   bool debug = false;
   if (debug) {
      printf("---------------------------- dataTypeNode:\n");
      printTree(4, dataTypeNode);
   }
   if (dataTypeNode -> sub != NULL)
   if (dataTypeNode -> sub -> sub != NULL) {
      NODE* tmpNode = dataTypeNode -> sub -> sub;
      if (debug) printf("---------------------------- tmpNode:\n");
      if (debug) printTree(4, tmpNode);
      if (tmpNode -> id == G_SV_INTEGER_TYPE_IDENTIFIER_TYPE) {
         if (!(checkSITree(tmpNode -> sub -> sub -> sub, doneSiNode -> sub))) {
            if (debug) printf("not found\n");
            return false;
         } else {
            if (debug) printf("found\n");
         }
      } else
      if (tmpNode -> id == G_SV_INTEGER_STRUCT_UNION_TYPE) {
         NODE* subNode = tmpNode -> sub -> next;
         if (subNode != NULL) // empty struct
         if (subNode -> id == G_SV_PACKED_KEYWORD)
            subNode = subNode -> next;
         if (subNode != NULL) // empty struct
         while (1) {
            if (debug) printf("---------------------------- subNode -> sub:\n");
            if (debug) printTree(4, subNode -> sub);
            if (subNode -> sub -> id == G_SV_DATA_TYPE) {
               if (!(checkTypeDependency(subNode -> sub, doneSiNode)))
                  return false;
            }
            if (subNode -> next == NULL)
               break;
            subNode = subNode -> next;
         }
      }
   }
   return true;
}
/////////////////////////////////////////////////////////////////////////////////
/// Write SystemVerilog module
///////////////////////////////////////////////////////////////////////////////// 
string writeSystemVerilogModule (NODE* modNode) {
   bool debug = false;
            string out = ""; 
            NODE* dbEntryNode = modNode -> sub;
            NODE* dbModuleParametersNode = NULL;
            NODE* dbModuleRegistersNode = NULL;
            NODE* dbModuleLatchesNode = NULL;
            NODE* dbModuleItemsNode = NULL;
            NODE* dbModuleTypesNode = NULL;
            NODE* dbModuleFunctionsNode = NULL;
            NODE* dbModuleConditionsNode = NULL;
            NODE* dbModuleDatapathsNode = NULL;
            NODE* dbModuleEventsNode = NULL;
            NODE* dbNamedPortsNode = NULL;
            NODE* dbModuleWiresNode = NULL;
            NODE* dbPortDeclarationsNode = NULL;
            NODE* dbSubModuleNode = NULL;
            while (true) {
               if (dbEntryNode -> id == DB_MODULE_PARAMETER)
                  dbModuleParametersNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_REGISTERS)
                  dbModuleRegistersNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_LATCHES)
                  dbModuleLatchesNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_ITEMS)
                  dbModuleItemsNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_TYPES)
                  dbModuleTypesNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_FUNCTIONS)
                  dbModuleFunctionsNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_CONDITIONS)
                  dbModuleConditionsNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_DATAPATHS)
                  dbModuleDatapathsNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_EVENTS)
                  dbModuleEventsNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_NAMED_PORTS)
                  dbNamedPortsNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_MODULE_WIRES)
                  dbModuleWiresNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_SUB_MODULES)
                  dbSubModuleNode = dbEntryNode;
               else if (dbEntryNode -> id == DB_PORT_DECLARATIONS)
                  dbPortDeclarationsNode = dbEntryNode;
               if (dbEntryNode -> next == NULL)
                  break;
               dbEntryNode = dbEntryNode -> next;
            }
            
            bool truePortsInline = true;
               NODE* inoutTree = initNode(0);
               NODE* signalTree = initNode(0);

               out.append(" (");
               
               if (!truePortsInline) 
               if (dbNamedPortsNode != NULL) 
               if (dbNamedPortsNode -> sub != NULL) {
                  if (debug) printTree(dbNamedPortsNode -> sub);
                  if (debug) printf("id: %d\n", dbNamedPortsNode -> sub -> id);
                  NODE* tmpNode = dbNamedPortsNode -> sub;
                  bool first = true;
                  while (true) {
                     if (!first)
                        out.append(",");
                     first = false;
                     out.append("\n\t");
                     out.append(getSI(tmpNode));
                     if (tmpNode -> next == NULL)
                        break;
                     tmpNode = tmpNode -> next;
                  }
               }
               if (truePortsInline)
               if (dbPortDeclarationsNode != NULL) 
               if (dbPortDeclarationsNode -> sub != NULL) {
                  if (debug) printf("id: %d\n", dbNamedPortsNode -> sub -> id);
                  NODE* tmpNode = dbPortDeclarationsNode -> sub;
                  if (debug) printTree(5, tmpNode);
                  bool first = true;
                  while (1) {
                     if (tmpNode -> sub != NULL) {
                        if (debug) printTree(5, tmpNode -> sub);
                        string tmpOut = ""; 
                        writer_sv_port_declaration(tmpOut, tmpNode -> sub);
                        if (debug) printf("%s\n", tmpOut.c_str());
                        if (first)
                           first = false;
                        else
                           out.append(", ");
                        out.append(tmpOut.substr(0, tmpOut.length() - 1));
                        if ( (tmpNode -> sub -> id == G_SV_INOUT_DECLARATION) ) {
                           NODE* portIdentifierNode = NULL;
                           if (tmpNode -> sub -> sub -> sub -> id == G_SV_NET_PORT_TYPE)
                              portIdentifierNode = getNode(tmpNode -> sub -> sub -> sub -> next, G_SV_PORT_IDENTIFIER);
                           else
                              portIdentifierNode = getNode(tmpNode -> sub, G_SV_PORT_IDENTIFIER);
                           addSITree(getNode(portIdentifierNode, G_SI), NULL, inoutTree);
                        }
                     }
                     if (tmpNode -> next == NULL)
                        break;
                     tmpNode = tmpNode -> next;
                  }  
               }

               out.append(");");        
               ///////////////////////////////////
               // Parameters
               ///////////////////////////////////
               bool printComment = true;
               if (dbModuleParametersNode != NULL)
               if (dbModuleParametersNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleParametersNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           if (printComment) {
                              if (debug) printf("------------------- parameters:\n");
                              out.append("\n//------------------- Parameter(s):\n");
                              printComment = false;
                           }
                           if (debug) printTree(tmpNode -> sub);
                           string tmpOut;
                           writer_sv_parameter_declaration(tmpOut, tmpNode -> sub);        
                           //if (reportLevel >= 2)
                           //    printf("%s\n", tmpOut.c_str());
                           out.append(tmpOut);
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
               ///////////////////////////////////
               // Types
               ///////////////////////////////////
               printComment = true;
               NODE* doneSiNode = initNode(0);
               if (dbModuleTypesNode != NULL)
               if (dbModuleTypesNode -> sub != NULL) {
                  ///////////////////////////////////
                  // Types ordering, repeat until all types written
                  ///////////////////////////////////
                  while (1) {
                     bool dependencyFound = false;
                     NODE* tmpClNode = dbModuleTypesNode -> sub;
                     while (1) {
                        if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                        NODE* tmpNode = tmpClNode -> sub;
                        while (1) {
                           if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                           if (tmpNode -> sub != NULL) {
                              if (printComment) {
                                 if (debug) printf("------------------- types:\n");
                                 out.append("\n//------------------- Types(s):\n");
                                 printComment = false;
                              }
                              if (debug) printTree(4, tmpNode -> sub);
                              NODE* typeNameNode = getNodeSubLevel(tmpNode, G_SV_TYPE_IDENTIFIER);
                              if (debug) {
                                 printf("---------------------------- checkTypeDependency:\n");
                                 printTree(typeNameNode -> sub);
                              }
                              bool found = false;
                              if (doneSiNode -> sub != NULL)
                              if (checkSITree(typeNameNode -> sub -> sub, doneSiNode -> sub))
                                 found = true;
                              if (!(found))
                              if (checkTypeDependency(tmpNode -> sub, doneSiNode)) {
                                 if (debug) printf("printing type: ");
                                 if (debug) printTree(typeNameNode -> sub);
                                 addSITree(typeNameNode -> sub, NULL, doneSiNode);
                                 string tmpOut;
                                 writer_sv_type_declaration(tmpOut, tmpNode -> sub);        
                                 //if (reportLevel >= 2)
                                 //   printf("%s\n", tmpOut.c_str());
                                 out.append(tmpOut);
                              } else {
                                 if (debug) printf("not printing type: ");
                                 if (debug) printTree(typeNameNode -> sub);
                                 dependencyFound = true;
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
                     if (!(dependencyFound))
                        break;
                  }
               }
               if (debug) printSITree(doneSiNode);
               ///////////////////////////////////
               // Functions
               ///////////////////////////////////
               printComment = true;
               if (dbModuleFunctionsNode != NULL)
               if (dbModuleFunctionsNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleFunctionsNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           if (printComment) {
                              if (debug) printf("------------------- functions:\n");
                              out.append("\n//------------------- functions(s):\n");
                              printComment = false;
                           }
                           if (debug) printTree(tmpNode -> sub);
                           string tmpOut;
                           writer_sv_function_declaration(tmpOut, tmpNode -> sub);        
                           //if (reportLevel >= 2)
                           //   printf("%s\n", tmpOut.c_str());
                           out.append(tmpOut);
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
               ///////////////////////////////////
               // Port declarations
               ///////////////////////////////////
               printComment = true;
               if (!truePortsInline)
               if (dbPortDeclarationsNode != NULL) 
               if (dbPortDeclarationsNode -> sub != NULL) {
                  if (debug) printf("id: %d\n", dbNamedPortsNode -> sub -> id);
                  NODE* tmpNode = dbPortDeclarationsNode -> sub;
                  if (debug) printTree(5, tmpNode);
                  while (1) {
                     if (tmpNode -> sub != NULL) {
                        if (printComment) {
                           if (debug) printf("------------------- port declaration:\n");
                           out.append("\n//------------------- Port declaration(s):\n");
                           printComment = false;
                        }
                        if (debug) printTree(5, tmpNode -> sub);
                        string tmpOut = ""; 
                        writer_sv_port_declaration(tmpOut, tmpNode -> sub);
                        if (debug) printf("%s\n", tmpOut.c_str());
                        out.append(tmpOut);
                        if (tmpNode -> sub -> id == G_SV_INOUT_DECLARATION) {
                           NODE* portIdentifierNode = NULL;
                           if (tmpNode -> sub -> sub -> sub -> id == G_SV_NET_PORT_TYPE)
                              portIdentifierNode = getNode(tmpNode -> sub -> sub -> sub -> next, G_SV_PORT_IDENTIFIER);
                           else
                              portIdentifierNode = getNode(tmpNode -> sub, G_SV_PORT_IDENTIFIER);
                           addSITree(getNode(portIdentifierNode, G_SI), NULL, inoutTree);
                        }
                     }
                     if (tmpNode -> next == NULL)
                        break;
                     tmpNode = tmpNode -> next;
                  }  
               }
               ///////////////////////////////////
               // Register declaration
               ///////////////////////////////////
               printComment = true;
               NODE* registerTree = initNode(0);
               if (dbModuleRegistersNode != NULL)
               if (dbModuleRegistersNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleRegistersNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           string itemName = getSI(tmpNode -> sub);
                           if (!(checkTree(itemName, inoutTree))) {
                              if (printComment) {
                                 if (debug) printf("------------------- register declaration:\n");
                                 out.append("\n//------------------- Register declaration(s):\n");
                                 printComment = false;
                              }
                              if (debug) printTree(5, tmpNode -> sub);
                              string tmpOut = "";
                              writeDeclaration(tmpOut, 2, getSI(tmpNode -> sub), tmpNode -> sub -> next);
                              tmpOut.append("; ");
                              //if (reportLevel >= 2)
                              //   printf("%s\n", tmpOut.c_str());
                              out.append(tmpOut);
                              addSITree(tmpNode -> sub, NULL, registerTree);
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
               ///////////////////////////////////
               // Latch (reg) declaration
               ///////////////////////////////////
               if (dbModuleLatchesNode != NULL)
               if (dbModuleLatchesNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleLatchesNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           string itemName = getSI(tmpNode -> sub);
                           if (!(checkTree(itemName, inoutTree))) {
                              if (printComment) {
                                 if (debug) printf("------------------- Latch (reg) declaration:\n");
                                 out.append("\n//------------------- Latch (reg) declaration(s):\n");
                                 printComment = false;
                              }
                              if (debug) printTree(tmpNode -> sub);
                              string tmpOut = "";
                              writeDeclaration(tmpOut, 2, getSI(tmpNode -> sub), tmpNode -> sub -> next);
                              tmpOut.append("; ");
                              //if (reportLevel >= 2)
                              //   printf("%s\n", tmpOut.c_str());
                              out.append(tmpOut);
                              addSITree(tmpNode -> sub, NULL, registerTree);
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
               ///////////////////////////////////
               // Procedural register declaration
               ///////////////////////////////////
               printComment = true;
               if (dbModuleItemsNode != NULL)
               if (dbModuleItemsNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleItemsNode -> sub;
                  if (tmpClNode -> sub != NULL)
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           string itemName = getSI(tmpNode -> sub);
                           if (!(checkTree(itemName, inoutTree))) {
                              if (debug) printTree(tmpNode -> sub);
                              NODE* assignNode = getNode(tmpNode -> sub, DB_ASSIGN);
                              NODE* coneNode = getNode(tmpNode -> sub, DB_CONE);
                              NODE* blockingNode = getNode(tmpNode -> sub, G_SV_BLOCKING_ASSIGN_EXPRESSION);
                              NODE* nonblockingNode = getNode(tmpNode -> sub, G_SV_NONBLOCKING_ASSIGN_EXPRESSION);
                              NODE* identifierListNode = getNode(tmpNode -> sub, G_PDVL_IDENTIFIER_LIST);
                              bool sinkSourceDef = false;
                              if (identifierListNode != NULL) {
                                 if (debug) printf("-------------------------- check for attribute\n"); 
                                 if (debug) printTree(tmpNode -> sub);
                                 NODE* attNode = getNodeSubLevel(tmpNode -> sub, G_SV_ATTRIBUTE_INSTANCE);
                                 if (debug) printf("-------------------------- attNode\n"); 
                                 if (attNode != NULL) {
                                    if (debug) printTree(attNode);
                                    string attName = getSI(attNode);
                                    if (debug) printf("attName: %s\n", attName.c_str());
                                    transform(attName.begin(), attName.end(), attName.begin(), ::tolower);
                                    if ( (attName == "source") |
                                         (attName == "sink")   )
                                       sinkSourceDef = true;
                                 }
                              }
                              if (	(coneNode == NULL)        &
                                    (blockingNode == NULL)    &
                                    (nonblockingNode == NULL) &
                                    (assignNode == NULL)   	  &
                                    (!(sinkSourceDef))        ) {
                              } else {
                                 if (printComment) {
                                    if (debug) printf("------------------- prodedural register declaration:\n");
                                    out.append("\n//------------------- Procedural register declaration(s):\n");
                                    printComment = false;
                                 }
                                 unsigned identifier = 2;
                                 if (	(blockingNode != NULL)	&
                                 		(nonblockingNode != NULL)	)
                                    identifier = 1;
                                 string tmpOut = "";
                                 writeDeclaration(tmpOut, identifier, getSI(tmpNode -> sub), tmpNode -> sub -> next);
                                 tmpOut.append("; ");
                                 if (debug) printf("%s\n", tmpOut.c_str());
                                 out.append(tmpOut);
                              }
                              addSITree(tmpNode -> sub, NULL, registerTree);
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
               ///////////////////////////////////
               // Condition declaration
               ///////////////////////////////////
               printComment = true;
               if (dbModuleConditionsNode != NULL)
               if (dbModuleConditionsNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleConditionsNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           string condName = "";
                           NODE* condSignalNameNode = getNodeSubLevel(tmpNode -> sub, G_PDVL_COND_SIGNAL_NAME);
                           if (condSignalNameNode == NULL)
                              condName = getSI(tmpNode -> sub);
                           else
                              condName = getSI(condSignalNameNode -> sub);
                           if (debug) printTree(tmpNode -> sub);
                           if (!(checkTree(condName, registerTree))) {
                              // Although multiple cond definition possible, only
                              // the first one has a DB_CONE entry
                              NODE* portNode = getNode(tmpNode -> sub -> sub, G_PDVL_TF_PORT_LIST_BRACKETS);
                              NODE* coneNode = getNode(tmpNode -> sub, DB_CONE);
                              if (coneNode != NULL) {
                                 if (portNode == NULL) {
                                    if (printComment) {
                                       if (debug) printf("------------------- conditions declaration:\n");
                                       out.append("\n//------------------- Condition declaration(s):\n");
                                       printComment = false;
                                    }
                                    string tmpOut;
                                    tmpOut.append("reg ");
                                    tmpOut.append(condName);
                                    tmpOut.append("; ");
                                    //if (reportLevel >= 2)
                                    //   printf("%s\n", tmpOut.c_str());
                                    out.append(tmpOut);
                                 }
                                 if (condSignalNameNode == NULL)
                                    addSITree(tmpNode -> sub, NULL, registerTree);
                                 else
                                    addSITree(condSignalNameNode -> sub, NULL, registerTree);
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
               }             
               if (debug) printTree(registerTree);
               ///////////////////////////////////
               // Wire declaration
               ///////////////////////////////////
               printComment = true;
               if (dbModuleWiresNode != NULL)
               if (dbModuleWiresNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleWiresNode -> sub;
                  if (debug) printTree(5, tmpClNode);
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           if (debug) printf("-----------------------------\n");
                           if (debug) printTree(tmpNode);
                           NODE* identifierNode = getNodeSubLevel(tmpNode, G_SV_LIST_OF_NET_DECL_ASSIGNMENTS);
                           if (identifierNode == NULL)
                              identifierNode = getNodeSubLevel(tmpNode, G_SV_LIST_OF_VARIABLE_DECL_ASSIGNMENTS);
                           if (identifierNode == NULL)
                              identifierNode = getNodeSubLevel(tmpNode -> sub, G_SV_LIST_OF_NET_DECL_ASSIGNMENTS);
                           if (debug) printf("----------------------------- identifierNode\n");
                           if (debug) printTree(identifierNode);
                           string wireName = getSI(identifierNode -> sub);
                           if (!(checkTree(wireName, inoutTree))) 
                           if (!(checkTree(wireName, registerTree))) {
                              if (printComment) {
                                 if (debug) printf("------------------- wire declaration:\n");
                                 out.append("\n//------------------- Wire declaration(s):\n");
                                 printComment = false;
                              }
                              string tmpOut;
                              if (tmpNode -> id == G_SV_NET_DECLARATION) {
                                 writer_sv_net_declaration(tmpOut, tmpNode -> sub);
                              } else 
                              if (tmpNode -> id == G_SV_DATA_DECLARATION) {
                                 writer_sv_data_declaration(tmpOut, tmpNode -> sub);
                              } else {
                                 NODE* coneNode = getNode(tmpNode -> sub, DB_CONE);
                                 if (coneNode == NULL) {
                                    tmpOut.append("wire");
                                 } else {
                                    tmpOut.append("reg");
                                 }
                                 if (tmpNode -> sub -> next != NULL)
                                 if (tmpNode -> sub -> next -> id == G_SV_SELECT) {
                                    writer_sv_select(tmpOut, tmpNode -> sub -> next -> sub);
                                 }
                                 tmpOut.append(" "); 
                                 tmpOut.append(wireName);
                                 tmpOut.append("; ");
                              }
      
                              if (debug) printf("Wire %s\n", tmpOut.c_str());
                              out.append(tmpOut);
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
      
               ///////////////////////////////////
               // Register body
               ///////////////////////////////////
               printComment = true;
               if (dbModuleRegistersNode != NULL)
               if (dbModuleRegistersNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleRegistersNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           string regName = getSI(tmpNode -> sub);
                           if (debug) printf("----------------------\n");
                           if (debug) printTree(tmpNode -> sub);
                           if (debug) printf("cont 1.\n");
                           NODE* coneNode = getNode(tmpNode -> sub, DB_CONE);
                           if (coneNode == NULL) {
                           } else {
                              if (printComment) {
                                 if (debug) printf("------------------- register body\n");
                                 out.append("\n//------------------- Register assignment(s):\n");
                                 printComment = false;
                              }
                              string tmpOut = cleanSVCone(coneNode, false, false, "", NULL, NULL, signalTree);
                              //if (reportLevel >= 2)
                              //   printf("%s\n", tmpOut.c_str());
                              out.append(tmpOut);
                           }
                           if (debug) printf("cont 2.\n");
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
               ///////////////////////////////////
               // Latches body
               ///////////////////////////////////
               printComment = true;
               if (dbModuleLatchesNode != NULL)
               if (dbModuleLatchesNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleLatchesNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           string regName = getSI(tmpNode -> sub);
                           if (debug) printf("----------------------\n");
                           if (debug) printTree(tmpNode -> sub);
                           if (debug) printf("cont 1.\n");
                           NODE* coneNode = getNode(tmpNode -> sub, DB_CONE);
                           if (coneNode == NULL) {
                           } else {
                              if (printComment) {
                                 if (debug) printf("------------------- latch body\n");
                                 out.append("\n//------------------- Latch assignment(s):\n");
                                 printComment = false;
                              }
                              string tmpOut = cleanSVCone(coneNode, false, false, "", NULL, NULL, signalTree);
                              //if (reportLevel >= 2)
                              //   printf("%s\n", tmpOut.c_str());
                              out.append(tmpOut);
                           }
                           if (debug) printf("cont 2.\n");
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
               ///////////////////////////////////
               // Items body
               ///////////////////////////////////
               printComment = true;
               if (dbModuleItemsNode != NULL)
               if (dbModuleItemsNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleItemsNode -> sub;
                  if (tmpClNode -> sub != NULL)
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           if (debug) printTree(9, tmpNode -> sub);
                           NODE* coneNode = getNode(tmpNode -> sub, DB_CONE);
                           if (coneNode == NULL) {
                           } else {
                              string itemName = getSI(tmpNode -> sub);
                              if (debug) printf("------------------- tmpNode\n");
                              if (debug) printTree(3, tmpNode);
                              NODE* typeNode = getNodeSubLevel(tmpNode, DB_SIGNAL_TYPE);
                              if (printComment) {
                                 if (debug) printf("------------------- items body\n");
                                 out.append("\n//------------------- Item assignment(s):\n");
                                 printComment = false;
                              }
                              string tmpOut = cleanSVCone(coneNode, true, true, itemName, typeNode, dbModuleTypesNode, signalTree);
                              if (debug) printf("items body: %s\n", tmpOut.c_str());
                              out.append(tmpOut);
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
               ///////////////////////////////////
               // Conditions as function
               ///////////////////////////////////
               printComment = true; 
               if (dbModuleConditionsNode != NULL)
               if (dbModuleConditionsNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleConditionsNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           if (debug) printTree(tmpNode -> sub);
                           if (debug) printf("----------------------\n");
                           string condName = getSI(tmpNode -> sub);
                           if (debug) printf("condition function: %s\n", condName.c_str());
                           NODE* coneNode = getNode(tmpNode -> sub, DB_CONE);
                           if (coneNode != NULL) 
                           if (coneNode -> sub != NULL)
                           if (coneNode -> sub -> sub != NULL)
                           if (coneNode -> sub -> sub -> id == G_SV_FUNCTION_DECLARATION) {
                              if (printComment) {
                                 if (debug) printf("------------------- conditions body:\n");
                                 out.append("\n//------------------- Condition(s) as function(s):\n");
                                 printComment = false;
                              }
                              if (debug) printTree(coneNode);
                              string tmpOut = "";
                              writer_sv_function_declaration(tmpOut, coneNode -> sub -> sub -> sub);
                              //if (reportLevel >= 2)
                              //   printf("%s\n", tmpOut.c_str());
                              out.append(tmpOut);
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
               ///////////////////////////////////
               // Conditions body
               ///////////////////////////////////
               printComment = true;
               if (dbModuleConditionsNode != NULL)
               if (dbModuleConditionsNode -> sub != NULL) {
                  NODE* tmpClNode = dbModuleConditionsNode -> sub;
                  while (1) {
                     if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
                     NODE* tmpNode = tmpClNode -> sub;
                     while (1) {
                        if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                        if (tmpNode -> sub != NULL) {
                           if (debug) printTree(tmpNode -> sub);
                           if (debug) printf("----------------------\n");
                           string condName = getSI(tmpNode -> sub);
                           if (debug) printf("condition assignment: %s\n", condName.c_str());
                           NODE* coneNode = getNode(tmpNode -> sub, DB_CONE);
                           if (coneNode != NULL) 
                           if (coneNode -> sub != NULL)
                           if (coneNode -> sub -> sub != NULL)
                           if (coneNode -> sub -> sub -> id == G_SV_ALWAYS_CONSTRUCT) {
                              if (printComment) {
                                 if (debug) printf("------------------- conditions body:\n");
                                 out.append("\n//------------------- Condition assignment(s):\n");
                                 printComment = false;
                              }
                              if (debug) printTree(coneNode);
                              string tmpOut = cleanSVCone(coneNode, true, false, "", NULL, NULL, signalTree);
                              //if (reportLevel >= 2)
                              //   printf("%s\n", tmpOut.c_str());
                              out.append(tmpOut);
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
               ///////////////////////////////////
               // Submodules         dbSubModuleNode
               ///////////////////////////////////
               printComment = true;
               if (dbSubModuleNode != NULL)
               if (dbSubModuleNode -> sub != NULL) {
                  if (printComment) {
                     if (debug) printf("------------------- submodules:\n");
                     out.append("\n//------------------- Submodule(s):\n");
                     printComment = false;
                  }
                  string tmpHeader = "";
                  if (debug) printSITree(dbSubModuleNode -> sub);
                  if (debug) printTree(dbSubModuleNode);
                  string tmpOut = writeSubModule(tmpHeader, dbSubModuleNode -> sub, true);
                  if (debug) printf("%s\n", tmpOut.c_str());
                  out.append(tmpOut);
      
               }             
               out.append("endmodule");
    return out;
}
/////////////////////////////////////////////////////////////////////////////////
/// Mark printed module
/////////////////////////////////////////////////////////////////////////////////
void markModulePrint (NODE* node, 
                      bool trueModuleFalseInstance) {
   bool debug = false;
   if (node -> id == 0) {
      if (trueModuleFalseInstance) {
         if (node -> sub != NULL)
            markModulePrint(node -> sub, false);
      } else
      if (node -> sub != NULL)
      if (node -> sub -> sub != NULL) {
         //mark
         NODE* dbEntryNode = node -> sub -> sub;
         NODE* newPrintNode = initNode(DB_PRINT);
         newPrintNode -> next = dbEntryNode;
         node -> sub -> sub = newPrintNode;
         if (debug) printf("found module.\n");
         if (debug) printTree(node -> sub -> sub);
         NODE* dbSubModuleNode = NULL;
         while (true) {
            if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
            if (dbEntryNode -> id == DB_SUB_MODULES) {
               dbSubModuleNode = dbEntryNode;
               break;
            }
            if (dbEntryNode -> next == NULL) {
               break;
            }
            dbEntryNode = dbEntryNode -> next;
         }  
      
         if (dbSubModuleNode != NULL)
            markModulePrint(dbSubModuleNode, true); 
      }
   } else
   if (node -> sub != NULL) {
      markModulePrint(node -> sub, trueModuleFalseInstance);
   }
   if (node -> next != NULL)
      markModulePrint(node -> next, trueModuleFalseInstance);
}
/////////////////////////////////////////////////////////////////////////////////
/// Check if sub-module already printed
/////////////////////////////////////////////////////////////////////////////////
bool checkSubModulePrint (NODE* node, 
                          bool trueModuleFalseInstance) {
   bool debug = false;
   bool returnBool = true;
   while (true) {
      if (node -> sub != NULL)
      if (node -> sub -> id != 0) {
         if (!(checkSubModulePrint(node -> sub, trueModuleFalseInstance)))
            return false;
      } else
      if (node -> sub -> sub != NULL) 
      if (node -> sub -> sub -> sub != NULL) {
         if (trueModuleFalseInstance) {  
            if (!(checkSubModulePrint(node -> sub, false)))
               return false;
         } else {
            NODE* modNode = node -> sub -> sub;
            while (true) {
               if (debug) printf("sub modNode: %d\n", modNode -> id);
               NODE* dbEntryNode = modNode -> sub;
               NODE* dbPrintNode = NULL;
               NODE* dbSubModuleNode = NULL;
               while (true) {
                  if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
                  if (dbEntryNode -> id == DB_PRINT)
                     dbPrintNode = dbEntryNode;
                  else if (dbEntryNode -> id == DB_SUB_MODULES)
                     dbSubModuleNode = dbEntryNode;
                  if (dbEntryNode -> next == NULL)
                     break;
                  dbEntryNode = dbEntryNode -> next;
               }
               if (dbPrintNode != NULL) {
                  if (debug) printf("sub print module found.\n");
                  if (dbPrintNode -> sub == NULL) {
                     if (debug) printf("sub print module found, undefined.\n");
                     return false;
                  } else
                  if (debug) printf("sub print module found, defined.\n");
               }
               if (modNode -> next == NULL)
                  break;
               modNode = modNode -> next;
            }
         }
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
   return true;   
}
/////////////////////////////////////////////////////////////////////////////////
/// Uniquify module to be written
/////////////////////////////////////////////////////////////////////////////////
bool uniquifyWriteModule (NODE* node, 
                          string &header, 
                          string &outputDir) {
   bool debug = false;
   bool redo = false;
   //////////////////////////////////////
   // Go through dbModule list SI tree
   //////////////////////////////////////
   while (true) {
      string moduleName = "";
      moduleName.append(header);
      moduleName.append(node2String(node));
      if (node -> sub != NULL)
      if (node -> sub -> id != 0) {
         if (uniquifyWriteModule(node -> sub, moduleName, outputDir))
            redo = true;
      } else
      //////////////////////////////////////
      // Leave found
      //////////////////////////////////////
      if (node -> sub -> sub != NULL) 
      if (node -> sub -> sub -> sub != NULL) {
         if (debug) printf("uniquifyWriteModule: %s\n", moduleName.c_str());
         NODE* listNode = node -> sub -> sub;
         //////////////////////////////////////
         // Go through module list
         // Check for undefined sub modules
         //////////////////////////////////////
         unsigned modules = 0;
         //unsigned defined = 0;
         unsigned undefinedSub = 0;
         bool done = false;
         NODE* lastDefinedBDPrintNode = NULL;
         NODE* lastModNode = NULL;
         if (debug) printTree(4, listNode);
         while (true) {
            if (listNode -> sub != NULL) {
               NODE* modNode = listNode -> sub;
               if (debug) printf("modNode: %d\n", modNode -> id);
               if (modNode -> sub != NULL) {
               NODE* dbEntryNode = modNode -> sub;
               NODE* dbPrintNode = NULL;
               NODE* dbSubModuleNode = NULL;
               while (true) {
                  if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
                  if (dbEntryNode -> id == DB_PRINT) {
                     dbPrintNode = dbEntryNode;
                     lastDefinedBDPrintNode = dbEntryNode;
                     lastModNode = modNode;
                  }
                  else if (dbEntryNode -> id == DB_SUB_MODULES)
                     dbSubModuleNode = dbEntryNode;
                  if (dbEntryNode -> next == NULL)
                     break;
                  dbEntryNode = dbEntryNode -> next;
               }
               if (dbPrintNode != NULL) {
                  modules ++;
                  if (dbPrintNode -> sub != NULL) {
                     done = true;
                     break;
                  } else
                  if (dbSubModuleNode != NULL) {
                     if (debug) printf("Print module has sub.\n");
                     if (checkSubModulePrint(dbSubModuleNode -> sub, true)) {
                     } else {
                        undefinedSub ++;
                        redo = true;
                        break;
                     }
                  } else {
                     if (debug) printf("Print module has no sub.\n");
                  }
               }
               }
            }
            if (listNode -> next == NULL)
               break;
            listNode = listNode -> next;
         } 
         if (debug) printf("Print modules %d done %d undefinedSub %d\n", modules, done, undefinedSub);
         //////////////////////////////////////
         // If undefinedSub == 0: 
         //    if modules == 1 => write and add name to dbPrint
         //////////////////////////////////////
         if (undefinedSub == 0)
         if (!(done)) 
         if (modules == 1) {
            string thisModuleName = moduleName; 

            string out = writeSystemVerilogModule(lastModNode);
            string outFileName = "";
            if (outputDir.length() > 0) {
               outFileName.append(outputDir);
               outFileName.append("/");
            }
            outFileName.append(thisModuleName);
            outFileName.append(".sv");

            if (reportLevel >= 2)
               printf("4.1 Writing file (module): %s (%s)\n", outFileName.c_str(), thisModuleName.c_str()); 
            out.insert(0, thisModuleName);
            out.insert(0, "module ");
            prettyPrint(out);
            if (debug) printf("%d\n", lastModNode -> id);
            //if (reportLevel > 3)
            //   printf("\n%s\n", out.c_str());
            //printf("---------------------------------\n");
            FILE* outFile = fopen(outFileName.c_str(),"w");
            fprintf(outFile, "%s", out.c_str()); 
            fclose(outFile); 

            NODE* newNode = initNode(G_SI);
            parser_si(thisModuleName, 0, newNode); 
            lastDefinedBDPrintNode -> sub = newNode;
            if (debug) printTree(lastDefinedBDPrintNode -> sub);
            
         //////////////////////////////////////
         // modules > 1
         //////////////////////////////////////
         } else 
         if (modules > 1) {
            string strArr[modules];
            unsigned ptr = 0;
            //////////////////////////////////////
            // write and save to strArr
            //////////////////////////////////////
            listNode = node -> sub -> sub; 
            while (true) {
               if (listNode -> sub != NULL) {
                  NODE* modNode = listNode -> sub;
                  NODE* lastDefinedBDPrintNode = NULL;
                  if (debug) printf("modNode: %d\n", modNode -> id);
                  NODE* dbEntryNode = modNode -> sub;
                  NODE* dbPrintNode = NULL;
                  NODE* dbSubModuleNode = NULL;
                  while (true) {
                     if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
                     if (dbEntryNode -> id == DB_PRINT)
                        dbPrintNode = dbEntryNode;
                     else if (dbEntryNode -> id == DB_SUB_MODULES)
                        dbSubModuleNode = dbEntryNode;
                     if (dbEntryNode -> next == NULL)
                        break;
                     dbEntryNode = dbEntryNode -> next;
                  }
                  if (dbPrintNode != NULL) {
                     string out = writeSystemVerilogModule(modNode);
                     strArr[ptr] = out;
                     ptr += 1;
                     if (debug) printf("%s\n", out.c_str());
                  } 
                  if (debug) printf("\n");
               }
               if (listNode -> next == NULL)
                  break;
               listNode = listNode -> next;
            }
            //////////////////////////////////////
            // get ptr to str used most often
            //////////////////////////////////////
            unsigned maxPtr = 0;
            unsigned maxCnt = 0;
            for (int a = 0; a < ptr; a++) {
               if (debug) printf("Module string:\n");
               if (debug) printf("%s\n", strArr[a].c_str());
               unsigned thisCnt = 1;
               for (int b = a + 1; b < ptr; b++) {
                  if (debug) printf("compare: %d %d\n", a, b);
                  if (strArr[a].compare(strArr[b]) == 0) {
                     thisCnt += 1;
                     if (debug) printf("Match %d:\n", thisCnt);
                  }
               }
               if (thisCnt > maxCnt) {
                  maxPtr = a;
                  maxCnt = thisCnt;
                  if (debug) printf("set new maxPtr: %d maxCnt: %d\n", maxPtr, maxCnt);
               }
            }
            if (debug) printf("maxPtr: %d maxCnt: %d\n", maxPtr, maxCnt);
            //////////////////////////////////////
            // go through list again
            // if print
            //    if most used => print with orig name, add to dbPrintNode
            //    else if same string => do not print, but add to dbPrintNode
            //    else uniquify and add to dbPrintNode
            //////////////////////////////////////
            listNode = node -> sub -> sub;
            ptr = 0; 
            unsigned modUniquifier = 0;
            while (true) {
               if (listNode -> sub != NULL) {
                  NODE* modNode = listNode -> sub;
                  if (debug) printf("modNode: %d\n", modNode -> id);
                  NODE* dbEntryNode = modNode -> sub;
                  NODE* dbPrintNode = NULL;
                  NODE* dbSubModuleNode = NULL;
                  while (true) {
                     if (debug) printf("dbEntryNode: %d\n", dbEntryNode -> id);
                     if (dbEntryNode -> id == DB_PRINT)
                        dbPrintNode = dbEntryNode;
                     else if (dbEntryNode -> id == DB_SUB_MODULES)
                        dbSubModuleNode = dbEntryNode;
                     if (dbEntryNode -> next == NULL)
                        break;
                     dbEntryNode = dbEntryNode -> next;
                  }
                  if (dbPrintNode != NULL) {
                     //////////////////////////////////////
                     // maxPtr
                     //////////////////////////////////////
                     if (ptr == maxPtr) {

                        string thisModuleName = moduleName; 
                        string out = strArr[ptr];
                        string outFileName = "";
                        if (outputDir.length() > 0) {
                           outFileName.append(outputDir);
                           outFileName.append("/");
                        }
                        outFileName.append(thisModuleName);
                        outFileName.append(".sv");

                        if (reportLevel >= 2)
                           printf("4.1 Writing file (module): %s (%s)\n", outFileName.c_str(), thisModuleName.c_str()); 
                        out.insert(0, thisModuleName);
                        out.insert(0, "module ");
                        prettyPrint(out);
                        if (debug) printf("%d\n", lastModNode -> id);
                        FILE* outFile = fopen(outFileName.c_str(),"w");
                        fprintf(outFile, "%s", out.c_str()); 
                        fclose(outFile); 

                        NODE* newNode = initNode(G_SI);
                        parser_si(thisModuleName, 0, newNode); 
                        dbPrintNode -> sub = newNode;
                        if (debug) printTree(dbPrintNode -> sub);
                     } else 
                     //////////////////////////////////////
                     // same
                     //////////////////////////////////////
                     if (strArr[ptr].compare(strArr[maxPtr]) == 0) {
                        string thisModuleName = moduleName; 
                        if (debug) printf("\n\nSame module: %s\n", thisModuleName.c_str()); 
                        NODE* newNode = initNode(G_SI);
                        parser_si(thisModuleName, 0, newNode); 
                        dbPrintNode -> sub = newNode;
                        if (debug) printTree(dbPrintNode -> sub);
                     } else {
                     //////////////////////////////////////
                     // uniquify
                     //////////////////////////////////////
                        string thisModuleName = moduleName; 
                        if (debug) printf("\n\nUniquify module: %s\n", thisModuleName.c_str()); 
                        thisModuleName.append(" ");
                        while (1) {
                           thisModuleName = moduleName; 
                           thisModuleName.append("_");
                           thisModuleName.append(to_string(modUniquifier));
                           thisModuleName.append(" ");
                           modUniquifier += 1;
                           NODE* tmpNode = initNode(0);
                           parser_si(thisModuleName, 0, tmpNode);
                           if (!(checkSITree(tmpNode -> sub, dbModuleNode -> sub)))
                              break;
                        }
                        thisModuleName = thisModuleName.substr(0, thisModuleName.length() - 1); // remove last space 
                        string out = strArr[ptr];
                        string outFileName = "";
                        if (outputDir.length() > 0) {
                           outFileName.append(outputDir);
                           outFileName.append("/");
                        }
                        outFileName.append(thisModuleName);
                        outFileName.append(".sv");

                        if (reportLevel >= 2)
                           printf("4.1 Writing file (module): %s (%s)\n", outFileName.c_str(), thisModuleName.c_str()); 
                        out.insert(0, thisModuleName);
                        out.insert(0, "module ");
                        prettyPrint(out);
                        if (debug) printf("%d\n", lastModNode -> id);
                        //if (reportLevel >= 2)
                        //   printf("\n%s\n", out.c_str());
                        FILE* outFile = fopen(outFileName.c_str(),"w");
                        fprintf(outFile, "%s", out.c_str()); 
                        fclose(outFile); 

                        NODE* newNode = initNode(G_SI);
                        parser_si(thisModuleName, 0, newNode); 
                        dbPrintNode -> sub = newNode;
                        if (debug) printTree(dbPrintNode -> sub);
                     }
                     ptr += 1;
                  } 
                  if (debug) printf("\n");
               }
               if (listNode -> next == NULL)
                  break;
               listNode = listNode -> next;
            }
         } 
         if (debug) printf("---------------------------------------\n");
         if (node -> sub -> next != NULL)
         if (uniquifyWriteModule(node -> sub -> next, moduleName, outputDir))
            redo = true;
      }
      if (debug) printf("cont 2\n");
 
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
   return redo;   
}
/////////////////////////////////////////////////////////////////////////////////
/// write SystemVerilog package
/////////////////////////////////////////////////////////////////////////////////
void writePackage (NODE* node, 
                   string &header, 
                   string &out) {
   bool debug = false;
   while (true) {
      string moduleName = "";
      moduleName.append(header);
      moduleName.append(node2String(node));
      if (node -> sub != NULL)
      if (node -> sub -> id != 0) {
         writePackage(node -> sub, moduleName, out);
      } else
      if (node -> sub -> sub != NULL) 
      if (node -> sub -> sub -> sub != NULL)
      if (node -> sub -> sub -> sub -> sub != NULL) {
         if (debug) printTree(5, node);
         out.append("\npackage ");
         out.append(moduleName.c_str());
         out.append(";");
         //////////////////////////////////
         // first list entry point to modNode
         //////////////////////////////////
         NODE* dbEntryNode = node -> sub -> sub -> sub -> sub;
         NODE* dbModuleParametersNode = NULL;
         while (true) {
            if (dbEntryNode -> id == DB_MODULE_PARAMETER)
               dbModuleParametersNode = dbEntryNode;
            if (dbEntryNode -> next == NULL)
               break;
            dbEntryNode = dbEntryNode -> next;
         }
         ///////////////////////////////////
         // Parameters
         ///////////////////////////////////
         if (dbModuleParametersNode != NULL)
         if (dbModuleParametersNode -> sub != NULL) {
            NODE* tmpClNode = dbModuleParametersNode -> sub;
            while (1) {
               if (debug) printf("tmpClNode: %d\n", tmpClNode -> id);
               NODE* tmpNode = tmpClNode -> sub;
               while (1) {
                  if (debug) printf("tmpNode: %d\n", tmpNode -> id);
                  if (tmpNode -> sub != NULL) {
                     if (debug) printTree(tmpNode -> sub);
                     string tmpOut;
                     writer_sv_parameter_declaration(tmpOut, tmpNode -> sub);        
                     if (debug) printf("%s\n", tmpOut.c_str());
                     out.append(tmpOut);
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
         //////////////////////////////////
         // print typedefs
         //////////////////////////////////
         NODE* listNode = node -> sub -> sub -> next; 
         while (1) {
            writer_sv_type_declaration(out, listNode -> sub -> sub); 
            if (listNode -> next == NULL)
               break;
            listNode = listNode -> next;
         }
         out.append("endpackage\n");
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }   
}
/////////////////////////////////////////////////////////////////////////////////
/// write SystemVerilog code
/////////////////////////////////////////////////////////////////////////////////
void writeSystemVerilog (NODE* topModuleNode, 
                         string &outputDir) {
   bool debug = false;
   
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
   
   // mark top as print
   NODE* newPrintNode = initNode(DB_PRINT);
   newPrintNode -> next = topModuleNode -> sub;
   topModuleNode -> sub = newPrintNode;
   
   if (dbSubModuleNode != NULL)   
      markModulePrint(dbSubModuleNode, true); 
   
   string tmpHeader = "";

   unsigned maxUniRounds = 4;
   for (int i = 1; i <= maxUniRounds; i++) { 
      bool redo = uniquifyWriteModule(dbModuleNode, tmpHeader, outputDir); 
      if (!redo)
         break;
      if (i == maxUniRounds) {
         printf("ERR.WRITING.EXCEEDED_MAX_UNIFICATION_ROUNDS\n");
         exit(-1);
      }
   }
   
   if (dbPackageNode -> sub != NULL) {
      if (debug) printTree(dbPackageNode);
      string out = "";
      string outFileName = "";
      if (outputDir.length() > 0) {
         outFileName.append(outputDir);
         outFileName.append("/");
      }
      outFileName.append("packages.sv");
      if (reportLevel >= 2)
         printf("4.1 Writing package: %s\n", outFileName.c_str()); 
      tmpHeader = "";
      writePackage(dbPackageNode -> sub, tmpHeader, out);
      prettyPrint(out);
      FILE* outFile = fopen(outFileName.c_str(),"w");
      fprintf(outFile, "%s", out.c_str()); 
      fclose(outFile); 
   }
}
