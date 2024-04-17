//
// Copyright 2024 Tobias Strauch, Munich, Bavaria
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//

#include <iostream>
#include <algorithm>
#include <new>
using namespace std;

#include <nodesAndTrees.h>
#include <writer.h>
      
/////////////////////////////////////////////////////////////////////////////////
/// Returns a new node with given id.
/////////////////////////////////////////////////////////////////////////////////
NODE* initNode (unsigned id) {
   NODE* returnNode = new NODE();
   returnNode -> id = id;
   returnNode -> sub = NULL; 
   returnNode -> next = NULL;
   return returnNode; 
}
/////////////////////////////////////////////////////////////////////////////////
/// Returns a new node with given id at the sub node of the give node.
/////////////////////////////////////////////////////////////////////////////////
NODE* initSubNode (NODE* node, 
                   unsigned id) {
   NODE* returnNode = initNode(id);
   node -> sub = returnNode;
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
///	Initializes a new node with the given id and links it as sub node 
/// to the given node.
/// Returns the new node.
/////////////////////////////////////////////////////////////////////////////////
//NODE* appendSubNode (NODE* node, unsigned id) {
//   NODE* returnNode = initNode(id);
//   node -> sub = returnNode;
//   return returnNode;
//} 
/////////////////////////////////////////////////////////////////////////////////
/// Returns a new node with given id at the next node of the give node.
/////////////////////////////////////////////////////////////////////////////////
NODE* initNextNode (unsigned id, 
                    NODE *node) {
   NODE* returnNode = initNode(id);
   node -> next = returnNode;
   return returnNode;
}
/////////////////////////////////////////////////////////////////////////////////
///	Initializes a new node with the given id and links it as sub node 
/// to the given node.
/////////////////////////////////////////////////////////////////////////////////
void insertNode (NODE *node, 
                 unsigned id) {
   NODE* newNode = new NODE();
   newNode -> id = node -> id;
   newNode -> sub = node -> sub;
   newNode -> next = node -> next;
   //node -> id = id;
   node -> sub = newNode;
   //node -> next = NULL;             
}
/////////////////////////////////////////////////////////////////////////////////
/// Parses the given tree and returns first node that matches given id.
/// If no node is found, then it returns NULL.
/////////////////////////////////////////////////////////////////////////////////
NODE* getNode (NODE* node, 
               unsigned id) {
   if (node -> id == id) return node;
   if (node -> sub != NULL) {
      NODE* returnNode = getNode(node -> sub, id);
      if (returnNode != NULL) return returnNode; }
   if (node -> next != NULL) return getNode(node -> next, id);
   return NULL;
}    
/////////////////////////////////////////////////////////////////////////////////
/// Parses the given tree only one the level of the given NODE 
/// and returns first node that matches given id.
/// If no NODE is found then it returns NULL.
/////////////////////////////////////////////////////////////////////////////////
NODE* getNodeThisLevel (NODE* node, 
                        unsigned id) {
   while (1) {
      if (node -> id == id) return node;
      if (node -> next == NULL)
         break;
      node = node -> next;
   }
   return NULL;
}    
/////////////////////////////////////////////////////////////////////////////////
/// Parses the given tree only one sub level of the given NODE 
/// and returns first node that matches given id.
/// If no NODE is found then it returns NULL.
/////////////////////////////////////////////////////////////////////////////////
NODE* getNodeSubLevel (NODE* node, 
                       unsigned id) {
   if (node -> sub != NULL)
      return getNodeThisLevel(node -> sub, id);
   return NULL;
}    
/////////////////////////////////////////////////////////////////////////////////
/// Finds all nodes with the given id in a tree and adds them to the return list
/////////////////////////////////////////////////////////////////////////////////
void getNodes (unsigned id, 
               NODE *sourceNode, 
               NODE *returnNode) {
   if (sourceNode -> id == id) {
      if (returnNode -> sub == NULL) {
         returnNode -> sub = sourceNode;
         return;
      } else {
         NODE* newNode = initNode(0);
         newNode -> sub = sourceNode;
         newNode -> next = returnNode -> next;
         returnNode -> next = newNode; }      
   } else
   if (sourceNode -> sub != NULL) {
      getNodes(id, sourceNode -> sub, returnNode); }                                  
   if (sourceNode -> next != NULL)
      getNodes(id, sourceNode -> next, returnNode);
}
/////////////////////////////////////////////////////////////////////////////////
/// Changes the id of all nodes in a tree with the given from id to 
/// the given to id.
/////////////////////////////////////////////////////////////////////////////////
void modifyNode (NODE* node, 
                 unsigned fromID, 
                 unsigned toID) {  
   if (node -> id == fromID)
      node -> id = toID;
   if (node -> sub != NULL) modifyNode(node -> sub, fromID, toID);
   if (node -> next != NULL) modifyNode(node -> next, fromID, toID);
}                                                
/////////////////////////////////////////////////////////////////////////////////
/// Converts a node into a string.
/////////////////////////////////////////////////////////////////////////////////
string node2String (NODE* node) {
   string thisHeader = "";
   for (int cnt = 0; cnt < 4; cnt++) {
      char c = (node -> id >> (8 * cnt)) & 0xff;
      if (	(	(c >= 'a') & (c <= 'z')	)	|
               	(	(c >= 'A') & (c <= 'Z')	)	|
               	(	(c >= '0') & (c <= '9')	)	|
             	(c == '_')						)
         thisHeader.append(1u, c);
   }
   return thisHeader;
}
/////////////////////////////////////////////////////////////////////////////////
/// Parses a list of a given node list and returns integer value.
/////////////////////////////////////////////////////////////////////////////////
int string2Int (NODE* node) {
   int returnInt = 0;
   while (true) {
      for (int cnt = 0; cnt < 4; cnt++) {
         char c = (node -> id >> (8 * cnt)) & 0xff;
         if (	(c >= '0') & (c <= '9')	)
            returnInt = returnInt * 10 + (c - 48);
      }                              
      if (node -> next == NULL)
         break;    
      node = node -> next;
   }
   return returnInt;
}
/////////////////////////////////////////////////////////////////////////////////
/// Check if string is number
///////////////////////////////////////////////////////////////////////////////// 
bool is_number (const string &s) {
  return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}
/////////////////////////////////////////////////////////////////////////////////
/// Compares two given trees. Return true if they are identical.
/////////////////////////////////////////////////////////////////////////////////
bool checkTree (NODE* treeA, 
                NODE* treeB) {
   if (treeA -> id != treeB -> id)
      return false;
   if (treeA -> sub != NULL) {
      if (treeB -> sub == NULL) 
      		return false;
      if (!(checkTree(treeA -> sub, treeB -> sub)))
         return false;
   } else
   if (treeB -> sub != NULL) 
      return false;
   if (treeA -> next != NULL) {
      if (treeB -> next == NULL) 
      		return false;
      if (!(checkTree(treeA -> next, treeB -> next)))
         return false;
   } else
   if (treeB -> next != NULL) 
      return false;
   return true;
}
/////////////////////////////////////////////////////////////////////////////////
/// Checks if a string is presented as a branch in tree. 
/// Updates subNode if branch found and sub node exists.
/////////////////////////////////////////////////////////////////////////////////
bool checkTree (string &name, 
                string &header, 
                NODE* tree, 
                NODE* subNode) {
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      for (int cnt = 0; cnt < 4; cnt++) {
         char c = (tree -> id >> (8 * cnt)) & 0xff;
         if (	(	(c >= 'a') & (c <= 'z')	)	|
                  	(	(c >= 'A') & (c <= 'Z')	)	|
                  	(	(c >= '0') & (c <= '9')	)	|
                	(c == '_')						)
            thisHeader.append(1u, c);
      }                              
      if (tree -> sub != NULL)
         if (tree -> sub -> id != 0) {
            bool found = checkTree(name, thisHeader, tree -> sub, subNode);
            if (found) return true;
         } else {
            if (thisHeader.compare(name) == 0) {
               if (subNode != NULL) 
                  subNode -> sub = tree -> sub -> sub;
               return true; 
            }
            if (tree -> sub -> next != NULL) {
               bool found = checkTree(name, thisHeader, tree -> sub -> next, subNode);
               if (found)
                  return true; 
            } 
         }
      if (tree -> next == NULL)
         break;    
      tree = tree -> next; }
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
/// Calls checkTree with the same parameters and a new header.
/////////////////////////////////////////////////////////////////////////////////
bool checkTree (string &name, 
                NODE* tree) {
   string tmpHeader = "";
   return checkTree(name, tmpHeader, tree, NULL);
}
/////////////////////////////////////////////////////////////////////////////////
/// Checks if the SI list testTreeNode is included in the tree inTreeNode.
/////////////////////////////////////////////////////////////////////////////////
bool checkSITree (NODE* testTreeNode, 
                  NODE* inTreeNode) {
   while (true) {
      if (inTreeNode -> id == testTreeNode -> id) {
         ///////////////////////////////////////////
         // end of testTree
         ///////////////////////////////////////////
         if (testTreeNode -> next == NULL) {
             if (inTreeNode -> sub -> id == 0) 
                return true;
             else
                return false;
         } else
            return checkSITree(testTreeNode -> next, inTreeNode -> sub);
      }
      if (inTreeNode -> next == NULL)
         break;    
      inTreeNode = inTreeNode -> next; }
   return false;
}
/////////////////////////////////////////////////////////////////////////////////
/// The function parses the given tree (starting from node), until it finds 
/// an identifier node. Starting from there it inserts the given SI list into 
/// the "tree". 
/// The resulting nodes on each level are ordered. 
/// It adds a node with the id 0 at the end of each branch.
/// The node origNode (can be NULL) is added as sub below the 0 identifier node.
/////////////////////////////////////////////////////////////////////////////////
void addSITree (NODE* node, 
                NODE* origNode, 
                NODE* tree) {
   if (	(node -> id == G_SV_CONSTANT_PRIMARY) 			|
  		(node -> id == G_SI) 						|
  		(node -> id == G_PDVL_CLUSTER_CL_SI) 						|
  		(node -> id == G_PDVL_EVENT_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_DATA_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME) 	) {
      NODE* givenTree = tree;
      if (node -> sub != NULL) {
         NODE* tmpNode = node -> sub;
         while (1) {
            if (tree -> sub == NULL) {
               NODE* newSubNode = initNode(tmpNode -> id);
               tree -> sub = newSubNode;
               tree = newSubNode;
            } else {            
               if (tree -> sub -> id == tmpNode -> id) {
                  tree = tree -> sub;
               } else if (tree -> sub -> id > tmpNode -> id) {
                  NODE* newSubNode = initNode(tmpNode -> id);
                  newSubNode -> next = tree -> sub;
                  tree -> sub = newSubNode;
                  tree = newSubNode;
               } else {
                  tree = tree -> sub;
                  while (1) {
                     if (tree -> next == NULL) {  // append
                        NODE* newSubNode = initNode(tmpNode -> id);
                        tree -> next = newSubNode;
                        tree = newSubNode;
                        break;
                     } else if (tree -> next -> id == tmpNode -> id) {
                        if (tmpNode -> next == NULL) {
                           NODE* newSubNode = initNode(0);
                           newSubNode -> next = tree -> next -> sub;
                           tree -> next -> sub = newSubNode;
                           newSubNode -> sub = origNode;
                           return;                  
                        }
                        tree = tree -> next;
                        break;
                     } else if (tree -> next -> id > tmpNode -> id) { // insert
                        NODE* newSubNode = initNode(tmpNode -> id);
                        newSubNode -> next = tree -> next;
                        tree -> next = newSubNode;
                        tree = newSubNode;
                        break;
                     } else
                        tree = tree -> next;
                  }
               }
            }
            if (tmpNode -> next == NULL)
               break;
            tmpNode = tmpNode -> next; 
         } 
         if (tree -> sub == NULL) {
            NODE* newSubNode = initNode(0);
            tree -> sub = newSubNode;
            newSubNode -> sub = origNode;
         } else 
         if (tree -> sub -> id != 0) {
            // This is still a bug, when tree (actually a list) longer than tree
            NODE* newSubNode = initNode(0);
            newSubNode -> next = tree -> sub;
            newSubNode -> sub = origNode; // 210504
            tree -> sub = newSubNode; 
         } else 
         if (1) {  // == 0 210931
            // This is still a bug, when tree (actually a list) longer than tree
            //NODE* newSubNode = initNode(tree -> sub -> id);  // 0);  210931
            //newSubNode -> next = tree -> sub;
            //newSubNode -> sub = origNode; // 210504
            //tree -> sub = newSubNode; 
            //exit(-1);
            //printf("calling mergeSITree.\n");
            if (origNode != NULL) {
               //   printTree(origNode);
               tree = tree -> sub;
               if (tree -> sub == NULL) {
                  tree -> sub = origNode;
                  return;
               } else {
                  //printf("into:\n");
                  //printTree(tree);
                  if (!(checkTree(origNode, tree -> sub))) {
                     //printf("not equal.\n");
                     mergeSITrees(origNode, tree -> sub);     
                  }
                  //printf("done.\n");
                  return;               
               }
            }
         } 
      }
      return; 
   }
   if (node -> sub != NULL)
      addSITree(node -> sub, origNode, tree);
   else if (node -> next != NULL)
      addSITree(node -> next, origNode, tree);
}
/////////////////////////////////////////////////////////////////////////////////
/// Converts the given string into an SI node and calls addSITree with it.
/////////////////////////////////////////////////////////////////////////////////
void addSITree (string &name, 
                NODE* subTree, 
                NODE* tree) {
   NODE* newNode = initNode(0);
   parser_si(name, 0, newNode);
   addSITree(newNode, subTree, tree);
   deleteTree(newNode);
}
/////////////////////////////////////////////////////////////////////////////////
/// Converts the given string into an SI node and calls addSITree with it.
/// Passes NULL as sub-tree.
/////////////////////////////////////////////////////////////////////////////////
void addSITree (string &name, 
                NODE* tree) {
   NODE* newNode = initNode(0);
   parser_si(name, 0, newNode);
   addSITree(newNode, NULL, tree);
   deleteTree(newNode);
}
/////////////////////////////////////////////////////////////////////////////////
/// Returns a hell of a copy of the given tree.
/////////////////////////////////////////////////////////////////////////////////
NODE* copyTree (NODE *node) {
   NODE* newEntry = initNode(node -> id);
   if (node -> sub != NULL) newEntry -> sub = copyTree(node -> sub);
   if (node -> next != NULL) newEntry -> next = copyTree(node -> next);
   return newEntry;
}
/////////////////////////////////////////////////////////////////////////////////
/// Returns a copy of a given tree w/o the -> next subbranch of the 
/// given top node.
/////////////////////////////////////////////////////////////////////////////////
NODE* copyTreeNoNext (NODE *node) {
   NODE* newEntry = initNode(node -> id);
   if (node -> sub != NULL) newEntry -> sub = copyTree(node -> sub);
   return newEntry;
}
/////////////////////////////////////////////////////////////////////////////////
/// Merges aTree into resultTree.
/// If aTree has a 0 identifier node, it continues merging, when 
/// parameter passZero is true.
/////////////////////////////////////////////////////////////////////////////////
void mergeTrees (bool passZero, 
                 NODE* aTree, 
                 NODE* resultTree) {                          
      /////////////////////////////////////
      //  Empty aTree sub
      /////////////////////////////////////
      if (aTree -> sub == NULL) {
      /////////////////////////////////////
      //  Empty bTree sub
      /////////////////////////////////////
      } else if (resultTree -> sub == NULL) {
         /////////////////////////////////////
         //  merge aTree sub
         /////////////////////////////////////
         resultTree -> sub = copyTree(aTree -> sub);
      /////////////////////////////////////////////////////////
      //  Go through aTree -> next and bTree -> next 
      /////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////
      //  Go through aTree -> next and resultTree -> next 
      /////////////////////////////////////////////////////////
      } else {
         aTree = aTree -> sub;
         //NODE* bTree = resultTree -> sub;
         bool sub = true;
         while (1) {        
            if (sub) {
               sub = false;
               /////////////////////////////////////
               //  Identical aTree and resultTree ids
               /////////////////////////////////////
               if (aTree -> id == resultTree -> sub -> id) {
                  resultTree = resultTree -> sub;
                  /////////////////////////////////////
                  //  continue on next level
                  /////////////////////////////////////
                  if (  (aTree -> sub == NULL) &
                        (resultTree -> sub != NULL) ) {
                  } else
                  if (  (!(passZero))			    &
                         (aTree -> sub != NULL)     &
                        (resultTree -> sub == NULL) ) {
                      printf("Error b?\n");
                      exit(-1);
                  } else {
                     if (passZero)
                        mergeTrees(passZero, aTree, resultTree);
                     else
                     if (  (aTree -> sub -> id == 0) &
                           (resultTree -> sub -> id == 0) ) {
                     } else {
                        mergeTrees(passZero, aTree, resultTree);
                     }
                  }
                  /////////////////////////////////////
                  //  next aTree -> next when exists
                  /////////////////////////////////////
                  if (aTree -> next == NULL) {
                     /////////////////////////////////////
                     //  copy next bTree -> next when exists
                     /////////////////////////////////////
                     break; }
                  aTree = aTree -> next;     
                  /////////////////////////////////////
                  //  next bTree -> next when exists
                  /////////////////////////////////////
                  if (resultTree -> next == NULL){
                     /////////////////////////////////////
                     //  copy next aTree 
                     /////////////////////////////////////
                     resultTree -> next = copyTree(aTree);     
                     break; }
               /////////////////////////////////////
               //  aTree < resultTree ids => copy aTree node
               /////////////////////////////////////
               } else if (aTree -> id < resultTree -> sub -> id) {
                  NODE* tmpNode = initNode(aTree -> id);
                  /////////////////////////////////////
                  //  merge at resultTree sub
                  /////////////////////////////////////
                  tmpNode -> next = resultTree -> sub;
                  resultTree -> sub = tmpNode;
                  resultTree = tmpNode;
                  /////////////////////////////////////
                  //  copy sub aTree -> sub when exists
                  /////////////////////////////////////
                  if (aTree -> sub != NULL)
                     resultTree -> sub = copyTree(aTree -> sub);
                  /////////////////////////////////////
                  //  next aTree -> next when exists
                  /////////////////////////////////////
                  if (aTree -> next == NULL)
                     break;
                  aTree = aTree -> next;
              /////////////////////////////////////
              //  aTree > resultTree ids
              /////////////////////////////////////
               } else {
                  resultTree = resultTree -> sub;
                  /////////////////////////////////////
                  //  next bTree -> next when exists
                  /////////////////////////////////////
                  if (resultTree -> next == NULL) {
                     /////////////////////////////////////
                     //  copy next aTree -> next when exists
                     /////////////////////////////////////
                     resultTree -> next = copyTree(aTree);     
                     //printf("a greater cont a\n");
                     break; }
               }
            } else
            {
               /////////////////////////////////////
               //  Identical aTree and resultTree ids
               /////////////////////////////////////
               if (aTree -> id == resultTree -> next -> id) {
                  resultTree = resultTree -> next;
                  /////////////////////////////////////
                  //  continue on next level
                  /////////////////////////////////////
                  if (  (!(passZero))				  &
                        (aTree -> sub == NULL) &
                        (resultTree -> sub != NULL) ) {
                      //break;
                      printf("Error c?\n");
                      exit(-1);
                  } else
                  if (  (aTree -> sub != NULL) &
                        (resultTree -> sub == NULL) ) {
                      printf("Error d?\n");
                      exit(-1);
                  } else {
                     if (  (!(passZero))				  &
                           (aTree -> sub -> id == 0)      &
                           (resultTree -> sub -> id == 0) ) {
                     } else {
                        mergeTrees(passZero, aTree, resultTree);
                     }
                  }
                  /////////////////////////////////////
                  //  next aTree -> next when exists
                  /////////////////////////////////////
                  if (aTree -> next == NULL) {
                     /////////////////////////////////////
                     //  copy next bTree -> next when exists
                     /////////////////////////////////////
                     break; }
                  aTree = aTree -> next;     
                  /////////////////////////////////////
                  //  next bTree -> next when exists
                  /////////////////////////////////////
                  if (resultTree -> next == NULL){
                     /////////////////////////////////////
                     //  copy next aTree 
                     /////////////////////////////////////
                     resultTree -> next = copyTree(aTree);     
                     break; }
               /////////////////////////////////////
               //  aTree < resultTree ids => copy aTree node
               /////////////////////////////////////
               } else if (aTree -> id < resultTree -> next -> id) {
                  NODE* tmpNode = initNode(aTree -> id);
                  /////////////////////////////////////
                  //  merge at resultTree next
                  /////////////////////////////////////
                  tmpNode -> next = resultTree -> next;
                  resultTree -> next = tmpNode;
                  resultTree = tmpNode;
                  /////////////////////////////////////
                  //  copy sub aTree -> sub when exists
                  /////////////////////////////////////
                  if (aTree -> sub != NULL)
                     resultTree -> sub = copyTree(aTree -> sub);
                  /////////////////////////////////////
                  //  next aTree -> next when exists
                  /////////////////////////////////////
                  if (aTree -> next == NULL)
                     break;
                  aTree = aTree -> next;
               /////////////////////////////////////
               //  aTree > resultTree ids
               /////////////////////////////////////
               } else {
                  resultTree = resultTree -> next;
                  /////////////////////////////////////
                  //  next resultTree -> next when exists
                  /////////////////////////////////////
                  if (resultTree -> next == NULL) {
                     /////////////////////////////////////
                     //  copy next aTree -> next when exists
                     /////////////////////////////////////
                        resultTree -> next = copyTree(aTree); 
                     break; }
               }           
            }
         }
      }
}
/////////////////////////////////////////////////////////////////////////////////
/// Calls mergeTrees with passZero parameter set to false
/////////////////////////////////////////////////////////////////////////////////
void mergeTrees (NODE* aTree, 
                 NODE* resultTree) {
   mergeTrees(false, aTree, resultTree);
}
/////////////////////////////////////////////////////////////////////////////////
/// Merges aTree and bTree to generate resultTree.
/////////////////////////////////////////////////////////////////////////////////
void mergeTrees (NODE* aTree, 
                 NODE* bTree, 
                 NODE* resultTree) {                          
      /////////////////////////////////////
      //  Empty aTree sub
      /////////////////////////////////////
      if (aTree -> sub == NULL) {
         /////////////////////////////////////
         //  merge bTree sub when applicable
         /////////////////////////////////////
         if (bTree -> sub != NULL)
            resultTree -> sub = copyTree(bTree -> sub);      // no a sub
      /////////////////////////////////////
      //  Empty bTree sub
      /////////////////////////////////////
      } else if (bTree -> sub == NULL) {
         /////////////////////////////////////
         //  merge aTree sub
         /////////////////////////////////////
         resultTree -> sub = copyTree(aTree -> sub);      // no b sub
      /////////////////////////////////////////////////////////
      //  Go through aTree -> next and bTree -> next 
      /////////////////////////////////////////////////////////
      } else {
         aTree = aTree -> sub;
         bTree = bTree -> sub;
         bool sub = true;
         while (1) {
            /////////////////////////////////////
            //  Identical aTree and bTree ids
            /////////////////////////////////////
            if (aTree -> id == bTree -> id) {
               NODE* tmpNode = initNode(aTree -> id);
               /////////////////////////////////////
               //  merge at resultTree sub
               /////////////////////////////////////
               if (sub) {
                  resultTree -> sub = tmpNode;
                  sub = false;
               /////////////////////////////////////
               //  merge at resultTree next
               /////////////////////////////////////
               } else {
                  resultTree -> next = tmpNode;
               }
               resultTree = tmpNode;
               /////////////////////////////////////
               //  continue on next level
               /////////////////////////////////////
               if (  (aTree -> sub == NULL) &
                     (bTree -> sub != NULL) ) {
                   printf("Error?\n");
               } else
               if (  (aTree -> sub != NULL) &
                     (bTree -> sub == NULL) ) {
                   printf("Error?\n");
               } else {
                  mergeTrees(aTree, bTree, resultTree);
               }
               /////////////////////////////////////
               //  next aTree -> next when exists
               /////////////////////////////////////
               if (aTree -> next == NULL) {
                  /////////////////////////////////////
                  //  copy next bTree -> next when exists
                  /////////////////////////////////////
                  resultTree -> next = copyTree(bTree);     
                  break; }
               aTree = aTree -> next;     
               /////////////////////////////////////
               //  next bTree -> next when exists
               /////////////////////////////////////
               if (bTree -> next == NULL){
                  /////////////////////////////////////
                  //  copy next aTree 
                  /////////////////////////////////////
                  resultTree -> next = copyTree(aTree);     
                  break; }
               bTree = bTree -> next;     
            /////////////////////////////////////
            //  aTree < bTree ids => copy aTree node
            /////////////////////////////////////
            } else if (aTree -> id < bTree -> id) {
               NODE* tmpNode = initNode(aTree -> id);
               /////////////////////////////////////
               //  merge at resultTree sub
               /////////////////////////////////////
               if (sub) {
                  resultTree -> sub = tmpNode;
                  sub = false;
               /////////////////////////////////////
               //  merge at resultTree next
               /////////////////////////////////////
               } else {
                  resultTree -> next = tmpNode;
               }
               resultTree = tmpNode;
               /////////////////////////////////////
               //  copy sub aTree -> sub when exists
               /////////////////////////////////////
               if (aTree -> sub != NULL)
                  resultTree -> sub = copyTree(aTree -> sub);
               /////////////////////////////////////
               //  next aTree -> next when exists
               /////////////////////////////////////
               if (aTree -> next == NULL) {
                  /////////////////////////////////////
                  //  copy next bTree -> next when exists
                  /////////////////////////////////////
                  resultTree -> next = copyTree(bTree);     
                  break; }
               aTree = aTree -> next;     
            /////////////////////////////////////
            //  aTree > bTree ids
            /////////////////////////////////////
            } else {
               NODE* tmpNode = initNode(bTree -> id);
               if (sub) {
                  resultTree -> sub = tmpNode;
                  sub = false;
               } else {
                  resultTree -> next = tmpNode;
               }
               resultTree = tmpNode;
               /////////////////////////////////////
               //  copy sub bTree -> sub when exists
               /////////////////////////////////////
               if (bTree -> sub != NULL)
                  resultTree -> sub = copyTree(bTree -> sub);     
               /////////////////////////////////////
               //  next bTree -> next when exists
               /////////////////////////////////////
               if (bTree -> next == NULL) {
                  /////////////////////////////////////
                  //  copy next aTree -> next when exists
                  /////////////////////////////////////
                     resultTree -> next = copyTree(aTree);     
                  break; }
               bTree = bTree -> next;     
            }           
         }
      }
}
/////////////////////////////////////////////////////////////////////////////////
/// Merge fromNode into toNode.
/////////////////////////////////////////////////////////////////////////////////
void mergeSITrees (NODE* fromNode, 
                   NODE* toNode) {
   //////////////////////////////////////
   // 0 indicator reached, shouldn't happen
   //////////////////////////////////////
   if ((fromNode -> id == 0) &
	   (toNode -> id == 0)	) {
	  if (fromNode -> sub != NULL) {                    // do not copy !
	     fromNode -> sub -> next = toNode -> sub;
	     toNode -> sub = fromNode -> sub;
	  }
   } else
   while (true) {
      NODE* tmpToNode = toNode;
      NODE* lastNode = NULL;
      while (true) {
         //////////////////////////////////////
         // same node, continue sub
         //////////////////////////////////////
         if (fromNode -> id == tmpToNode -> id) {
            if (fromNode -> sub != NULL) 
            if (tmpToNode -> sub != NULL) 
               mergeSITrees(fromNode -> sub, tmpToNode -> sub);
            break;
         } else
         //////////////////////////////////////
         // insert single node 
         //////////////////////////////////////
         if (fromNode -> id < tmpToNode -> id) {
            if (lastNode == NULL) {
               NODE* newNode = initNode(tmpToNode -> id);
               newNode -> sub = tmpToNode -> sub;
               newNode -> next = tmpToNode -> next;
               tmpToNode -> id = fromNode -> id;
               tmpToNode -> sub = fromNode -> sub;
               tmpToNode -> next = newNode;
            } else {
               NODE* newNode = initNode(fromNode -> id);
               newNode -> sub = fromNode -> sub;
               newNode -> next = lastNode -> next;
               lastNode -> next = newNode;               
            }
            break;
         }
         //////////////////////////////////////
         // append
         //////////////////////////////////////
         if (tmpToNode -> next == NULL) {
            tmpToNode -> next = fromNode;
            return;
         }
         lastNode = tmpToNode;
         tmpToNode = tmpToNode -> next;
      }
      //////////////////////////////////////
      // append
      //////////////////////////////////////
      if (fromNode -> next == NULL) {
         return;
      }
      fromNode = fromNode -> next;
   }
}
/////////////////////////////////////////////////////////////////////////////////
/// Merge fromNode into toNode.
/////////////////////////////////////////////////////////////////////////////////
void mergeSITreesSubList (NODE* fromNode, 
                          NODE* toNode) {
   //////////////////////////////////////
   // 0 indicator reached, shouldn't happen
   //////////////////////////////////////
   if ((fromNode -> id == 0) &
	   (toNode -> id == 0)	) {
	  if (fromNode -> sub != NULL) {                    // do not copy !
	     if (toNode -> sub == NULL) {
           toNode -> sub = fromNode -> sub;
         } else {
            NODE* listNode = toNode -> sub;
            while (1) {
               if (listNode -> next == NULL)
                  break;
               listNode = listNode -> next;
            }
            listNode -> next = fromNode -> sub;
         }
	  }
   } else
   while (true) {
      NODE* tmpToNode = toNode;
      NODE* lastNode = NULL;
      while (true) {
         //////////////////////////////////////
         // same node, continue sub
         //////////////////////////////////////
         if (fromNode -> id == tmpToNode -> id) { 
            mergeSITreesSubList(fromNode -> sub, tmpToNode -> sub);
            break;
         } else
         //////////////////////////////////////
         // insert single node 
         //////////////////////////////////////
         if (fromNode -> id < tmpToNode -> id) {
            if (lastNode == NULL) {
               NODE* newNode = initNode(tmpToNode -> id);
               newNode -> sub = tmpToNode -> sub;
               newNode -> next = tmpToNode -> next;
               tmpToNode -> id = fromNode -> id;
               tmpToNode -> sub = fromNode -> sub;
               tmpToNode -> next = newNode;
            } else {
               NODE* newNode = initNode(fromNode -> id);
               newNode -> sub = fromNode -> sub;
               newNode -> next = lastNode -> next;
               lastNode -> next = newNode;               
            }
            break;
         }
         //////////////////////////////////////
         // append
         //////////////////////////////////////
         if (tmpToNode -> next == NULL) {
            tmpToNode -> next = fromNode;
            return;
         }
         lastNode = tmpToNode;
         tmpToNode = tmpToNode -> next;
      }
      //////////////////////////////////////
      // append
      //////////////////////////////////////
      if (fromNode -> next == NULL) {
         return;
      }
      fromNode = fromNode -> next;
   }
}
/////////////////////////////////////////////////////////////////////////////////
///	Deletes the given tree, including top level node.
/////////////////////////////////////////////////////////////////////////////////
void deleteTree (NODE *node)
{     
   if (node -> sub != NULL)
      deleteTree(node -> sub);
   if (node -> next != NULL)
      deleteTree(node -> next);
   delete node;
}
/////////////////////////////////////////////////////////////////////////////////
/// Counts the number of autumn leaves of a tree.
/////////////////////////////////////////////////////////////////////////////////
unsigned countTreeLeaves (NODE* aTree) {
   unsigned returnValue = 0;
   if (aTree -> sub == NULL)
      returnValue = 1;
   else
      returnValue = countTreeLeaves(aTree -> sub);
   if (aTree -> next != NULL)
      returnValue += countTreeLeaves(aTree -> next);
   return returnValue;
}
/////////////////////////////////////////////////////////////////////////////////
/// Finds the shortest branch and removes other branches at the same time.
/// Returns branch depth or -1 when shortest branch length not unique.
/////////////////////////////////////////////////////////////////////////////////
int chopTree (NODE* node) {
   if (node -> id == 0) {
      if (node -> sub != NULL) {
         int subVal = chopTree(node -> sub);
         if (subVal < 0)
            return -1;
         else
            return subVal + 1;
      }
      node -> next = NULL;
      return 0;
   } else 
   if (node -> next == NULL) {
      if (node -> sub != NULL)
         return chopTree(node -> sub);
      return 0; // shouldn't
   } else {
      ///////////////////////////////
      // find unique minVal
      ///////////////////////////////
      int minVal = 10000;
      bool valid = false;
      unsigned minValId = 0;
      NODE* tmpNode = node;
      while (true) {
         int subVal = chopTree(tmpNode -> sub);
         ///////////////////////////////
         // first value or lower value
         ///////////////////////////////
         if (subVal < minVal) {
            minVal = subVal;
            valid = true;
            minValId = tmpNode -> id;
         } else 
         ///////////////////////////////
         // one min exists, new is same => not unique
         ///////////////////////////////
         if (subVal == minVal) {
            valid = false;
         }
         if (tmpNode -> next == NULL) 
            break;
         tmpNode = tmpNode -> next;
      }
      if ( (valid)       &
           (minVal > -1) ) {
         if (node -> id != minValId) {
            node -> id = minValId;
            deleteTree(node -> sub);
            NODE* tmpNode = node -> next;
            while (1) {
               if (node -> id == minValId) {
                  node -> sub = tmpNode -> sub;
                  tmpNode -> sub = NULL;
                  break;
               } 
               if (tmpNode -> next == NULL)
                  break;
               tmpNode = tmpNode -> next;
            }
         }
         deleteTree(node -> next);
         node -> next = NULL;
         return minVal;
      } else
         return -1;
   }
   return 0; // shouldn't
}
/////////////////////////////////////////////////////////////////////////////////
/// Checks if a tree in the form of a list is covered in the tree.
/////////////////////////////////////////////////////////////////////////////////
bool listCoveredInTree (NODE* node, 
                        NODE* tree, 
                        bool passTrueExactFalse) {
   bool debug = false;
   if (debug) printf("listCoveredInTree: %d %d %d\n", passTrueExactFalse, node -> id, tree -> id);
   bool returnBool = false;
   if (node -> id == tree -> id) {
      ///////////////////////////////
      // first node match found
      ///////////////////////////////
      if (passTrueExactFalse) {
         ///////////////////////////////
         // node ends on first node match found
         ///////////////////////////////
         if (node -> sub == NULL) {
            ///////////////////////////////
            // tree must end on first node match found
            ///////////////////////////////
            return (tree -> sub == NULL);
         } else {
         ///////////////////////////////
         // node has subnodes, check exact match
         ///////////////////////////////
            ///////////////////////////////
            // tree ends here => failure
            ///////////////////////////////
            if (tree -> sub == NULL) {
               return false;
            } else
            ///////////////////////////////
            // check exact match, allow further digging
            ///////////////////////////////
            if (listCoveredInTree(node -> sub, tree -> sub, false)) {
               return true;
            }
         }
      } else
      ///////////////////////////////
      // node match found while checking for exact coverage
      ///////////////////////////////
      {
         ///////////////////////////////
         // if node ends here, tree must end here as well
         ///////////////////////////////
         if (node -> sub == NULL)
            return (tree -> sub == NULL);
         ///////////////////////////////
         // node does not end here, but tree does
         ///////////////////////////////
         if (tree -> sub == NULL)
            return false;
         ///////////////////////////////
         // continue exact match
         ///////////////////////////////
         return listCoveredInTree(node -> sub, tree -> sub, false);
      }
   } else
   if (!passTrueExactFalse)
      return false;
   if (tree -> sub != NULL) {
       if (listCoveredInTree(node, tree -> sub, passTrueExactFalse))
          return true;
   }
   if (tree -> next != NULL) {
       if (listCoveredInTree(node, tree -> next, passTrueExactFalse))
          return true;
   }
   return returnBool;
}
/////////////////////////////////////////////////////////////////////////////////
/// Checks if a tree in the form of a list is covered in the tree.
/////////////////////////////////////////////////////////////////////////////////
bool listCoveredInTree (NODE* node, 
                        NODE* tree) {
   bool debug = false;
   if (debug) printf("listCoveredInTree: %d %d\n", node -> id, tree -> id);
   bool returnBool = false;
   if (node -> id == tree -> id) {
      ///////////////////////////////
      // node ends here
      ///////////////////////////////
      if (node -> sub == NULL)
         return true;
      ///////////////////////////////
      // node does not end here, but tree does
      ///////////////////////////////
      if (tree -> sub == NULL)
         return false;
      ///////////////////////////////
      // continue exact match
      ///////////////////////////////
      return listCoveredInTree(node -> sub, tree -> sub);
   } else
   if (tree -> next != NULL) {
       if (listCoveredInTree(node, tree -> next))
          return true;
   }
   return returnBool;
}
/////////////////////////////////////////////////////////////////////////////////
/// Counts all first 0 nodes of a given tree.
/////////////////////////////////////////////////////////////////////////////////
unsigned countSITree (NODE *node)
{      
   unsigned returnVal = 0;  
   while (true) {
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0)
            returnVal += countSITree(node -> sub);
         else { 
            returnVal += 1;
            if (node -> sub -> next != NULL)
               returnVal += countSITree(node -> sub -> next); } }
      if (node -> next == NULL)
         break;    
      node = node -> next; }
   return returnVal;
}
/////////////////////////////////////////////////////////////////////////////////
/// Counts all first 0 nodes of a given tree.
/////////////////////////////////////////////////////////////////////////////////
unsigned countSITree (NODE *node, 
                      unsigned level)
{      
   unsigned returnVal = 0;  
   while (true) {
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0)
            returnVal += countSITree(node -> sub, level);
         else {                                                   
            if (level == 0)
               returnVal += 1;
            else
               returnVal += countSITree(node -> sub -> sub, level - 1);
            if (node -> sub -> next != NULL)
               returnVal += countSITree(node -> sub -> next, level); } }
      if (node -> next == NULL)
         break;    
      node = node -> next; }
   return returnVal;
}
/////////////////////////////////////////////////////////////////////////////////
/// Counts all first 0 nodes of a given tree.
/////////////////////////////////////////////////////////////////////////////////
unsigned countSITreeLinked (NODE *node, 
                            unsigned level)
{      
   unsigned returnVal = 0;  
   while (true) {
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0)
            returnVal += countSITreeLinked(node -> sub, level);
         else {                                                   
            if (level == 0) { 
               if (node -> sub -> sub != NULL)
                  returnVal += 1;
            } else
               returnVal += countSITreeLinked(node -> sub -> sub, level - 1);
            if (node -> sub -> next != NULL)
               returnVal += countSITreeLinked(node -> sub -> next, level); } }
      if (node -> next == NULL)
         break;    
      node = node -> next; }
   return returnVal;
}
/////////////////////////////////////////////////////////////////////////////////
/// Return depth of SI-tree by counting zeros
/////////////////////////////////////////////////////////////////////////////////
unsigned getDepth (NODE* aNode) {
   if (aNode -> sub == NULL)
      return 0;
   unsigned returnVal = getDepth(aNode -> sub);
   if (aNode -> id == 0)
      returnVal += 1;
   return returnVal;
}
/////////////////////////////////////////////////////////////////////////////////
/// Return distance of two nodes 
/////////////////////////////////////////////////////////////////////////////////
int getDist (NODE* aNode, 
             NODE* bNode) {
   bool debug = false;
   int returnVal = 0;
   if (debug) printf("getDist: %d %d\n", aNode -> id, bNode -> id);
   if (aNode -> id == bNode -> id) {
      if (aNode -> sub != NULL) {
         if (bNode -> sub != NULL) {
            int dist = getDist(aNode -> sub, bNode -> sub);
            ///////////////////////////////////// 
            // when dist >= 0 => return dist;
            // when node == 0 => return a length + b length
            //                   else return -1
            /////////////////////////////////////
            if (dist >= 0)
               return dist;
            if (aNode -> id == 0) {
               if (debug) printf("getDist here: %d %d\n", aNode -> id, bNode -> id);
               if (debug) printTree(aNode);
               if (debug) printf("----------\n");
               if (debug) printTree(bNode);
               unsigned aDepth = getDepth(aNode);
               unsigned bDepth = getDepth(bNode);
               if (debug) printf("depth %d %d\n", aDepth, bDepth);
               return aDepth + bDepth;
            } else
               return -1;
         } else
         /////////////////////////////////////
         // asub but no no b sub
         /////////////////////////////////////
            /////////////////////////////////////
            // when node != 0 => return a length  
            //                   else return -1
            /////////////////////////////////////
            if (aNode -> id == 0) {
               unsigned aDepth = getDepth(aNode);
               return aDepth;
               //exit(-1);
            } else
               return -1;
      } else {
         /////////////////////////////////////
         // no a sub
         /////////////////////////////////////
         if (bNode -> sub != NULL) {
            /////////////////////////////////////
            // when node != 0 => return b length  
            //                   else return -1
            /////////////////////////////////////
            if (aNode -> id == 0) {
               unsigned bDepth = getDepth(bNode);
               return bDepth;
            } else
               return -1;
         } else 
         /////////////////////////////////////
         // no a sub and no b sub => leaves
         /////////////////////////////////////
            return 0;
      }
   } else {
      /////////////////////////////////////
      // different nodes => return -1
      /////////////////////////////////////
      return -1;
   }
   return returnVal;
}
/////////////////////////////////////////////////////////////////////////////////
/// Replaces the list of all G_SI nodes with a new list of the given string.
/////////////////////////////////////////////////////////////////////////////////
void replaceSI (NODE* node, 
                string &newString) {  
  if (node -> sub -> id == G_SI) {
     deleteTree(node -> sub); 
     NODE* newNode = initNode(0);
     parser_si(newString, 0, newNode);
     node -> sub = newNode;
     return; }
  if (node -> sub != NULL) return replaceSI(node -> sub, newString);
  if (node -> next != NULL) return replaceSI(node -> next, newString);
}
/////////////////////////////////////////////////////////////////////////////////
/// Return the simple identifier string for the first relevant node 
/// in the given tree.
/////////////////////////////////////////////////////////////////////////////////
string getSI (NODE* node) {                          
   if (	(node -> id == G_SI) 								|
   		(node -> id == G_USI) 								|
  		(node -> id == G_PDVL_CLUSTER_CL_SI) 					|
  		(node -> id == G_PDVL_EVENT_IDENTIFIER_BY_NAME) 			|
  		(node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) 			|
  		(node -> id == G_PDVL_DATA_IDENTIFIER_BY_NAME) 			|
  		(node -> id == G_PDVL_TRANSACTION_AND_DATA_IDENTIFIER_BY_NAME) 			|
  		(node -> id == G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME) 	|
  		(node -> id == G_PDVL_THEOREM_IDENTIFIER_BY_NAME) 	) {
      string tmpString;
      printLexNode(tmpString, node -> sub);
      return tmpString; }
   if (node -> sub != NULL) {
      string returnString = getSI(node -> sub);
      if (returnString != "")
         return returnString;
   }
   if (node -> next != NULL) return getSI(node -> next);
   return "";
}
/////////////////////////////////////////////////////////////////////////////////
/// Search the SI tree of the given node based on an SI string
/// and return its sub node if found.
/////////////////////////////////////////////////////////////////////////////////
NODE* getTree (string &header, string signal, NODE* node) {
   NODE* typeNode = NULL;
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      for (int cnt = 0; cnt < 4; cnt++) {
         char c = (node -> id >> (8 * cnt)) & 0xff;
         if (	(	(c >= 'a') & (c <= 'z')	)	|
                  	(	(c >= 'A') & (c <= 'Z')	)	|
                  	(	(c >= '0') & (c <= '9')	)	|
                	(c == '_')						)
            thisHeader.append(1u, c);
      }
      
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0) {
            typeNode = getTree(thisHeader, signal, node -> sub);
            if (typeNode != NULL)
               return typeNode;
         } else { 
            if (thisHeader == signal) { //210108
               return getNode(node -> sub, DB_LIST_ENTRY);
            } else
            if (node -> sub -> next != NULL) {
               typeNode = getTree(thisHeader, signal, node -> sub -> next); } } }
   
      if (node -> next == NULL)
         break;    
      node = node -> next; }
   
   return typeNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Search the SI tree of the given node based on an SI
/// and return its sub node if found.
/////////////////////////////////////////////////////////////////////////////////
NODE* getSubTree (string &name, 
                  NODE* tree) {
   string tmpHeader = "";
   NODE* subNode = initNode(0);
   checkTree(name, tmpHeader, tree, subNode);
   return subNode;
}
/////////////////////////////////////////////////////////////////////////////////
/// Search the SI tree of the given node based on an node
/// and return its sub node if found.
/////////////////////////////////////////////////////////////////////////////////
NODE* getSITreeNode (NODE* cmpNode, NODE *node) { 
   bool debug = false;
   while (true) {
      if (debug) printf("compare %d %d\n", cmpNode -> id, node -> id);
      if (cmpNode -> id == node -> id) {
         // end of cmpNode
         if (cmpNode -> next == NULL) {
            // end of tree, should not happen
            if (node -> sub == NULL) {
            } else
            // not end of tree but first entry must be 0 if match
            if (node -> sub -> id != 0) {
            // found
            } else {
               if (debug) printf("found!\n");
               return node -> sub -> sub;
            }
         // continue
         } else
         if (node -> sub != NULL) {
            return getSITreeNode(cmpNode -> next, node -> sub);
         }
         return NULL;
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; }
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
/// Skip "level" number 0 identifiers within a tree.
/// Then call getSITreeNode w/o level parameter.
/// Continue as long as the called getSITreeNode function returns a valid node.
/////////////////////////////////////////////////////////////////////////////////
NODE* getSITreeNode (unsigned level, 
                     NODE* cmpNode, 
                     NODE *node) {
   bool debug = false; 
   while (true) {
      if (debug) printf("getSITreeNode level %d check %d\n", level, node -> id);
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0) {
            NODE* returnNode = getSITreeNode(level, cmpNode, node -> sub);
            if (returnNode != NULL) {
               if (debug) printf("getSITreeNode compare found.\n");
               return returnNode;
            }
         } else {
            if (level == 1) {
               if (debug) printf("getSITreeNode found 0 cont %d %d\n", cmpNode -> id, node -> sub -> sub -> sub -> id);
               NODE* returnNode = getSITreeNode(cmpNode, node -> sub -> sub);
               if (returnNode != NULL) {
                  if (debug) printf("getSITreeNode compare found.\n");
                  return returnNode;
               }
            } else {
               NODE* returnNode = getSITreeNode(level - 1, cmpNode, node -> sub);
               if (returnNode != NULL)
                  return returnNode;
            }
         }
         if (node -> sub -> next != NULL) {
            NODE* returnNode = getSITreeNode(cmpNode, node -> sub -> next);
            if (returnNode != NULL)
               return returnNode;
         }
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; 
   }
   return NULL;
}
/////////////////////////////////////////////////////////////////////////////////
/// Prints database tree.
/// Adds debug information for some key ids when appendInfo is set.
/// Beyond certain ids the string is printed.
/////////////////////////////////////////////////////////////////////////////////
void printTree (int level, 
                int max, 
                bool appendInfo, 
                NODE *node)
{        
   while (true) {
      for(int n = 0; n < level; n++)
         printf("  |");
      printf("%4d ", node -> id);  
      if (	(node -> id == G_SI) 								|
     		(node -> id == G_PDVL_CLUSTER_CL_SI)						|
     		(node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) 			|
     		(node -> id == G_PDVL_DATA_IDENTIFIER_BY_NAME) 			|
            (node -> id == G_PDVL_TRANSACTION_AND_DATA_IDENTIFIER_BY_NAME) 			|
        	(node -> id == G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME)	) {
         string tmpString;
         printLexNode(tmpString, node -> sub);
         printf("%s\n", tmpString.c_str());  
      } else {
      if (!(appendInfo))
      for (int cnt = 0; cnt < 4; cnt++) {
         char c = (node -> id >> (8 * cnt)) & 0xff;
         if (	(	(c >= 'a') & (c <= 'z')	)	|
                  	(	(c >= 'A') & (c <= 'Z')	)	|
                  	(	(c >= '0') & (c <= '9')	)	|
                	(c == '_')						)
            printf("%c", c); }
      if (appendInfo) 
      if (node -> id == DB_LIST_ENTRY) printf(" (DB_LIST_ENTRY)");
      else if (node -> id == DB_CLUSTERS) printf(" (DB_CLUSTERS)");
      else if (node -> id == DB_MODULES) printf(" (DB_MODULES)");
      else if (node -> id == DB_SUB_MODULES) printf(" (DB_SUB_MODULES)");
      else if (node -> id == DB_NAMED_PORTS) printf(" (DB_NAMED_PORTS)");
      else if (node -> id == DB_MODULE_ITEMS) printf(" (DB_MODULE_ITEMS)"); 
      else if (node -> id == DB_MODULE_REGISTERS) printf(" (DB_MODULE_REGISTERS)");
      else if (node -> id == DB_ASSIGN) printf(" (DB_ASSIGN)");
      else if (node -> id == DB_MODULE_EVENTS) printf(" (DB_MODULE_EVENTS)");
      else if (node -> id == DB_MODULE_CONDITIONS) printf(" (DB_MODULE_CONDITIONS)");
      else if (node -> id == DB_MODULE_DATAPATHS) printf(" (DB_MODULE_DATAPATHS)");
      else if (node -> id == DB_MODULE_PARAMETER) printf(" (DB_MODULE_PARAMETER)");
      else if (node -> id == DB_MODULE_TRANSACTIONS) printf(" (DB_MODULE_TRANSACTIONS)");
      else if (node -> id == DB_MODULE_ATTRIBUTES) printf(" (DB_MODULE_ATTRIBUTES)");
      else if (node -> id == DB_LHS) printf(" (DB_LHS)");
      else if (node -> id == DB_RHS) printf(" (DB_RHS)");
      else if (node -> id == DB_CONE) printf(" (DB_CONE)");
      else if (node -> id == DB_PORT_DECLARATIONS) printf(" (DB_PORT_DECLARATIONS)");
      else if (node -> id == DB_MODULE_WIRES) printf(" (DB_MODULE_WIRES)");
      else if (node -> id == DB_JOINED_CLUSTERS) printf(" (DB_JOINED_CLUSTERS)");
      else printGrammar(node -> id);
      printf("\n");
      bool subAppendInfo = appendInfo;
      if (appendInfo)
      if (	(node -> id == G_SI) 								)
         subAppendInfo = false;
      if (node -> sub != NULL)
      if ( (max == 0) |
           (level < max) )
         printTree(level + 1, max, subAppendInfo, node -> sub);
      }
      if (node -> next == NULL)
         break;    
      if (node -> next == node) { printf("printTree exit on next error.\n"); exit(-1); }
      if ( (max == 0) |
           (level < max) )
      if (node -> sub == node) { printf("printTree exit on sub error.\n"); exit(-1); }
      node = node -> next; }
}
/////////////////////////////////////////////////////////////////////////////////
/// Calls printTree and sets appendInfo.
/////////////////////////////////////////////////////////////////////////////////
void printTree (int level, 
                int max, 
                NODE *node)
{        
   printTree(level, max, true, node);
}
/////////////////////////////////////////////////////////////////////////////////
/// Calls printTree and sets appendInfo.
/////////////////////////////////////////////////////////////////////////////////
void printTree (int level, 
                NODE *node)
{        
   printTree(0, level, true, node);
}
/////////////////////////////////////////////////////////////////////////////////
/// Calls printTree and adds unlimited level parameters and sets appendInfo.
/////////////////////////////////////////////////////////////////////////////////
void printTree (NODE *node)
{        
   printTree(0, 0, true, node);
}
/////////////////////////////////////////////////////////////////////////////////
/// Converts the SI tree into string and prints them.
/// Followed by individual subtrees when printSub is set.
/////////////////////////////////////////////////////////////////////////////////
void printSITree (string &header, 
                  bool printSub, 
                  NODE *node)
{        
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      for (int cnt = 0; cnt < 4; cnt++) {
         char c = (node -> id >> (8 * cnt)) & 0xff;
         if (	(	(c >= 'a') & (c <= 'z')	)	|
                  	(	(c >= 'A') & (c <= 'Z')	)	|
                  	(	(c >= '0') & (c <= '9')	)	|
                	(c == '_')						)
            thisHeader.append(1u, c);
      }                              
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0)
            printSITree(thisHeader, printSub,node -> sub);
         else { 
            printf("   %s\n", thisHeader.c_str());
            if (printSub)
               printTree(0, node -> sub);
            if (node -> sub -> next != NULL)
               printSITree(thisHeader, printSub, node -> sub -> next); } }
      if (node -> next == NULL)
         break;    
      node = node -> next; }
}
/////////////////////////////////////////////////////////////////////////////////
/// Converts the SI tree into string and prints them.
/// Followed by "." and a second  printSITree call when printSub is set.
/////////////////////////////////////////////////////////////////////////////////
void printSITree (string &header, 
                  bool printSub, 
                  bool skip, 
                  bool skipThis, 
                  NODE *node)
{        
   while (true) {
      string thisHeader = "";
      thisHeader.append(header);
      if (!(skipThis))
      for (int cnt = 0; cnt < 4; cnt++) {
         char c = (node -> id >> (8 * cnt)) & 0xff;
         if (	(	(c >= 'a') & (c <= 'z')	)	|
                  	(	(c >= 'A') & (c <= 'Z')	)	|
                  	(	(c >= '0') & (c <= '9')	)	|
                	(c == '_')						)
            thisHeader.append(1u, c);
      }                              
      if (node -> sub != NULL) {
         if (node -> sub -> id != 0)
            printSITree(thisHeader, printSub, skip, skipThis, node -> sub);
         else { 
            if (printSub) {
               if (node -> sub -> sub != NULL) {
                  if (!skipThis)
                     thisHeader.append(".");
                  printSITree(thisHeader, printSub, skip, !skipThis, node -> sub -> sub);
               } else
                  printf("   %s\n", thisHeader.c_str());
            } else
               printf("   %s\n", thisHeader.c_str());
            if (node -> sub -> next != NULL)
               printSITree(thisHeader, printSub, skip, skipThis, node -> sub -> next); 
         } 
      }
      if (node -> next == NULL)
         break;    
      node = node -> next; }
}
/////////////////////////////////////////////////////////////////////////////////
/// Calls printSITree and sets printSub to false.
/////////////////////////////////////////////////////////////////////////////////
void printSITree (string &header, 
                  NODE *node)
{                           
   printSITree(header, false, node);
}
/////////////////////////////////////////////////////////////////////////////////
/// Calls printSITree and adds a header string and sets printSub to false.
/////////////////////////////////////////////////////////////////////////////////
void printSITree (NODE *node)
{                           
   string header = "";
   printSITree(header, false, node);
}


