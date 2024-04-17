
#include <nodesAndTrees.h>
#include <solve.h>

/////////////////////////////////////////////////////////////////////////////////
// 0—represents a logic zero or a false condition
// 1—represents a logic one or a true condition
// x—represents an unknown logic value
// z—represents a high-impedance state
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
// unsignedNumber2Unsigned
/////////////////////////////////////////////////////////////////////////////////
unsigned unsignedNumber2Unsigned (NODE* node) {
   bool debug = false;
   unsigned returnVal = 0;
   if (debug) printf("--------------------- node:\n");
   if (debug) printTree(node);
   while (true) {
      node = node -> sub -> sub;
      returnVal *= 10;
      if (node -> id != G_US_DIGIT)
         returnVal += node -> sub -> id - G_0_DIGIT;
      if (node -> next == NULL)
         break;
      node = node -> next;
   }
   return returnVal;
}
/////////////////////////////////////////////////////////////////////////////////
// binOctHex2SBin
/////////////////////////////////////////////////////////////////////////////////
NODE* binOctHex2SBin (NODE* node) {
   bool debug = false;
   if (debug) printf("------------------------------ binOctHex2SBin node:\n");
   if (debug) printTree(node);
   /////////////////////////////////////////
   // handle sign, get baseNode
   // not relevant for unsigned 
   /////////////////////////////////////////
   NODE* returnNode = initNode(0);
   NODE* baseNode = node;
   if ( (node -> id == G_SV_BINARY_BASE) |
        (node -> id == G_SV_OCTAL_BASE)  |
        (node -> id == G_SV_DECIMAL_BASE)  |
        (node -> id == G_SV_HEX_BASE)    ) {
   } else 
   if (node -> next != NULL) {
      baseNode = node -> next;
   }
   if ( (baseNode -> sub -> id == G_SV_BINARY_SIGNED_BASE) |
        (baseNode -> sub -> id == G_SV_OCTAL_SIGNED_BASE) |
        (baseNode -> sub -> id == G_SV_DECIMAL_SIGNED_BASE) |
        (baseNode -> sub -> id == G_SV_HEX_SIGNED_BASE) ) 
         returnNode -> id = 1;
   /////////////////////////////////////////
   // handle length 
   // not relevant for unsigned 
   /////////////////////////////////////////
   int length = -1;
   if ( (node -> id == G_SV_BINARY_BASE)   |
        (node -> id == G_SV_OCTAL_BASE)    |
        (node -> id == G_SV_DECIMAL_BASE)  |
        (node -> id == G_SV_HEX_BASE)      ) {
      returnNode -> next = initNode(-1);
      node = node -> next; 
   } else 
   if (node -> id == G_DECIMAL_DIGIT) {
      returnNode -> next = initNode(-1);
   } else {
      //length = string2Int(node -> sub);
      length = unsignedNumber2Unsigned(node);
      returnNode -> next = initNode(length);
      node = node -> next -> next; 
   }
   if (length == 0)
      return returnNode;
   /////////////////////////////////////////
   // handle bit 
   ///////////////////////////////////////// 
   if (node -> id == G_SV_BINARY_VALUE) {
      string tmpString = "";
      writer_sv_binary_value(tmpString, node -> sub);
      if(debug) printf("tmpString: %s\n", tmpString.c_str());
      NODE* newNode = initNode(0);
      parser_sv_binary_value_digit(tmpString, 0, newNode);
      if (debug) printTree(newNode);
      node -> sub = newNode -> sub;
   } else
   if (node -> id == G_SV_HEX_VALUE) {
      string tmpString = "";
      writer_sv_hex_value(tmpString, node -> sub);
      if(debug) printf("tmpString: %s\n", tmpString.c_str());
      NODE* newNode = initNode(0);
      parser_sv_hex_value_digit(tmpString, 0, newNode);
      if (debug) printTree(newNode);
      node -> sub = newNode -> sub;
   } else
   if (node -> id == G_SV_OCTAL_VALUE) {
      string tmpString = "";
      writer_sv_octal_value(tmpString, node -> sub);
      if(debug) printf("tmpString: %s\n", tmpString.c_str());
      NODE* newNode = initNode(0);
      parser_sv_octal_value_digit(tmpString, 0, newNode);
      if (debug) printTree(newNode);
      node -> sub = newNode -> sub;
   } else
   if (node -> id == G_SV_UNSIGNED_NUMBER)
      node = node -> sub -> sub;
   if (node -> id == G_DECIMAL_DIGIT) {
      if (debug) printf("------------------------------ binOctHex2SBin node (decimal):\n");
      if (debug) printTree(node);
      string valueString = "";
      while (1) {
         if ( (node -> id == G_X_DIGIT) |
              (node -> id == G_Z_DIGIT) ) {
            returnNode -> next -> next = initNode(node -> id - G_X_DIGIT + 2);
            return returnNode;
         }   
         if (node -> id != G_US_DIGIT)
            valueString.append(1u, node -> sub -> id - G_0_DIGIT + '0');
         if (node -> next == NULL)
            break;
         node = node -> next -> sub -> sub;
      }
      if (debug) printf("valueString: %s\n", valueString.c_str());
      if (valueString.length() > 1)
      while (1) {
         char thisChar = valueString.at(0);
         if (thisChar == '0')
           valueString = valueString.substr(1);
         else
            break;
         if (valueString.length() == 1)
            break;
      }
      NODE* ptrNode = NULL;
      while (1) {
        char lastChar = valueString.at(valueString.length() - 1);
        if (ptrNode == NULL) {
           ptrNode = initNode(lastChar % 2);
           returnNode -> next -> next = ptrNode;
        } else {
           NODE* newNode = initNode(lastChar % 2);
           ptrNode -> next = newNode;
           ptrNode = newNode;
        }
        if (lastChar % 2) {
           valueString.pop_back();
           valueString.push_back(lastChar - 1);
        }
        if (valueString == "0")
           break;
        string newString = "";
        bool transfer = false;
        for (int i = 0; i < valueString.length(); i++) {
           char thisChar = valueString.at(i);
           if (debug) printf("thisChar: %d\n", thisChar);
           if (thisChar % 2) {
              thisChar -= 1;
              thisChar = ((thisChar - 48) / 2) + 48;
              if (transfer)
                 thisChar += 5;
              transfer = true;
           } else {
              thisChar = ((thisChar - 48) / 2) + 48;
              if (transfer)
                 thisChar += 5;
              transfer = false;
           }
           if (debug) printf("thisChar: %d transfer: %d\n", thisChar, transfer);
           if (!( (thisChar == 48)          &
                  (newString.length() == 0) ))
              newString.push_back(thisChar);
           if (debug) printf("newString: %s\n", newString.c_str());
        }
        if (debug) printf("newString: %s\n", newString.c_str());
        valueString = newString;
        //exit(-1);
      }
   } else
   while (1) {
      if (debug) printf("------------------------------ binOctHex2SBin node:\n");
      if (debug) printTree(node);
      if (baseNode -> id == G_SV_BINARY_BASE) {
         if (node -> sub -> sub -> id == G_BINARY_DIGIT) {
            NODE* newNode = initNode(3);
            if (node -> sub -> sub -> sub -> id == G_0_DIGIT)
               newNode -> id = 0;
            else
            if (node -> sub -> sub -> sub -> id == G_1_DIGIT)
               newNode -> id = 1;
            else
            if (node -> sub -> sub -> sub -> id == G_X_DIGIT)
               newNode -> id = 2;
            newNode -> next = returnNode -> next -> next;
            returnNode -> next -> next = newNode;   
         }
      } else
      if (baseNode -> id == G_SV_OCTAL_BASE) {
         if (node -> sub -> sub -> id == G_OCTAL_DIGIT) {
            if ( (node -> sub  -> sub -> sub -> id == G_X_DIGIT) |
                 (node -> sub  -> sub -> sub -> id == G_Z_DIGIT) ) {
               for (int i = 0; i < 3; i++) {
                  NODE* newNode = initNode(node -> sub  -> sub -> sub -> id - G_X_DIGIT + 2);
                  newNode -> next = returnNode -> next -> next;
                  returnNode -> next -> next = newNode;   
               }
            } else {
               unsigned oct = node -> sub -> sub -> sub -> id - G_0_DIGIT;
               //for (int i = 0; i < 3; i++) {
               for (int i = 2; i >= 0; i--) {
                  NODE* newNode = initNode((oct >> i) & 0x1);
                  newNode -> next = returnNode -> next -> next;
                  returnNode -> next -> next = newNode;   
               }
            }
         }
      } else {
         if (node -> sub -> sub -> id == G_HEX_DIGIT) {
            if ( (node -> sub -> sub -> sub -> id == G_X_DIGIT) |
                 (node -> sub -> sub -> sub -> id == G_Z_DIGIT) ) {
               for (int i = 0; i < 4; i++) {
                  NODE* newNode = initNode(node -> sub -> sub -> sub -> id - G_X_DIGIT + 2);
                  newNode -> next = returnNode -> next -> next;
                  returnNode -> next -> next = newNode;   
               }
            } else {
               unsigned hex = node -> sub -> sub -> sub -> id - G_0_DIGIT;
               if (debug) printf("hex: %x\n", hex);
               //for (int i = 0; i < 4; i++) {
               for (int i = 3; i >= 0; i--) {
                  NODE* newNode = initNode((hex >> i) & 0x1);
                  newNode -> next = returnNode -> next -> next;
                  returnNode -> next -> next = newNode;   
               }
            } 
         }
      }
      node = node -> sub -> sub -> next;
      if (node == NULL)
         break;
   }
   if (length > 0) {
      node = returnNode -> next -> next;
      while (1) {
         if (length == 1) {
            node -> next = NULL;
            break;
         }
         length -= 1;
         node = node -> next;
         if (node == NULL)
            break;
      }
   }
   if (debug) printf("--------------------- returnNode:\n");
   if (debug) printTree(returnNode);
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
// sbin2Unsigned_sub
/////////////////////////////////////////////////////////////////////////////////
unsigned sbin2Unsigned_sub (NODE* node) {
   unsigned returnVal = node -> id;
   if (node -> next != NULL)
      returnVal += 2 * sbin2Unsigned_sub(node -> next);
   return returnVal;
}
/////////////////////////////////////////////////////////////////////////////////
// sbin2Unsigned
/////////////////////////////////////////////////////////////////////////////////
unsigned sbin2Unsigned (NODE* node) {
   node = node -> next -> next;
   return sbin2Unsigned_sub(node);
}
/////////////////////////////////////////////////////////////////////////////////
// sbin2Int
/////////////////////////////////////////////////////////////////////////////////
int sbin2Int (NODE* node) {
   if (node -> id == 0) 
      return sbin2Unsigned_sub(node -> next -> next);
   else
      return 0 - sbin2Unsigned_sub(node -> next -> next);
}
/////////////////////////////////////////////////////////////////////////////////
// sbin2Bool
/////////////////////////////////////////////////////////////////////////////////
bool sbin2Bool (NODE* node) {
   node = node -> next -> next;
   while (1) {
      if (node -> id == 1)
         return true;
      if (node -> next == NULL)
         break;
      node = node -> next;
   }
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
// cleanBin
/////////////////////////////////////////////////////////////////////////////////
NODE* cleanBin (NODE* node) {
   bool debug = false;
   if (debug) printf("------------- cleanBin:\n");
   if (debug) printTree(node);
   //bool isZero = true;
   /////////////////////////////////////
   // unbound
   /////////////////////////////////////
   //if (node -> next -> id == -1) {
      NODE* tmpNode = node -> next -> next;
      NODE* lastOneNode = NULL;
      while (1) {
         if (tmpNode -> id > 0)
            lastOneNode = tmpNode;
         if (tmpNode -> next == NULL) {
            ////////////////////////////////
            // all zeros
            ////////////////////////////////
            if (lastOneNode == NULL) {
               node -> id = 0;
               /////////////////////////////////////
               // unbound
               /////////////////////////////////////
               if (node -> next -> id == -1)
                  node -> next -> next -> next = NULL;
            ////////////////////////////////
            // > 0
            ////////////////////////////////
            } else {
               /////////////////////////////////////
               // unbound
               /////////////////////////////////////
               if (node -> next -> id == -1)
               if (lastOneNode -> next != NULL) {
                  deleteTree(lastOneNode -> next);
                  lastOneNode -> next = NULL;
               }
            }
            return node;
         }
         tmpNode = tmpNode -> next;
      }
   //}
   return node;
}
/////////////////////////////////////////////////////////////////////////////////
// chopZero
/////////////////////////////////////////////////////////////////////////////////
bool chopZero (NODE* node) {
   if (node -> next == NULL) {
      if (node -> id == 0)
         return true;
      else
         return false;
   } else {
      if (chopZero(node -> next)) {
         if (node -> id == 0)
            return true;
         node -> next == NULL;
         return false;
      } else
         return false;
   }
}
/////////////////////////////////////////////////////////////////////////////////
// isZero
/////////////////////////////////////////////////////////////////////////////////
bool isZero (NODE* node) {
   if (node -> id != 0)
      return false;
   if (node -> next != NULL)
      return isZero(node -> next);
   return true;
}
/////////////////////////////////////////////////////////////////////////////////
// twosCompl
/////////////////////////////////////////////////////////////////////////////////
void twosCompl (NODE* node) {
   bool debug = false;
   unsigned var = 1; 
   // -4: 	100
   //		011
   //		  1
   //		100

   // -6: 	110
   //		001
   //		  1
   //		010
   ///////////////////////
   // id !id var res var
   //  0   1  0   1   0
   //  0   1  1   0   1
   //  1   0  0   0   0
   //  1   0  1   1   0
   while (1) {
      if (debug) printf("node: %d var: %d ", node -> id, var);
      switch (node -> id) {
         case 0: switch (var) {
                    case 0: node -> id = 1; break;
                    case 1: node -> id = 0; break;
                    case 2: node -> id = 2; var = 0; break;
                 } break;
         case 1: switch (var) {
                    case 0: node -> id = 0; break;
                    case 1: node -> id = 1; var = 0; break;
                    case 2: node -> id = 2; break;
                 } break;
         default: node -> id = 2; var = 2; break;
      }
      if (debug) printf("= %d var: %d\n", node -> id, var);
      if (node -> next == NULL)
         break;
      node = node -> next;
   }
}
/////////////////////////////////////////////////////////////////////////////////
// compareEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* compareEquation (NODE* aNode, NODE* bNode, unsigned id) {
   bool debug = false; 
   ////////////////////////////////////////////////////////////////////
   //                                      LOGICAL  CASE     WILDCARD
   // EQUAL:   check sign, unequal =>      false    false    false
   //          walk: find 2 =>             2        n/a      var = 1
   //                find match =>         var = 1  var = 1  var = 1
   //                find mismatch =>      false    false    false
   //          terminate: same length =>   true     true     true
   //                     b = 2 =>         2        false    cont.
   //                     b = 1 =>         false    false    false
   //                     b = 0 =>         cont.    cont.    cont.
   //                     b terminate =>   true     true     true
   //                     a = 2 =>         2        false    cont.
   //                     a = 1 =>         false    false    false
   //                     a = 0 =>         cont.    cont.    cont.
   //                     terminate =>     true     true     true
   //
   // INEQUAL: walk: find 2 =>             2        n/a      var = 1
   //                find match =>         var = 1  var = 1  var = 1
   //                find mismatch =>      true     true     true
   //          terminate: same length:
   //                         sameSign =>  false    false    false
   //                         !sameSign => true     true     true
   //                     b = 2 =>         2        true     cont.
   //                     b = 1 =>         true     true     true
   //                     b = 0 =>         cont.    cont.    cont.
   //                     b terminate:
   //                         sameSign =>  false    false    false
   //                         !sameSign => true     true     true
   //                     a = 2 =>         2        true     cont.
   //                     a = 1 =>         true     true     true
   //                     a = 0 =>         cont.    cont.    cont.
   //                     terminate:
   //                         sameSign =>  false    false    false
   //                         !sameSign => true     true     true
   // LESSER_EQUAL:  equal => true
   //                not equal => continue as LESSER
   // GREATER_EQUAL: equal => true
   //                not equal => continue as GREATER
   // LESSER: recall with flipped a, b using GREATER
   // GREATER: +a > +b continue
   //          +a > -b return true
   //          -a > +b return false
   //          -a > -b change to b > a as sign is not checked
   //          walk: find 2 => return 2
   //                a > b => var = 1 
   //                a == b => no change
   //                a < b => var = 0
   //          terminate: same length =>   var
   //                     b = 2 =>         2  
   //                     b = 1 =>         return false
   //                     b = 0 =>         no change
   //                     b terminate =>   var
   //                     a = 2 =>         no change
   //                     a = 1 =>         var = 1
   //                     a = 0 =>         no change
   //                     terminate =>     var
   ////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////
   // forall EQUAL: return false when sign not equal
   /////////////////////////////////////////////////////////////
   bool sameSign = aNode -> id == bNode -> id;
   if ( (id == G_OPERATOR_LOGICAL_EQUAL)    |
        (id == G_OPERATOR_CASE_EQUAL)       |
        (id == G_OPERATOR_WILDCARD_EQUAL)   ) {
      if (debug) printf("------------- compareEquation aNode:\n");
      if (debug) printTree(aNode);
      if (debug) printf("------------- compareEquation bNode:\n");
      if (debug) printTree(bNode);
      if (!sameSign) {
         NODE* returnNode = initNode(0);
         returnNode -> next = initNode(1);
         returnNode -> next -> next = initNode(0);
         return returnNode;
      }
   } else
   /////////////////////////////////////////////////////////////
   // GREATER_EQUAL, LESSER_EQUAL: return true when equal
   // otherwise turn GREATER_EQUAL => GREATER
   //                LESSER_EQUAL => LESSER
   /////////////////////////////////////////////////////////////
   if ( (id == G_OPERATOR_GREATER_EQUAL) |
        (id == G_OPERATOR_LESSER_EQUAL)  ) {
      if (debug) printf("------------- compareEquation aNode:\n");
      if (debug) printTree(aNode);
      if (debug) printf("------------- compareEquation bNode:\n");
      if (debug) printTree(bNode);
      NODE* tmpNode = compareEquation(aNode, bNode, G_OPERATOR_LOGICAL_EQUAL);
      if (sbin2Bool(tmpNode))
         return tmpNode;
      deleteTree(tmpNode);
      if (id == G_OPERATOR_GREATER_EQUAL)
         id = G_OPERATOR_GREATER;
      else
         id = G_OPERATOR_LESSER;
   }
   NODE* returnNode = initNode(0);
   returnNode -> next = initNode(1);
   NODE* endNode = returnNode -> next;
   /////////////////////////////////////////////////////////////
   // Turn LESSER into GREATER and flip sides
   /////////////////////////////////////////////////////////////
   if ( (id == G_OPERATOR_LESSER)       ) {
      NODE* cNode = aNode;
      aNode = bNode;
      bNode = cNode;
      id = G_OPERATOR_GREATER;
   } 
   /////////////////////////////////////////////////////////////
   // GREATER: +a > +b continue
   //          +a > -b return true
   //          -a > +b return false
   //          -a > -b change to b > a as sign with be skipped
   /////////////////////////////////////////////////////////////
   if (id == G_OPERATOR_GREATER) {
      // a positive
      if (aNode -> id == 0) {
         // b negative
         if (bNode -> id == 1) {
            endNode -> next = initNode(1);
            return returnNode;
         }
      } else
      // a negative
      {
         // b positive
         if (bNode -> id == 0) {
            endNode -> next = initNode(0);
            return returnNode;
         // a and b negative
         } else {
            NODE* cNode = aNode;
            aNode = bNode;
            bNode = cNode;
         }
      }
   }
   aNode = aNode -> next -> next;
   bNode = bNode -> next -> next;
   int var = 0;
   while (true) {
      ////////////////////////////////////
      // greater (lesser changed to greater)
      ////////////////////////////////////
      if (id == G_OPERATOR_GREATER) {
         if ( (aNode -> id > 1) |
              (bNode -> id > 1) ) {
            endNode -> next = initNode(2);
            return returnNode;
         } else
         // at least on greater is enough
         if (aNode -> id > bNode -> id)
            var = 1;
         // a lesser resets var
         else if (aNode -> id < bNode -> id)
            var = 0;
      } else
      ////////////////////////////////////
      // logical (in-)equal
      ////////////////////////////////////
      if ( (id == G_OPERATOR_LOGICAL_INEQUAL) |
           (id == G_OPERATOR_LOGICAL_EQUAL)     ) {
         if ( (aNode -> id > 1) |
              (bNode -> id > 1) ) {
            endNode -> next = initNode(2);
            return returnNode;
         } else
         if ( (aNode -> id == bNode -> id) )
            var = 1;
         else {
            endNode -> next = initNode(id == G_OPERATOR_LOGICAL_INEQUAL);
            return returnNode;
         }
      } else
      ////////////////////////////////////
      // case (in-)equal
      ////////////////////////////////////
      if ( (id == G_OPERATOR_CASE_INEQUAL) |
           (id == G_OPERATOR_CASE_EQUAL)     ) {
         if (aNode -> id == bNode -> id)
            var = 1;
         else {
            endNode -> next = initNode(id == G_OPERATOR_CASE_INEQUAL);
            return returnNode;
         }
      } else
      ////////////////////////////////////
      // wildcard (in-)equal
      ////////////////////////////////////
      if ( (id == G_OPERATOR_WILDCARD_INEQUAL) |
           (id == G_OPERATOR_WILDCARD_EQUAL)     ) {
         if (aNode -> id == bNode -> id)
            var = 1;
         else if (bNode -> id > 1) 
            var = 1;
         else {
            endNode -> next = initNode(id == G_OPERATOR_WILDCARD_INEQUAL);
            return returnNode;
         }
      }
      ////////////////////////////////////
      // check termination
      ////////////////////////////////////
      if (aNode -> next == NULL) {
         ////////////////////////////////////
         // end of aNode and bNode
         ////////////////////////////////////
         if (bNode -> next == NULL) {
            if ( (id == G_OPERATOR_LOGICAL_INEQUAL)  |
                 (id == G_OPERATOR_CASE_INEQUAL)     |
                 (id == G_OPERATOR_WILDCARD_INEQUAL) ) {
               if (var == 0)
                  endNode -> next = initNode(1);
               else if (!sameSign)
                  endNode -> next = initNode(1);
               else
                  endNode -> next = initNode(0);
            } else
               endNode -> next = initNode(var);
            return returnNode;
         } else {
         ////////////////////////////////////
         // end of aNode, but not bNode
         ////////////////////////////////////
            ////////////////////////////////////
            // greater
            ////////////////////////////////////
            if (id == G_OPERATOR_GREATER) {
               bNode = bNode -> next;
               while (1) {
                  if (bNode -> id > 1) {
                     endNode -> next = initNode(2);
                     return returnNode;
                  } else
                  if (bNode -> id == 1) {
                     endNode -> next = initNode(0);
                     return returnNode;
                  }
                  if (bNode -> next == NULL)
                     break;
                  bNode = bNode -> next;
               }
               endNode -> next = initNode(var);
               return returnNode;
            } else
            ////////////////////////////////////
            // logical (in-)equal: compare the rest with 0
            ////////////////////////////////////
            if ( (id == G_OPERATOR_LOGICAL_INEQUAL) |
                 (id == G_OPERATOR_LOGICAL_EQUAL)     ) {
               bNode = bNode -> next;
               while (1) {
                  if (bNode -> id > 1) {
                     endNode -> next = initNode(2);
                     return returnNode;
                  } else
                  if (bNode -> id == 1) {
                     endNode -> next = initNode(id == G_OPERATOR_LOGICAL_INEQUAL);
                     return returnNode;
                  }
                  if (bNode -> next == NULL)
                     break;
                  bNode = bNode -> next;
               }
               if ( (id == G_OPERATOR_LOGICAL_INEQUAL) &
                    (!sameSign)                        )
                  endNode -> next = initNode(1);
               else
                  endNode -> next = initNode(id == G_OPERATOR_LOGICAL_EQUAL);
               return returnNode;
            } else
            ////////////////////////////////////
            // case (in-)equal: compare the rest with 0
            ////////////////////////////////////
            if ( (id == G_OPERATOR_CASE_INEQUAL) |
                 (id == G_OPERATOR_CASE_EQUAL)     ) {
               bNode = bNode -> next;
               while (1) {
                  if (bNode -> id != 0) {
                     endNode -> next = initNode(id == G_OPERATOR_CASE_INEQUAL);
                     return returnNode;
                  }
                  if (bNode -> next == NULL)
                     break;
                  bNode = bNode -> next;
               }
               if ( (id == G_OPERATOR_CASE_INEQUAL) &
                    (!sameSign)                        )
                  endNode -> next = initNode(1);
               else
                  endNode -> next = initNode(id == G_OPERATOR_CASE_EQUAL);
               return returnNode;
            } else
            ////////////////////////////////////
            // wildcard (in-)equal: compare the rest with 0
            ////////////////////////////////////
            if ( (id == G_OPERATOR_WILDCARD_INEQUAL) |
                 (id == G_OPERATOR_WILDCARD_EQUAL)     ) {
               bNode = bNode -> next;
               while (1) {
                  if (bNode -> id > 1) { 
                  } else
                  if (bNode -> id == 1) {
                     endNode -> next = initNode(id == G_OPERATOR_WILDCARD_INEQUAL);
                     return returnNode;
                  }
                  if (bNode -> next == NULL)
                     break;
                  bNode = bNode -> next;
               }
               if ( (id == G_OPERATOR_WILDCARD_INEQUAL) &
                    (!sameSign)                        )
                  endNode -> next = initNode(1);
               else
                  endNode -> next = initNode(id == G_OPERATOR_WILDCARD_EQUAL);
               return returnNode;
            }
            return NULL;
         }
      } else {
         ////////////////////////////////////
         // end of bNode, but not aNode
         ////////////////////////////////////
         if (bNode -> next == NULL) {
            ////////////////////////////////////
            // greater
            ////////////////////////////////////
            if (id == G_OPERATOR_GREATER) {
               aNode = aNode -> next;
               while (1) {
                  // no change for X, Z
                  //if (aNode -> id > 1) {
                  //   var = 2;
                  //} else
                  if (aNode -> id == 1) {
                     var = 1;
                  }
                  if (aNode -> next == NULL)
                     break;
                  aNode = aNode -> next;
               }
               endNode -> next = initNode(var);
               return returnNode;
            } else
            ////////////////////////////////////
            // logical (in-)equal: compare the rest with 0
            ////////////////////////////////////
            if ( (id == G_OPERATOR_LOGICAL_INEQUAL) |
                 (id == G_OPERATOR_LOGICAL_EQUAL)     ) {
               aNode = aNode -> next;
               while (1) {
                  if (aNode -> id > 1) {
                     endNode -> next = initNode(2);
                     return returnNode;
                  } else
                  if (aNode -> id == 1) {
                     endNode -> next = initNode(id == G_OPERATOR_LOGICAL_INEQUAL);
                     return returnNode;
                  }
                  if (aNode -> next == NULL)
                     break;
                  aNode = aNode -> next;
               }
               if ( (id == G_OPERATOR_LOGICAL_INEQUAL) &
                    (!sameSign)                        )
                  endNode -> next = initNode(1);
               else
                  endNode -> next = initNode(id == G_OPERATOR_LOGICAL_EQUAL);
               return returnNode;
            } else
            ////////////////////////////////////
            // case (in-)equal: compare the rest with 0
            ////////////////////////////////////
            if ( (id == G_OPERATOR_CASE_INEQUAL) |
                 (id == G_OPERATOR_CASE_EQUAL)     ) {
               aNode = aNode -> next;
               while (1) {
                  if (aNode -> id != 0) {
                     endNode -> next = initNode(id == G_OPERATOR_CASE_INEQUAL);
                     return returnNode;
                  }
                  if (aNode -> next == NULL)
                     break;
                  aNode = aNode -> next;
               }
               if ( (id == G_OPERATOR_CASE_INEQUAL) &
                    (!sameSign)                        )
                  endNode -> next = initNode(1);
               else
                  endNode -> next = initNode(id == G_OPERATOR_CASE_EQUAL);
               return returnNode;
            } else
            ////////////////////////////////////
            // wildcard (in-)equal: compare the rest with 0
            ////////////////////////////////////
            if ( (id == G_OPERATOR_WILDCARD_INEQUAL) |
                 (id == G_OPERATOR_WILDCARD_EQUAL)     ) {
               aNode = aNode -> next;
               while (1) {
                  // b is 0, so no wildcards
                  //if (aNode -> id > 1) { 
                  //} else
                  if (aNode -> id == 1) {
                     endNode -> next = initNode(id == G_OPERATOR_WILDCARD_INEQUAL);
                     return returnNode;
                  }
                  if (aNode -> next == NULL)
                     break;
                  aNode = aNode -> next;
               }
               if ( (id == G_OPERATOR_WILDCARD_INEQUAL) &
                    (!sameSign)                        )
                  endNode -> next = initNode(1);
               else
                  endNode -> next = initNode(id == G_OPERATOR_WILDCARD_EQUAL);
               return returnNode;
            }
            return NULL;
         } 
      }
      aNode = aNode -> next;
      bNode = bNode -> next;
   }
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
// shiftEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* shiftEquation (NODE* aNode, NODE* bNode, unsigned id) {
   bool debug = false;
   if (bNode -> id == 1) {
      printf("ERR.SOLVE.SHIFT.NEGATIVE_SHIFT_AMOUNT\n");
      exit(-1);
   }
   if ( (id == G_OPERATOR_ASR) |
        (id == G_OPERATOR_LSR) ) {
      ///////////////////////////////////////////////
      // ASR on unsigned number with undefined length not defined
      ///////////////////////////////////////////////
      if ( (id == G_OPERATOR_ASR)          &
           (aNode -> next -> id == -1)     &
           (aNode -> id == 0)              ) {
         printf("ERR.SOLVE.ASR.UNDEFINED_LENGTH\n");
         exit(-1);
      }
      NODE* returnNode = copyTree(aNode);
      NODE* endNode = returnNode -> next -> next;
      if (returnNode -> next -> id != -1)
      while (1) {
         if (endNode -> next == NULL) {
            break;
         }
         endNode = endNode -> next;
      }
      unsigned shift = sbin2Unsigned(bNode);
      if (debug) printf("--------------------------------- shift by %d\n", shift);
      if (debug) printTree(returnNode);
      NODE* tmpNode = returnNode -> next;
      for (int n = 0; n < shift; n++) {
         if (tmpNode -> next == NULL) {
            break;
         }
         tmpNode -> next = tmpNode -> next -> next;
      }
      // Wikipedia: The Verilog arithmetic right shift operator only actually performs an 
      // arithmetic shift if the first operand is signed. If the first operand is unsigned, 
      // the operator actually performs a logical right shift.
      // Here: asr performed when length defined.
      //if  ( ( (id == G_OPERATOR_ASR)      & 
      //        (aNode -> id == 1)          ) |
      //      ( (id == G_OPERATOR_ASR)      &
      //        (aNode -> next -> id != -1) ) ) {
      if (id == G_OPERATOR_ASR) {
         unsigned newBit = endNode -> id;
         endNode = returnNode -> next -> next;
         while (1) {
            if (endNode -> next == NULL) {
               break;
            }
            endNode = endNode -> next;
         }
         for (int n = 0; n < shift; n++) {
            endNode -> next = initNode(newBit);
            endNode = endNode -> next;
         }
       }
      if (debug) printf("--------------------------------- return:\n");
      if (debug) printTree(returnNode);
      return cleanBin(returnNode);
   } else
   if ( (id == G_OPERATOR_ASL) |
        (id == G_OPERATOR_LSL) ) {
      unsigned shift = sbin2Unsigned(bNode);
      NODE* returnNode = copyTree(aNode);
      if (debug) printf("--------------------------------- shift by %d\n", shift);
      if (debug) printTree(returnNode);
      for (int n = 0; n < shift; n++) {
         NODE* newNode = initNode(0);
         newNode -> next = returnNode -> next -> next;
         returnNode -> next -> next = newNode;
      }
      if (debug) printf("--------------------------------- return:\n");
      if (debug) printTree(returnNode);
      return returnNode;
   }
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
// combEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* combEquation (NODE* aNode, 
                    NODE* bNode, 
                    unsigned id) {
   bool debug = false;
   NODE* returnNode = initNode(0);
   bool aInv = false;
   bool bInv = false;
   //////////////////////////////////
   // new sign
   //////////////////////////////////
   if (aNode -> id == 0) {
   } else {
      if (debug) printf("----------------- given aNode:\n");		
      if (debug) printTree(aNode);
      twosCompl(aNode -> next -> next);
      if (debug) printf("----------------- twosCompl aNode:\n");
      if (debug) printTree(aNode);
      aInv = true;
      //exit(-1);
      if (id == G_OPERATOR_AND)
      if (bNode -> id == 1)
         returnNode -> id = 1;
      if (id == G_OPERATOR_OR)
         returnNode -> id = 1;
      if (id == G_OPERATOR_XOR)
      if (bNode -> id == 0)
         returnNode -> id = 1;
      if (id == G_OPERATOR_NXOR)
      if (bNode -> id == 1)
         returnNode -> id = 1;
   }
   if (bNode -> id == 0) {
   } else {
      if (debug) printf("----------------- given bNode:\n");
      if (debug) printTree(bNode);
      twosCompl(bNode -> next -> next);
      if (debug) printf("----------------- twosCompl bNode:\n");
      if (debug) printTree(bNode);
      bInv = true;
      if (id == G_OPERATOR_OR)
         returnNode -> id = 1;
      if (id == G_OPERATOR_XOR)
      if (aNode -> id == 0)
         returnNode -> id = 1;
   }
   //////////////////////////////////
   // new length
   //////////////////////////////////
   if ( (aNode -> next -> id == -1) |
        (bNode -> next -> id == -1) )
      returnNode -> next = initNode(-1);
   else
      returnNode -> next = initNode(std::max(aNode -> next -> id, bNode -> next -> id));
   //////////////////////////////////
   // bits
   //////////////////////////////////
   NODE* endNode = returnNode -> next;
   aNode = aNode -> next -> next;
   bNode = bNode -> next -> next;
   while (true) {
      unsigned result = 0;
      unsigned a = aNode -> id;
      unsigned b = bNode -> id;
      if (id == G_OPERATOR_AND) {
         if (a == 0) result = 0;
         else if (b == 0) result = 0;
         else if ((a == 1) & (b == 1)) result = 1;
         else result = 2;
      } else
      if (id == G_OPERATOR_OR) {
         if (a == 1) result = 1;
         else if (b == 1) result = 1;
         else if ((a == 0) & (b == 0)) result = 0;
         else result = 2;
      } else
      if (id == G_OPERATOR_XOR) {
         if ((a >= 2) | (b >= 2)) result = 2;
         else result = a ^ b;
      } else
      if (id == G_OPERATOR_NXOR) {
         if ((a >= 2) | (b >= 2)) result = 2;
         else result = (!(a ^ b)) & 0x1;
      }
      if (debug) printf("comb %d %d = %d\n", a, b, result);
      endNode -> next = initNode(result);
      endNode = endNode -> next;
      ////////////////////////////////////
      // check termination
      ////////////////////////////////////
      if (aNode -> next == NULL) {
         ////////////////////////////////////
         // end of aNode and bNode
         ////////////////////////////////////
         if (bNode -> next == NULL) {
            //return returnNode;
         } else {
         ////////////////////////////////////
         // end of aNode, but not bNode
         //////////////////////////////////// 
            if (debug) printf("comb -\n");
            a = 0;
            if (aInv)
               a = 1;
            bNode = bNode -> next;
            while (1) {
               unsigned result = 0;
               b = bNode -> id;
               if (id == G_OPERATOR_AND) {
                  if (a == 0) result = 0;
                  else if (b == 0) result = 0;
                  else if ((a == 1) & (b == 1)) result = 1;
                  else result = 2;
               } else
               if (id == G_OPERATOR_OR) {
                  if (a == 1) result = 1;
                  else if (b == 1) result = 1;
                  else if ((a == 0) & (b == 0)) result = 0;
                  else result = 2;
               } else
               if (id == G_OPERATOR_XOR) {
                  if ((a >= 2) | (b >= 2)) result = 2;
                  else result = a ^ b;
               } else
               if (id == G_OPERATOR_NXOR) {
                  if ((a >= 2) | (b >= 2)) result = 2;
                  else result = (!(a ^ b)) & 0x1;
               }
               endNode -> next = initNode(result);
               endNode = endNode -> next;
               if (debug) printf("comb %d %d = %d\n", a, b, result);
               if (aNode -> next == NULL) {
                  break;
               }
               bNode = bNode -> next;
            }
         }
      } else {
         ////////////////////////////////////
         // end of bNode, but not aNode
         ////////////////////////////////////
         if (bNode -> next == NULL) {
            if (debug) printf("comb   -\n");
            b = 0;
            if (bInv)
               b = 1;
            aNode = aNode -> next;
            while (1) {
               unsigned result = 0;
               a = aNode -> id;
               if (id == G_OPERATOR_AND) {
                  if (a == 0) result = 0;
                  else if (b == 0) result = 0;
                  else if ((a == 1) & (b == 1)) result = 1;
                  else result = 2;
               } else
               if (id == G_OPERATOR_OR) {
                  if (a == 1) result = 1;
                  else if (b == 1) result = 1;
                  else if ((a == 0) & (b == 0)) result = 0;
                  else result = 2;
               } else
               if (id == G_OPERATOR_XOR) {
                  if ((a >= 2) | (b >= 2)) result = 2;
                  else result = a ^ b;
               } else
               if (id == G_OPERATOR_NXOR) {
                  if ((a >= 2) | (b >= 2)) result = 2;
                  else result = (!(a ^ b)) & 0x1;
               }
               endNode -> next = initNode(result);
               endNode = endNode -> next;
               if (debug) printf("comb %d %d = %d\n", a, b, result);
               if (aNode -> next == NULL) {
                  break;
               }
               aNode = aNode -> next;
            }
         } 
      }
      if ( (aNode -> next == NULL) &
           (bNode -> next == NULL) ) {
         NODE* resNode = returnNode -> next;
         if (debug) printf("resNode -> id %d\n", resNode -> id); 
         if (resNode -> id != -1)
            return returnNode;
         resNode = resNode -> next;
         ///////////////////////////
         // check if zero 
         ///////////////////////////
         bool isZero = true;
         bool isAllOne = true;
         if (resNode != NULL) {
            while (1) {
               if (resNode -> id != 0) {
                  isZero = false;
               }
               if (resNode -> id != 1) {
                  isAllOne = false;
               }
               if (resNode -> next == NULL)
                  break;
               resNode = resNode -> next;
            }
         }
         if (debug) printf("isZero %d\n", isZero); 
         if (debug) printf("isAllOne %d\n", isAllOne); 
         if (debug) printf("returnNode -> next -> id %d\n", returnNode -> next -> id); 
         if (debug) printf("aInv == bInv %d\n", aInv == bInv); 
         if (isZero) {
            if (returnNode -> id == 1) {
               resNode -> next = initNode(1);
            }
         } else
         //////////////////////////////////////////
         // special case NXOR
         //////////////////////////////////////////
         if ( (isAllOne)                      & 
              (returnNode -> next -> id == -1) &
              (id == G_OPERATOR_NXOR)         &
              (aInv == bInv)    ) {
            returnNode -> id = 1;
            returnNode -> next -> next = initNode(1);
         } else
         if ( returnNode -> id == 1) {
            if (debug) printf("----------------- given returnNode:\n");
            if (debug) printTree(returnNode);
            twosCompl(returnNode -> next -> next);
            if (debug) printf("----------------- twosCompl returnNode:\n");
            if (debug) printTree(returnNode);
         }
         return cleanBin(returnNode);
      }
      aNode = aNode -> next;
      bNode = bNode -> next;
   }
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
// logicalEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* logicalEquation (NODE* aNode, 
                       NODE* bNode, 
                       unsigned id) {
   bool debug = false;
   int var = 0;
   NODE* returnNode = initNode(0);
   returnNode -> next = initNode(1);
   if (id == G_OPERATOR_LAND) {
      if (sbin2Bool(aNode) & sbin2Bool(bNode))
         returnNode -> next -> next = initNode(1);
      else
         returnNode -> next -> next = initNode(0);
   } else
   if (id == G_OPERATOR_LOR) {
      if (sbin2Bool(aNode) | sbin2Bool(bNode))
         returnNode -> next -> next = initNode(1);
      else
         returnNode -> next -> next = initNode(0);
   } else
      returnNode -> next -> next = initNode(2);
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
// plusEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* plusEquation (NODE* aNode, 
                    NODE* bNode) {
   bool debug = false;
   int var = 0;
   if ( (aNode -> id == 0) &
        (bNode -> id == 1) ) {
      bNode -> id = 0;
      return minusEquation(aNode, bNode);
   } else
   if ( (aNode -> id == 1) &
        (bNode -> id == 0) ) {
      aNode -> id = 0;
      return minusEquation(bNode, aNode);
   }
   NODE* returnNode = initNode(aNode -> id);
   returnNode -> next = initNode(-1);
   NODE* endNode = NULL;
   aNode = aNode -> next -> next;
   bNode = bNode -> next -> next;
   while (true) {
      unsigned result = 0;
      if (debug) printf("plus %d %d %d ", aNode -> id, bNode -> id, var);
      switch (aNode -> id) {
         case 0 : switch (bNode -> id) {
                     case 0: switch (var) {
                                case 0: break;
                                case 1: result = 1; var = 0; break;
                                case 2: result = 2; var = 0; break;
                             } break;
                     case 1: switch (var) {
                                case 0: result = 1; break;
                                case 1: var = 1; break;
                                case 2: result = 2; break;
                             } break;
                     default: switch (var) {
                                case 0: result = 2; break;
                                case 1: result = 2; var = 2; break;
                                case 2: result = 2; break;
                             } break;
                  } break;
         case 1 : switch (bNode -> id) {
                     case 0: switch (var) {
                                case 0: result = 1; break;
                                case 1: break;
                                case 2: result = 2; var = 0; break;
                             } break;
                     case 1: switch (var) {
                                case 0: var = 1; break;
                                case 1: result = 1; var = 1; break;
                                case 2: result = 2; var = 1; break;
                             } break;
                     default: switch (var) {
                                case 0: result = 2; var = 2; break;
                                case 1: result = 2; var = 1; break;
                                case 2: result = 2; break;
                             } break;
                  } break;
         default : result = 2; 
                   switch (bNode -> id) {
                     case 0: switch (var) {
                                case 0: break;
                                case 1: var = 2; break;
                                case 2: break;
                             } break;
                     case 1: switch (var) {
                                case 0: var = 2; break;
                                case 1: var = 1; break;
                                case 2: var = 2; break;
                             } break;
                     default: var = 2;
                  } break;
      }
      if (debug) printf(" = %d %d\n", result, var);
      if (endNode == NULL) {
         endNode = initNode(result);
         returnNode -> next -> next = endNode;
      } else {
         endNode -> next = initNode(result);
         endNode = endNode -> next;
      }
      ////////////////////////////////////
      // check termination
      ////////////////////////////////////
      if (aNode -> next == NULL) {
         ////////////////////////////////////
         // end of aNode and bNode
         ////////////////////////////////////
         if (bNode -> next == NULL) {
            if (var > 0)
               endNode -> next = initNode(var);
            break;
         } else {
         ////////////////////////////////////
         // end of aNode, but not bNode
         ////////////////////////////////////
            bNode = bNode -> next;
            while (1) {
               result = 0;
               if (debug) printf("plus %d %d %d ", 0, bNode -> id, var);
               switch (bNode -> id) {
                     case 0: switch (var) {
                                case 0: break;
                                case 1: result = 1; var = 0; break;
                                case 2: result = 2; var = 0; break;
                             } break;
                     case 1: switch (var) {
                                case 0: result = 1; break;
                                case 1: var = 1; break;
                                case 2: result = 2; break;
                             } break;
                     default: switch (var) {
                                case 0: result = 2; break;
                                case 1: result = 2; var = 2; break;
                                case 2: result = 2; break;
                             } break;
               }
               if (debug) printf(" = %d %d\n", result, var);
               endNode -> next = initNode(result);
               endNode = endNode -> next;
               if (bNode -> next == NULL) {
                  if (var > 0)
                     endNode -> next = initNode(var);
                  break;
               }
               bNode = bNode -> next;
            }
            break;
         }
      } else {
         ////////////////////////////////////
         // end of bNode, but not aNode
         ////////////////////////////////////
         if (bNode -> next == NULL) {
            aNode = aNode -> next;
            while (1) {
               result = 0;
               if (debug) printf("plus %d %d %d ", 0, aNode -> id, var);
               switch (aNode -> id) {
                     case 0: switch (var) {
                                case 0: break;
                                case 1: result = 1; var = 0; break;
                                case 2: result = 2; var = 0; break;
                             } break;
                     case 1: switch (var) {
                                case 0: result = 1; break;
                                case 1: var = 1; break;
                                case 2: result = 2; break;
                             } break;
                     default: switch (var) {
                                case 0: result = 2; break;
                                case 1: result = 2; var = 2; break;
                                case 2: result = 2; break;
                             } break;
               }
               if (debug) printf(" = %d %d\n", result, var);
               endNode -> next = initNode(result);
               endNode = endNode -> next;
               if (aNode -> next == NULL) {
                  if (var > 0)
                     endNode -> next = initNode(var);
                  break;
               }
               aNode = aNode -> next;
            }
            break;
         } 
      }
      aNode = aNode -> next;
      bNode = bNode -> next;
   }
   if (debug) printf("--------------------- returnNode:\n");
   if (debug) printTree(returnNode);
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// minusEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* minusEquation (NODE* aNode, 
                     NODE* bNode) {
   bool debug = false;
   if (debug) printf("--------------------- minus aNode:\n");
   if (debug) printTree(aNode);
   if (debug) printf("--------------------- minus bNode:\n");
   if (debug) printTree(bNode);
   /////////////////////////////////////////
   //  a - -b = a + b
   /////////////////////////////////////////
   if ( (aNode -> id == 0) &
        (bNode -> id == 1) ) {
      bNode -> id = 0;
      return plusEquation(aNode, bNode);
   } else
   /////////////////////////////////////////
   //  -a - b = -a + -b
   /////////////////////////////////////////
   if ( (aNode -> id == 1) &
        (bNode -> id == 0) ) {
      bNode -> id = 1; // result is negative
      return plusEquation(aNode, bNode);
   } else   
   /////////////////////////////////////////
   //  a - b = 
   /////////////////////////////////////////
   if ( (aNode -> id == 0) &
        (bNode -> id == 0) ) {
      NODE* tmpNode = compareEquation(bNode, aNode, G_OPERATOR_GREATER);
      if (debug) printf("--------------------- tmpNode:\n");
      if (debug) printTree(tmpNode);
      /////////////////////////////////////////
      // 3 - 5
      // a - b (a < b) = -(b - a)
      /////////////////////////////////////////
      if (sbin2Bool(tmpNode)) {
         if (debug) printf("is greater\n");
         deleteTree(tmpNode);
         NODE* returnNode = minusEquation(bNode, aNode);
         returnNode -> id = 1;
         return cleanBin(returnNode);
      }
      deleteTree(tmpNode);
   } else   
   /////////////////////////////////////////
   //  -a - -b = 
   /////////////////////////////////////////
   if ( (aNode -> id == 1) &
        (bNode -> id == 1) ) {
      aNode -> id = 0;
      bNode -> id = 0;
      NODE* tmpNode = compareEquation(bNode, aNode, G_OPERATOR_GREATER);
      /////////////////////////////////////////
      //  -2 - -5 = 5 - 2
      /////////////////////////////////////////
      if (sbin2Bool(tmpNode)) {
         deleteTree(tmpNode);
         return minusEquation(bNode, aNode);
      } else {
      /////////////////////////////////////////
      //  -5 - -2 = -3
      /////////////////////////////////////////
         deleteTree(tmpNode);
         NODE* returnNode = minusEquation(aNode, bNode);
         returnNode -> id = 1;
         return cleanBin(returnNode);
      }
   }
   
   NODE* returnNode = initNode(0);
   returnNode -> next = initNode(-1);
   NODE* endNode = NULL;
   aNode = aNode -> next -> next;
   bNode = bNode -> next -> next;
   int var = 0;
   while (true) {
      unsigned result = 0;
      if (debug) printf("minus %d %d %d ", aNode -> id, bNode -> id, var);
      switch (aNode -> id) {
         case 0 : switch (bNode -> id) {
                     case 0: switch (var) {
                                case 0: break;
                                case 1: result = 1; break;
                                case 2: result = 2; break;
                             } break;
                     case 1: switch (var) {
                                case 0: result = 1; var = 1; break;
                                case 1: break;
                                case 2: result = 2; var = 1; break;
                             } break;
                     default: switch (var) {
                                case 0: result = 2; var = 2; break;
                                case 1: result = 2; break;
                                case 2: result = 2; break;
                             } break;
                  } break;
         case 1 : switch (bNode -> id) {
                     case 0: switch (var) {
                                case 0: result = 1; break;
                                case 1: var = 0; break;
                                case 2: result = 2; var = 0; break;
                             } break;
                     case 1: switch (var) {
                                case 0: break;
                                case 1: result = 1; break;
                                case 2: result = 2; break;
                             } break;
                     default: switch (var) {
                                case 0: result = 2; break;
                                case 1: result = 2; var = 2; break;
                                case 2: result = 2; break;
                             } break;
                  } break;
         default : result = 2; 
                   var = 2;
                   break;
      }
      if (debug) printf(" = %d %d\n", result, var);
      if (endNode == NULL) {
         endNode = initNode(result);
         returnNode -> next -> next = endNode;
      } else {
         endNode -> next = initNode(result);
         endNode = endNode -> next;
      }
      ////////////////////////////////////
      // check termination
      ////////////////////////////////////
      if (aNode -> next == NULL) {
         ////////////////////////////////////
         // end of aNode and bNode
         ////////////////////////////////////
         if (bNode -> next == NULL) {
            if (var == 1)
               endNode -> next = initNode(1);
            break;
         } else {
         ////////////////////////////////////
         // end of aNode, but not bNode
         ////////////////////////////////////
            bNode = bNode -> next;
            while (1) {
               result = 0;
               if (debug) printf("minus %d %d %d ", 0, bNode -> id, var);
               switch (bNode -> id) {
                     case 0: switch (var) {
                                case 0: break;
                                case 1: result = 1; break;
                                case 2: result = 2; break;
                             } break;
                     case 1: switch (var) {
                                case 0: result = 1; var = 1; break;
                                case 1: break;
                                case 2: result = 2; var = 1; break;
                             } break;
                     default: switch (var) {
                                case 0: result = 2; var = 2; break;
                                case 1: result = 2; break;
                                case 2: result = 2; break;
                             } break;
               }
               if (debug) printf(" = %d %d\n", result, var);
               endNode -> next = initNode(result);
               endNode = endNode -> next;
               if (bNode -> next == NULL) {
                  if (var == 1)
                     endNode -> next = initNode(1);
                  break;
               }
               bNode = bNode -> next;
            }
            break;
         }
      } else {
         ////////////////////////////////////
         // end of bNode, but not aNode
         ////////////////////////////////////
         if (bNode -> next == NULL) {
            aNode = aNode -> next;
            while (1) {
               result = 0;
               if (debug) printf("minus %d %d %d ", aNode -> id, 0, var);
               switch (aNode -> id) {
                  case 0 : switch (var) {
                                case 0: break;
                                case 1: result = 1; break;
                                case 2: result = 2; break;
                             } break;
                  case 1 : switch (var) {
                                case 0: result = 1; break;
                                case 1: var = 0; break;
                                case 2: result = 2; var = 0; break;
                             } break;
                  default : result = 2; 
                            var = 2;
                            break;
               }
               if (debug) printf(" = %d %d\n", result, var);
               endNode -> next = initNode(result);
               endNode = endNode -> next;
               if (aNode -> next == NULL) {
                  if (var == 1)
                     endNode -> next = initNode(1);
                  break;
               }
               aNode = aNode -> next;
            }
            break;
         } 
      }
      aNode = aNode -> next;
      bNode = bNode -> next;
   }
   if (debug) printf("--------------------- returnNode:\n");
   if (debug) printTree(returnNode);
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// multEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* multEquation (NODE* aNode, 
                    NODE* bNode) {
   bool debug = false;
   if (debug) printf("--------------------- mul aNode:\n");
   if (debug) printTree(aNode);
   if (debug) printf("--------------------- mul bNode:\n");
   if (debug) printTree(bNode);
   bool retNeg = false;
   if (aNode -> id != bNode -> id)
      retNeg = true;
   NODE* returnNode = initNode(0);
   returnNode -> next = initNode(-1);
   if ( (aNode -> next -> id != -1) &
        (bNode -> next -> id != -1) )
      returnNode -> next -> id = aNode -> next -> id + bNode -> next -> id;
   returnNode -> next -> next = initNode(0);
   aNode = aNode -> next -> next;
   bNode -> id = 0;
   if (debug) printf("mul start\n");
   if (debug) printTree(returnNode);
   while (true) {
      if (aNode -> id == 1) {
         returnNode = plusEquation(returnNode, bNode);
         if (debug) printf("mul\n");
         if (debug) printTree(returnNode);
      }
      ////////////////////////////////////
      // check termination
      ////////////////////////////////////
      if (aNode -> next == NULL) {
         break;
      }
      aNode = aNode -> next;
      if (debug) printf("lsl start\n"); 
      if (debug) printTree(bNode);
      NODE* newNode = initNode(0);
      newNode -> next = bNode -> next -> next;
      bNode -> next -> next = newNode;
      if (debug) printf("lsl end\n"); 
      if (debug) printTree(bNode);
   }
   if (retNeg)
      returnNode -> id = 1;
   if (debug) printf("--------------------- returnNode:\n");
   if (debug) printTree(returnNode);
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// powerEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* powerEquation (NODE* aNode, 
                     NODE* bNode) {
   bool debug = false;
   if (debug) printf("--------------------- power aNode:\n");
   if (debug) printTree(aNode);
   if (debug) printf("--------------------- power bNode:\n");
   if (debug) printTree(bNode);
   if (bNode -> id == 1) {
      printf("ERR.SOLVE.POWER.POWER_OF_NEGATIVE_NUMBER\n");
      exit(-1);
   }
   unsigned power = sbin2Unsigned(bNode);
   if (power == 0) {
      NODE* returnNode = initNode(0);
      returnNode -> next = initNode(-1);
      returnNode -> next -> next = initNode(1);
      return returnNode;
   }

   NODE* returnNode = copyTree(aNode);
   for (int n = 1; n < power; n++) {
      returnNode = multEquation(returnNode, copyTree(aNode));
      if (debug) printf("--------------------- power (tmp) returnNode:\n");
      if (debug) printTree(returnNode);
   }
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// divModEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* divModEquation (NODE* aNode, NODE* bNode, unsigned id) {
   bool debug = false;
   // The integer division shall truncate any fractional part toward zero. 
   // For the division or modulus operators, if the second operand is a zero, 
   // then the entire result value shall be x. The modulus operator (for example,
   // a % b) gives the remainder when the first operand is divided by the second 
   // and thus is zero when b divides a exactly. 
   // The result of a modulus operation shall take the sign of the first operand.
   if (debug) printf("--------------------- divMod aNode:\n");
   if (debug) printTree(aNode);
   if (debug) printf("--------------------- divMod bNode:\n");
   if (debug) printTree(bNode); 
   if (isZero(bNode -> next -> next)) {
      NODE* returnNode = initNode(0);
      returnNode -> next = initNode(-1);
      returnNode -> next -> next = initNode(2);
      return returnNode;
   }
   bool retNeg = false;
   if (aNode -> id != bNode -> id)
      retNeg = true;
   aNode -> id = 0;
   bNode -> id = 0;
   unsigned shift = 0;
   while (1) {
      NODE* tmpNode = compareEquation(aNode, bNode, G_OPERATOR_GREATER_EQUAL);
      if (!sbin2Bool(tmpNode)) {
         bNode -> next -> next = bNode -> next -> next -> next;
         break;
      }
      NODE* newNode = initNode(0);
      newNode -> next = bNode -> next -> next;
      bNode -> next -> next = newNode;
      shift += 1;
   }
   if (debug) printf("shift: %d\n", shift);
   if (debug) printf("--------------------- divMod bNode (post shift):\n");
   if (debug) printTree(bNode); 
   NODE* returnNode = initNode(0);
   if (shift == 0) {
      returnNode -> next = initNode(1);
      returnNode -> next -> next = initNode(0);
      return returnNode;
   }
   if (retNeg)
      returnNode -> id = 1;
   returnNode -> next = initNode(shift); 
   for (int i = 0; i < shift; i++) {
      if (debug) printf("--------------------- divMod bNode (pre dec):\n");
      if (debug) printTree(bNode); 
      NODE* tmpNode = compareEquation(aNode, bNode, G_OPERATOR_GREATER_EQUAL);
      NODE* newNode = initNode(0);
      if (sbin2Bool(tmpNode)) {
         newNode -> id = 1;
         aNode = minusEquation(aNode, bNode);
      }
      if (id == G_OPERATOR_DIV) {
         newNode -> next = returnNode -> next -> next;
         returnNode -> next -> next = newNode;
      }
      bNode -> next -> next = bNode -> next -> next -> next;
      if (debug) printf("--------------------- divMod aNode (post shift):\n");
      if (debug) printTree(aNode); 
   }
   if (id == G_OPERATOR_MOD) {
      aNode -> id = returnNode -> id;
      return cleanBin(aNode);
   }
   if (debug) printf("--------------------- returnNode:\n");
   if (debug) printTree(returnNode);
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// incDecEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* incDecEquation (NODE* aNode, 
                      unsigned id) {
   bool debug = false;
   if (aNode -> id == 1) {
      aNode -> id = 0;
      NODE* returnNode = NULL;
      if (id == G_INC_OPERATOR)
        returnNode = incDecEquation(aNode, G_DEC_OPERATOR);
      else
        returnNode = incDecEquation(aNode, G_INC_OPERATOR);
      returnNode -> id = 1;
      return cleanBin(returnNode);
   }
   int var = 1;
   NODE* returnNode = initNode(0);
   returnNode -> next = initNode(aNode -> next -> id);
   NODE* endNode = returnNode -> next;
   aNode = aNode -> next -> next;
   while (true) {
      if (id == G_INC_OPERATOR) {
         unsigned result = aNode -> id + var;
         if (debug) printf("plus %d %d = %d\n", aNode -> id, var, result);
         endNode -> next = initNode(result % 2);
         if (result > 1)
            var = 1;
         else
            var = 0;
      } else {
         unsigned result = 0;
         if (debug) printf("minus %d %d %d ", aNode -> id, 0, var);
         switch (aNode -> id) {
                  case 0 : switch (var) {
                                case 0: break;
                                case 1: result = 1; break;
                                case 2: result = 2; break;
                             } break;
                  case 1 : switch (var) {
                                case 0: result = 1; break;
                                case 1: var = 0; break;
                                case 2: result = 2; var = 0; break;
                             } break;
                  default : result = 2; 
                            var = 2;
                            break;
               }
         if (debug) printf(" = %d %d\n", result, var);
         endNode -> next = initNode(result);
      }
      endNode = endNode -> next;
      ////////////////////////////////////
      // check termination
      ////////////////////////////////////
      if (aNode -> next == NULL) {
         if (var == 1)
            endNode -> next = initNode(1);
         break;
      }
      aNode = aNode -> next;
   }
   if (debug) printf("--------------------- returnNode:\n");
   if (debug) printTree(returnNode);
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// decEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* decEquation (NODE* aNode) {
   bool debug = false;
   int var = 1;
   NODE* returnNode = initNode(0);
   returnNode -> next = initNode(aNode -> next -> id);
   NODE* endNode = returnNode -> next;
   aNode = aNode -> next -> next;
   while (true) {
      unsigned result = 0;
      if (debug) printf("minus %d %d %d ", aNode -> id, 0, var);
      switch (aNode -> id) {
               case 0 : switch (var) {
                             case 0: break;
                             case 1: result = 1; break;
                             case 2: result = 2; break;
                          } break;
               case 1 : switch (var) {
                             case 0: result = 1; break;
                             case 1: var = 0; break;
                             case 2: result = 2; var = 0; break;
                          } break;
               default : result = 2; 
                         var = 2;
                         break;
            }
      if (debug) printf(" = %d %d\n", result, var);
      endNode -> next = initNode(result);
      endNode = endNode -> next;
      ////////////////////////////////////
      // check termination
      ////////////////////////////////////
      if (aNode -> next == NULL) {
         break;
      }
      aNode = aNode -> next;
   }
   if (debug) printf("--------------------- returnNode:\n");
   if (debug) printTree(returnNode);
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// concatEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* concatEquation (NODE* node) {
   bool debug = false;
   if (debug) printf("--------------------- concat given node:\n");
   if (debug) printTree(node);
   NODE* returnNode = NULL;
   while (true) {
      NODE* tmpNode = solveEquation(node -> sub);
      if (debug) printf("--------------------- concat tmpNode:\n");
      if (debug) printTree(tmpNode);   
      if (tmpNode -> next -> id == -1) {
         printf("ERR.SOLVE.CONCATENATION.UNDEFINED_LENGTH\n");
         exit(-1);
      }
      if (returnNode == NULL) {
         returnNode = tmpNode;
      } else {
         NODE* endNode = tmpNode -> next -> next;
         unsigned cnt = 0;
         while (1) {
            cnt += 1;
            if (endNode -> next == NULL)
               break;
            endNode = endNode -> next;
         }
         endNode -> next = returnNode -> next -> next;
         returnNode -> next -> next = tmpNode -> next -> next;
         returnNode -> next -> id = cnt + returnNode -> next -> id;
      }
      if (node -> next == NULL)
         break;
      node = node -> next;
   }
   if (debug) printf("--------------------- returnNode:\n");
   if (debug) printTree(returnNode);
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// unaryConstant2SBin
/////////////////////////////////////////////////////////////////////////////////
NODE* unaryConstant2SBin (NODE* node) {
   bool debug = false;
   NODE* returnNode = NULL;
   if (node -> sub -> id == G_OPERATOR_EXCLAMATION) {
      NODE* tmpNode = solveEquation(node -> next);
      returnNode = initNode(0);
      returnNode -> next = initNode(1);
      if (sbin2Bool(tmpNode))
         returnNode -> next -> next = initNode(0);
      else
         returnNode -> next -> next = initNode(1);
      if (debug) printf("----------------- returnNode:\n");
      if (debug) printTree(returnNode);
   } else
   if (node -> sub -> id == G_OPERATOR_TILDE) {
      NODE* tmpNode = solveEquation(node -> next);
      if (debug) printf("----------------- tmpNode ~:\n");
      if (debug) printTree(tmpNode);
      if (tmpNode -> next -> id != -1) {
         returnNode = initNode(0);
         returnNode -> next = initNode(tmpNode -> next -> id);
         returnNode -> next -> next = copyTree(tmpNode -> next -> next);
         NODE* ptrNode = returnNode -> next -> next;
         while (1) {
            if (ptrNode -> id == 0) {
               ptrNode -> id = 1;
            } else 
            if (ptrNode -> id == 1) {
               ptrNode -> id = 0;
            } else
               ptrNode -> id = 2;
            if (ptrNode -> next == NULL)
               break;
            ptrNode = ptrNode -> next;
         }
      } else {
         tmpNode = incDecEquation(tmpNode, G_INC_OPERATOR);
         if (tmpNode -> id == 0)
            tmpNode -> id = 1;
         else
            tmpNode -> id = 0;
         tmpNode -> next -> id = -1;
         if (debug) printf("----------------- tmpNode:\n");
         if (debug) printTree(tmpNode);
         returnNode = tmpNode; 
      }
      if (debug) printf("----------------- returnNode:\n");
      if (debug) printTree(returnNode);
   } else
   if ( (node -> sub -> id == G_OPERATOR_AND)  |
        (node -> sub -> id == G_OPERATOR_NAND) |
        (node -> sub -> id == G_OPERATOR_OR)   |
        (node -> sub -> id == G_OPERATOR_NOR)  |
        (node -> sub -> id == G_OPERATOR_XOR)  |
        (node -> sub -> id == G_OPERATOR_NXOR) ) {
      NODE* tmpNode = solveEquation(node -> next);
      if (debug) printf("----------------- tmpNode unary [n]and|or:\n");
      if (debug) printTree(tmpNode);
      unsigned retVal = 1;
      if (tmpNode -> next -> id == -1)
         chopZero(tmpNode -> next -> next);
      if (debug) printf("----------------- tmpNode unary [n]and|or:\n");
      if (debug) printTree(tmpNode);
      if (1) {
         NODE* ptrNode = tmpNode -> next -> next;
         while (1) {
            if (ptrNode -> id == 0) {
               if ( (node -> sub -> id == G_OPERATOR_AND)  |
                    (node -> sub -> id == G_OPERATOR_NAND) ) {
                  retVal = 0;
                  break;
               }
            } else
            if (ptrNode -> id == 1) {
               if ( (node -> sub -> id == G_OPERATOR_OR)  |
                    (node -> sub -> id == G_OPERATOR_NOR) ) {
                  retVal = 0;
                  break;
               }
               if ( (node -> sub -> id == G_OPERATOR_XOR)  |
                    (node -> sub -> id == G_OPERATOR_NXOR) ) {
                  if (retVal == 1)
                     retVal = 0;
                  else
                  if (retVal == 0)
                     retVal = 1;
               }
            } else {
               retVal = 2;
               break;
            }
            if (ptrNode -> next == NULL)
               break;
            ptrNode = ptrNode -> next;
         }
      }
      returnNode = initNode(0);
      returnNode -> next = initNode(tmpNode -> next -> id);
      if ( (node -> sub -> id == G_OPERATOR_NAND) |
           (node -> sub -> id == G_OPERATOR_NOR)  |
           (node -> sub -> id == G_OPERATOR_XOR)  )
      if (retVal == 0)
         retVal = 1;
      else
      if (retVal == 1)
         retVal = 0;
      returnNode -> next -> next = initNode(retVal);
      if (debug) printf("----------------- returnNode unary [n]and|or:\n");
      if (debug) printTree(returnNode);
   } else
   if (node -> sub -> id == G_OPERATOR_MINUS) {
      returnNode = solveEquation(node -> next);
      if (returnNode == NULL)
         return NULL;
      if (debug) printf("----------------- tmpNode unary minus:\n");
      if (debug) printTree(returnNode);
      NODE* resNode = returnNode -> next -> next;
      bool isZero = true;
      if (resNode != NULL) {
         while (1) {
            if (resNode -> id != 0) {
               isZero = false;
            }
            if (resNode -> next == NULL)
               break;
            resNode = resNode -> next;
         }
      }
      if (debug) printf("isZero: %d\n", isZero);
      if (isZero) {
         returnNode -> id = 0;
         chopZero(returnNode -> next -> next);
      } else
      if (returnNode -> id == 0)
         returnNode -> id = 1;
      else
         returnNode -> id = 0;
      if (debug) printf("----------------- returnNode:\n");
      if (debug) printTree(returnNode);
   } else
   if (node -> sub -> id == G_OPERATOR_PLUS) {
      returnNode = solveEquation(node -> next);
      if (debug) printf("----------------- returnNode:\n");
      if (debug) printTree(returnNode);
   } 
   return cleanBin(returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
// getPrecedence
/////////////////////////////////////////////////////////////////////////////////
unsigned getPrecedence (unsigned operatorId) {
   switch (operatorId) {
   // 0: case () [] :: . Left Highest
   // 1: case + - ! ~ & ~& | ~| ^ ~^ ^~ ++ -- (unary)
   // 2: case ** Left
   case G_OPERATOR_POW :            return 2;
   // 3: case * / % Left
   case G_OPERATOR_MUL :
   case G_OPERATOR_DIV :
   case G_OPERATOR_MOD :              return 3;
   // 4: case + - (binary) Left
   case G_OPERATOR_PLUS :
   case G_OPERATOR_MINUS :            return 4;
   // 5: case << >> <<< >>> Left
   case G_OPERATOR_LSL :
   case G_OPERATOR_LSR :
   case G_OPERATOR_ASL :
   case G_OPERATOR_ASR :              return 5;
   // 6: case < <= > >= inside dist Left
   case G_OPERATOR_GREATER :
   case G_OPERATOR_GREATER_EQUAL :
   case G_OPERATOR_LESSER :
   case G_OPERATOR_LESSER_EQUAL :     return 6;
   // 7: case == != === !== ==? !=? Left
   case G_OPERATOR_LOGICAL_EQUAL :
   case G_OPERATOR_LOGICAL_INEQUAL :
   case G_OPERATOR_CASE_EQUAL :
   case G_OPERATOR_CASE_INEQUAL :
   case G_OPERATOR_WILDCARD_EQUAL :
   case G_OPERATOR_WILDCARD_INEQUAL : return 7;
   // 8: case & (binary) Left
   case G_OPERATOR_AND :              return 8;
   // 9: case ^ ~^ ^~ (binary) Left
   case G_OPERATOR_XOR :
   case G_OPERATOR_NXOR :             return 9;
   //10: case | (binary) Left
   case G_OPERATOR_OR :               return 10;
   //11: case && Left
   case G_OPERATOR_LAND :             return 11;
   //12: case || Left
   case G_OPERATOR_LOR :              return 12;
   //13: case ?: (conditional operator) Right
   //14: case –> <–> Right
   //15: case = += -= *= /= %= &= ^= |=
   //16: case <<= >>= <<<= >>>= := :/ <=
   //17: case None
   //18: case {} {{}}
   }
   return 0;
}
/////////////////////////////////////////////////////////////////////////////////
// solvePrecedenceEquation
/////////////////////////////////////////////////////////////////////////////////
NODE* solvePrecedenceEquation (NODE* node, 
                               NODE* bSubNode) {
   bool debug = false;
   unsigned aPrec = getPrecedence(node -> sub -> sub -> next -> sub -> id);
   unsigned bPrec = getPrecedence(bSubNode -> sub -> sub -> next -> sub -> id);
   if (debug) printf("aPrec: %d bPrec: %d\n", aPrec, bPrec);
   if (aPrec < bPrec) {
      node -> sub -> sub -> next -> next -> id = G_SV_CONSTANT_PRIMARY;
      node -> sub -> sub -> next -> next -> sub = bSubNode -> sub -> sub -> sub;
      bSubNode -> sub -> sub -> id = G_SV_CONSTANT_EXPRESSION;
      bSubNode -> sub -> sub -> sub = node -> sub;
      if (debug) printf("----------------- precedence node reordered:\n");
      if (debug) printTree(bSubNode);
      return solveEquation(bSubNode -> sub);
   }
   return solveEquation(node -> sub);
}
/////////////////////////////////////////////////////////////////////////////////
/// Solves the expression of the given NODE.
/// Returns NULL when solving not successful.
/////////////////////////////////////////////////////////////////////////////////
NODE* solveEquation (NODE* node) {
   bool debug = false;
   if (debug) printf("solveEquation: %d\n", node -> id);
   if (	(node -> id == G_SV_BINARY_NUMBER_PREV0) 	|
        (node -> id == G_SV_BINARY_NUMBER_PREV1) 	|
        (node -> id == G_SV_DECIMAL_NUMBER_PREV1)  |
        (node -> id == G_SV_DECIMAL_NUMBER_PREV4)  ) {
      return binOctHex2SBin(node -> sub);
   } else
   if (	(node -> id == G_SV_DECIMAL_NUMBER_PREV2)  |
        (node -> id == G_SV_DECIMAL_NUMBER_PREV5)  ) {
      NODE* returnNode = initNode(0);
      returnNode -> next = initNode(-1);
      returnNode -> next -> next = initNode(2);
      return returnNode;
   } else
   if (	(node -> id == G_SV_DECIMAL_NUMBER_PREV3)  |
        (node -> id == G_SV_DECIMAL_NUMBER_PREV6)  ) {
      NODE* returnNode = initNode(0);
      returnNode -> next = initNode(-1);
      returnNode -> next -> next = initNode(3);
      return returnNode;
   } else
   if (	(node -> id == G_SV_OCTAL_NUMBER) 			|
        (node -> id == G_SV_HEX_NUMBER) 			|
        (node -> id == G_SV_UNSIGNED_NUMBER) 			) {
      return binOctHex2SBin(node -> sub -> sub);
   } else
   if (	(node -> id == G_SV_UNARY_CONSTANT_PRIMARY) 	) {
      return unaryConstant2SBin(node -> sub);
   } else
   if (	(node -> id == G_SV_CONSTANT_CONCATENATION) 	) {
      return concatEquation(node -> sub);
   } else
   if (	(node -> id == G_SV_CONSTANT_EXPRESSION_BINARY)) {
      //////////////////////////////////////
      // precedence
      //////////////////////////////////////
      NODE* bSubNode = node -> sub -> sub -> next -> next -> sub;
      if (bSubNode -> id == G_SV_CONSTANT_EXPRESSION_BINARY) {
         if (debug) printf("----------------- precedence node:\n");
         if (debug) printTree(node);
         return solvePrecedenceEquation(node, bSubNode);
      }
      return solveEquation(node -> sub);
   } else
   if (	(node -> id == G_SV_EXPRESSION)	   			|
   		(node -> id == G_SV_EXPRESSION_BINARY)			|
   		(node -> id == G_SV_CONSTANT_PRIMARY)			|
   		(node -> id == G_SV_CONSTANT_MINTYPMAX_EXPRESSION) |
   		(node -> id == G_SV_CONSTANT_BRACKET_MINTYPMAX_EXPRESSION) |
   		(node -> id == G_SV_CONSTANT_PARAM_EXPRESSION) |
      	(node -> id == G_SV_CONSTANT_EXPRESSION)		|
        (node -> id == G_SV_GENVAR_IDENTIFIER)			|
        (node -> id == G_SV_GENVAR_EXPRESSION)			|
   		(node -> id == G_SV_PRIMARY) 					|
   		(node -> id == G_SV_PRIMARY_LITERAL)			|
   		(node -> id == G_SV_NUMBER) 				|
   		(node -> id == G_SV_INTEGRAL_NUMBER) 			|
   		(node -> id == G_SV_BINARY_NUMBER) 			|
   		(node -> id == G_SV_DECIMAL_NUMBER) 			|
   		(node -> id == G_SV_DECIMAL_NUMBER_PREV7) 		) {
      return solveEquation(node -> sub);
   } else
   if (	(node -> id == G_SV_GENVAR_ITERATION_ASSIGNMENT) 	|
   		(node -> id == G_SV_GENVAR_ITERATION_INC_OR_DEC) 	|
   		(node -> id == G_SV_EXPRESSION_BINARY_PRIMARY)		|
   		(node -> id == G_SV_EXPRESSION_BINARY_UNARY)		|
   		(node -> id == G_SV_CONSTANT_EXPRESSION_BINARY_PRIMARY) 	|
      	(node -> id == G_SV_CONSTANT_EXPRESSION_BINARY_UNARY)		|
   		(node -> id == G_SV_CONSTANT_TRINARY_EXPRESSION) 	) {
      if (node -> sub != NULL) {
         if (debug) printf("----------------- node -> sub:\n");
         if (debug) printTree(node -> sub);
         NODE* aNode = solveEquation(node -> sub);
         if (aNode == NULL)
            return NULL;
         if (debug) printf("----------------- aNode:\n");
         if (debug) printTree(aNode);
         NODE* returnNode = NULL;
         ////////////////////////////////////////////
         // unary operation
         ////////////////////////////////////////////
         if (node -> sub -> next != NULL)
         if (node -> sub -> next -> next == NULL) {
            if (node -> sub -> next -> sub != NULL) {
               returnNode = incDecEquation(aNode, node -> sub -> next -> sub -> id);
            }
            deleteTree(aNode);
            if (debug) printf("----------------- returnNode:\n");
            if (debug) printTree(returnNode);
            return returnNode;
         } else 
         ////////////////////////////////////////////
         // trinary operation (only ?: so far)
         ////////////////////////////////////////////
         if (node -> sub -> next != NULL)
         if (node -> sub -> next -> id == G_SV_TRINARY_OPERATOR) {
            if (sbin2Bool(aNode))
               returnNode = solveEquation(node -> sub -> next -> next);
            else
               returnNode = solveEquation(node -> sub -> next -> next -> next);
            deleteTree(aNode);
            if (debug) printf("----------------- returnNode:\n");
            if (debug) printTree(returnNode);
            return returnNode;
         } else {
         ////////////////////////////////////////////
         // binary operation
         ////////////////////////////////////////////
            NODE* bNode = solveEquation(node -> sub -> next -> next);
            if (bNode == NULL)
               return NULL;
            if (debug) printf("----------------- bNode:\n");
            if (debug) printTree(bNode);
            //exit(-1);
            if (node -> sub -> next -> sub != NULL) {
               if ( (node -> sub -> next -> sub -> id == G_OPERATOR_GREATER)          |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_GREATER_EQUAL)    |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_LESSER)           |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_LESSER_EQUAL)     |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_LOGICAL_INEQUAL)  |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_LOGICAL_EQUAL)    |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_CASE_INEQUAL)     |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_CASE_EQUAL)       |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_WILDCARD_INEQUAL) |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_WILDCARD_EQUAL)   ) {
                  returnNode = compareEquation(aNode, bNode, node -> sub -> next -> sub -> id);
               } else
               if ( (node -> sub -> next -> sub -> id == G_OPERATOR_AND)  |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_OR)   |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_XOR)  |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_NXOR) ) {
                  returnNode = combEquation(aNode, bNode, node -> sub -> next -> sub -> id);
               } else
               if ( (node -> sub -> next -> sub -> id == G_OPERATOR_LAND) |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_LOR)  ) {
                  returnNode = logicalEquation(aNode, bNode, node -> sub -> next -> sub -> id);
               } else
               if ( (node -> sub -> next -> sub -> id == G_OPERATOR_ASL) |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_ASR) |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_LSL) |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_LSR) ) {
                  returnNode = shiftEquation(aNode, bNode, node -> sub -> next -> sub -> id);
               } else
               if ( (node -> sub -> next -> sub -> id == G_SV_ASSIGNMENT_OPERATOR_PLUS_ASSIGN) |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_PLUS)                   ) {
                  returnNode = plusEquation(aNode, bNode);
               } else
               if (node -> sub -> next -> sub -> id == G_OPERATOR_MINUS) {
                  returnNode = minusEquation(aNode, bNode);
               } else
               if (node -> sub -> next -> sub -> id == G_OPERATOR_MUL) {
                  return multEquation(aNode, bNode);
               } else
               if ( (node -> sub -> next -> sub -> id == G_OPERATOR_DIV) |
                    (node -> sub -> next -> sub -> id == G_OPERATOR_MOD) ) {
                  returnNode = divModEquation(aNode, bNode, node -> sub -> next -> sub -> id);
               } else
               if (node -> sub -> next -> sub -> id == G_OPERATOR_POW) {
                  returnNode = powerEquation(aNode, bNode);
               }
               deleteTree(aNode);
               deleteTree(bNode);
               if (debug) printf("----------------- returnNode:\n");
               if (debug) printTree(returnNode);
               if (0)
               if (node -> sub -> next -> sub -> id == G_OPERATOR_MINUS) {
                  exit(-1);
               }
               return returnNode;
            }
         }
      }
      return NULL;
   } else
   if (	(node -> id == G_SV_UNARY_PRIMARY)	) {
      if (node -> sub != NULL) {
         if (node -> sub -> sub -> id == G_OPERATOR_MINUS) {
            NODE* returnNode = solveEquation(node -> sub -> next);
            if (returnNode -> id == 0)
               returnNode -> id = 1;
            else
               returnNode -> id = 0;
            if (debug) printf("----------------- returnNode:\n");
            if (debug) printTree(returnNode);
            return returnNode;
         }
      }
      return NULL;
   } else
   if (	(node -> id == G_SV_BRACKET_MINTYPMAX_EXPRESSION) |
        (node -> id == G_SV_MINTYPMAX_EXPRESSION)         ) {
      if (node -> sub != NULL) {
         NODE* returnNode = solveEquation(node -> sub);
         return returnNode;
      }
   }
   if (debug) printf("----------------- unsolved:\n");
   if (debug) printTree(node);
   return NULL;
}
