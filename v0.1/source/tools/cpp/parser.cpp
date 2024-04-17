
#include <parser.h>

int parser_grammar_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_grammar_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GRAMMAR;
   return ptr;
}
int parser_grammar_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_description_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GRAMMAR;
   return ptr;
}
int parser_grammar_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_grammar_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GRAMMAR;
   return ptr;
}
int parser_grammar (string &source, int ptr, NODE *node) {
   int newPtr = parser_grammar_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_grammar_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_grammar_v2(source, ptr, node);
}
int parser_tmp_transaction_case_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_unique_priority(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_tmp_transaction_case_keyword(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_tmp_transaction_case_item_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_TMP_TRANSACTION_CASE_STATEMENT;
   return ptr;
}
int parser_tmp_transaction_case_keyword (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_TMP_TRANSACTION_CASE_KEYWORD;
   return ptr;
}
int parser_tmp_transaction_case_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_TMP_TRANSACTION_CASE_EXPRESSION;
   return ptr;
}
int parser_tmp_transaction_case_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_tmp_transaction_default_case(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_TMP_TRANSACTION_CASE_ITEM;
   return ptr;
}
int parser_tmp_transaction_case_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_tmp_transaction_item_case(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_TMP_TRANSACTION_CASE_ITEM;
   return ptr;
}
int parser_tmp_transaction_case_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_tmp_transaction_case_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_tmp_transaction_case_item_v1(source, ptr, node);
}
int parser_tmp_transaction_item_case (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_tmp_transaction_case_item_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_TMP_TRANSACTION_ITEM_CASE;
   return ptr;
}
int parser_tmp_transaction_default_case (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_TMP_TRANSACTION_DEFAULT_CASE;
   return ptr;
}
int parser_tmp_transaction_case_item_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_TMP_TRANSACTION_CASE_ITEM_EXPRESSION;
   return ptr;
}
int parser_cpp_grammar (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_preprocessing_or_declaration_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_CPP_GRAMMAR;
   return ptr;
}
int parser_preprocessing_or_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_preprocessing_file(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PREPROCESSING_OR_DECLARATION;
   return ptr;
}
int parser_preprocessing_or_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PREPROCESSING_OR_DECLARATION;
   return ptr;
}
int parser_preprocessing_or_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_preprocessing_or_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_preprocessing_or_declaration_v1(source, ptr, node);
}
int parser_cpp_function_call (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_expression_list_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_FUNCTION_CALL;
   return ptr;
}
int parser_cpp_unary_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_unary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_EXPRESSION;
   return ptr;
}
int parser_cpp_function_call_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_function_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_FUNCTION_CALL_ASSIGNMENT;
   return ptr;
}
int parser_cpp_unary_operator_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_plus(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_minus(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_nand(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_nor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_nxor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_exclamation(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_tilde(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_and(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_or(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_xor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_UNARY_OPERATOR;
   return ptr;
}
int parser_cpp_unary_operator (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_unary_operator_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_unary_operator_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_unary_operator_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_unary_operator_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_unary_operator_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_unary_operator_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_unary_operator_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_unary_operator_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_unary_operator_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_unary_operator_v9(source, ptr, node);
}
int parser_cpp_assignment_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_ASSIGNMENT_EXPRESSION;
   return ptr;
}
int parser_cpp_variable_lvalue (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_select_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_CPP_VARIABLE_LVALUE;
   return ptr;
}
int parser_cpp_expression_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_assignment_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_EXPRESSION;
   return ptr;
}
int parser_cpp_expression_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_conditional_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_EXPRESSION;
   return ptr;
}
int parser_cpp_expression_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_binary_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_EXPRESSION;
   return ptr;
}
int parser_cpp_expression_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_unary_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_EXPRESSION;
   return ptr;
}
int parser_cpp_expression_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_inc_or_dec_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_EXPRESSION;
   return ptr;
}
int parser_cpp_expression_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_EXPRESSION;
   return ptr;
}
int parser_cpp_expression_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_EXPRESSION;
   return ptr;
}
int parser_cpp_expression (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_expression_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_expression_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_expression_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_expression_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_expression_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_expression_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_expression_v6(source, ptr, node);
}
int parser_cpp_conditional_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_cond_predicate(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 63) /* ? */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_CONDITIONAL_EXPRESSION;
   return ptr;
}
int parser_cpp_cond_predicate_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_bracket_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_COND_PREDICATE;
   return ptr;
}
int parser_cpp_cond_predicate_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_COND_PREDICATE;
   return ptr;
}
int parser_cpp_cond_predicate (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_cond_predicate_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_cond_predicate_v1(source, ptr, node);
}
int parser_cpp_bracket_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_BRACKET_EXPRESSION;
   return ptr;
}
int parser_cpp_binary_expression_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_binary_expression_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_BINARY_EXPRESSION;
   return ptr;
}
int parser_cpp_binary_expression_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_binary_expression_unary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_BINARY_EXPRESSION;
   return ptr;
}
int parser_cpp_binary_expression (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_binary_expression_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_binary_expression_v1(source, ptr, node);
}
int parser_cpp_binary_expression_primary (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_BINARY_EXPRESSION_PRIMARY;
   return ptr;
}
int parser_cpp_binary_expression_unary (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_unary_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_BINARY_EXPRESSION_UNARY;
   return ptr;
}
int parser_cpp_primary_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_function_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PRIMARY;
   return ptr;
}
int parser_cpp_primary_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_bracket_mintypmax_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PRIMARY;
   return ptr;
}
int parser_cpp_primary_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_identifier_select(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PRIMARY;
   return ptr;
}
int parser_cpp_primary_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_primary_literal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PRIMARY;
   return ptr;
}
int parser_cpp_primary (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_primary_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_primary_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_primary_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_primary_v3(source, ptr, node);
}
int parser_cpp_primary_literal (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PRIMARY_LITERAL;
   return ptr;
}
int parser_cpp_bracket_mintypmax_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_mintypmax_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_BRACKET_MINTYPMAX_EXPRESSION;
   return ptr;
}
int parser_cpp_mintypmax_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_MINTYPMAX_EXPRESSION;
   return ptr;
}
int parser_cpp_identifier_select (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_asterisk_identifier(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_cpp_ampersand_identifier(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_cpp_select_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_CPP_IDENTIFIER_SELECT;
   return ptr;
}
int parser_cpp_asterisk_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_CPP_ASTERISK_IDENTIFIER;
   return ptr;
}
int parser_cpp_ampersand_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 38) /* & */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_CPP_AMPERSAND_IDENTIFIER;
   return ptr;
}
int parser_cpp_select (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_SELECT;
   return ptr;
}
int parser_cpp_expression_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_EXPRESSION_LIST;
   return ptr;
}
int parser_cpp_unsigned_number (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 48) /* 0 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 120) /* x */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_hex_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 85) /* U */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_UNSIGNED_NUMBER;
   return ptr;
}
int parser_cpp_hex_value_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_hex_value_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_HEX_VALUE;
   return ptr;
}
int parser_cpp_hex_value_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_hex_value_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_HEX_VALUE;
   return ptr;
}
int parser_cpp_hex_value (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_hex_value_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_hex_value_v1(source, ptr, node);
}
int parser_cpp_hex_value_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hex_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_hex_value(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_CPP_HEX_VALUE_PREV0;
   return ptr;
}
int parser_cpp_hex_value_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_us_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_hex_value(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_CPP_HEX_VALUE_PREV1;
   return ptr;
}
int parser_cpp_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_compound_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_empty_compound_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_selection_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_labeled_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_function_call_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_ref_expression_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_break_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_declaration_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_return_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_STATEMENT;
   return ptr;
}
int parser_cpp_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_statement_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_statement_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_statement_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_statement_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_statement_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_statement_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_statement_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_statement_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_statement_v9(source, ptr, node);
}
int parser_condition (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CONDITION;
   return ptr;
}
int parser_cpp_declaration_statement_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_DECLARATION_STATEMENT_H0;
   return ptr;
}
int parser_cpp_declaration_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_declaration_statement_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_DECLARATION_STATEMENT;
   return ptr;
}
int parser_cpp_return_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_RETURN_STATEMENT;
   return ptr;
}
int parser_cpp_labeled_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_labeled_default_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_LABELED_STATEMENT;
   return ptr;
}
int parser_cpp_labeled_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_labeled_case_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_LABELED_STATEMENT;
   return ptr;
}
int parser_cpp_labeled_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_labeled_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_labeled_statement_v1(source, ptr, node);
}
int parser_cpp_labeled_case_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_statement_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_CPP_LABELED_CASE_STATEMENT;
   return ptr;
}
int parser_cpp_labeled_default_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_statement_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_CPP_LABELED_DEFAULT_STATEMENT;
   return ptr;
}
int parser_cpp_break_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 107) /* k */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_CPP_BREAK_STATEMENT;
   return ptr;
}
int parser_cpp_expression_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_EXPRESSION_STATEMENT;
   return ptr;
}
int parser_cpp_ref_expression_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_REF_EXPRESSION_STATEMENT;
   return ptr;
}
int parser_cpp_compound_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_cpp_statement_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_COMPOUND_STATEMENT;
   return ptr;
}
int parser_cpp_empty_compound_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_CPP_EMPTY_COMPOUND_STATEMENT;
   return ptr;
}
int parser_cpp_selection_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_if_else_selection_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_SELECTION_STATEMENT;
   return ptr;
}
int parser_cpp_selection_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_if_selection_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_SELECTION_STATEMENT;
   return ptr;
}
int parser_cpp_selection_statement_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_case_selection_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_SELECTION_STATEMENT;
   return ptr;
}
int parser_cpp_selection_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_selection_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_selection_statement_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_selection_statement_v2(source, ptr, node);
}
int parser_cpp_if_else_selection_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_IF_ELSE_SELECTION_STATEMENT;
   return ptr;
}
int parser_cpp_if_selection_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_IF_SELECTION_STATEMENT;
   return ptr;
}
int parser_cpp_case_selection_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_CASE_SELECTION_STATEMENT;
   return ptr;
}
int parser_cpp_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_template_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_DECLARATION;
   return ptr;
}
int parser_decl_specifier_seq (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECL_SPECIFIER_SEQ;
   return ptr;
}
int parser_declarator (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_parameters_and_qualifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_DECLARATOR;
   return ptr;
}
int parser_parameters_and_qualifiers (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_parameter_declaration_clause(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PARAMETERS_AND_QUALIFIERS;
   return ptr;
}
int parser_parameter_declaration_clause_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_parameter_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PARAMETER_DECLARATION_CLAUSE_H0;
   return ptr;
}
int parser_parameter_declaration_clause (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_parameter_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_parameter_declaration_clause_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_PARAMETER_DECLARATION_CLAUSE;
   return ptr;
}
int parser_cpp_parameter_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_parameter_declaration_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PARAMETER_DECLARATION;
   return ptr;
}
int parser_cpp_parameter_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_parameter_declaration_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PARAMETER_DECLARATION;
   return ptr;
}
int parser_cpp_parameter_declaration_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_parameter_declaration_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PARAMETER_DECLARATION;
   return ptr;
}
int parser_cpp_parameter_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_cpp_parameter_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_cpp_parameter_declaration_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_cpp_parameter_declaration_v2(source, ptr, node);
}
int parser_cpp_parameter_declaration_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PARAMETER_DECLARATION_PREV0;
   return ptr;
}
int parser_cpp_parameter_declaration_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_PARAMETER_DECLARATION_PREV1;
   return ptr;
}
int parser_cpp_parameter_declaration_prev2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_CPP_PARAMETER_DECLARATION_PREV2;
   return ptr;
}
int parser_template_declaration_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_TEMPLATE_DECLARATION_H0;
   return ptr;
}
int parser_template_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_decl_specifier_seq(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_template_declaration_h0(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_declarator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_function_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_TEMPLATE_DECLARATION;
   return ptr;
}
int parser_function_body (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_compound_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_FUNCTION_BODY;
   return ptr;
}
int parser_preprocessing_file (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_group(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PREPROCESSING_FILE;
   return ptr;
}
int parser_group (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_group_part(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GROUP;
   return ptr;
}
int parser_group_part (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_control_line(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GROUP_PART;
   return ptr;
}
int parser_control_line (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 35) /* # */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_h_pp_tokens(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_CONTROL_LINE;
   return ptr;
}
int parser_h_pp_tokens (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_header_name_tokens(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_H_PP_TOKENS;
   return ptr;
}
int parser_header_name_tokens (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_HEADER_NAME_TOKENS;
   return ptr;
}
int parser_sv_library_text (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_library_description(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIBRARY_TEXT;
   return ptr;
}
int parser_sv_library_description (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_include_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIBRARY_DESCRIPTION;
   return ptr;
}
int parser_sv_include_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 96) /* ` */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_file_path_spec(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INCLUDE_STATEMENT;
   return ptr;
}
int parser_sv_file_path_spec_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FILE_PATH_SPEC_H1;
   return ptr;
}
int parser_sv_file_path_spec (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 34) /* " */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_file_path_spec_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 34) /* " */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_FILE_PATH_SPEC;
   return ptr;
}
int parser_sv_description_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DESCRIPTION;
   return ptr;
}
int parser_sv_description_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_library_text(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DESCRIPTION;
   return ptr;
}
int parser_sv_description (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_description_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_description_v1(source, ptr, node);
}
int parser_sv_module_ansi_header (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_keyword(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_port_declarations(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_MODULE_ANSI_HEADER;
   return ptr;
}
int parser_sv_module_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_ansi_header(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_non_port_module_item_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_MODULE_DECLARATION;
   return ptr;
}
int parser_sv_module_keyword (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_MODULE_KEYWORD;
   return ptr;
}
int parser_sv_list_of_ports_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PORTS_H0;
   return ptr;
}
int parser_sv_list_of_ports (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_ports_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_LIST_OF_PORTS;
   return ptr;
}
int parser_sv_list_of_port_declarations_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_ansi_port_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PORT_DECLARATIONS_H1;
   return ptr;
}
int parser_sv_list_of_port_declarations (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_ansi_port_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_port_declarations_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_PORT_DECLARATIONS;
   return ptr;
}
int parser_sv_port_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_inout_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_DECLARATION;
   return ptr;
}
int parser_sv_port_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_input_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_DECLARATION;
   return ptr;
}
int parser_sv_port_declaration_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_output_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_DECLARATION;
   return ptr;
}
int parser_sv_port_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_port_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_port_declaration_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_port_declaration_v2(source, ptr, node);
}
int parser_sv_port_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT;
   return ptr;
}
int parser_sv_port_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT;
   return ptr;
}
int parser_sv_port (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_port_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_port_v1(source, ptr, node);
}
int parser_sv_port_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_PREV0;
   return ptr;
}
int parser_sv_port_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_PORT_PREV1;
   return ptr;
}
int parser_sv_port_expression_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_expression_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_EXPRESSION;
   return ptr;
}
int parser_sv_port_expression_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_expression_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_EXPRESSION;
   return ptr;
}
int parser_sv_port_expression (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_port_expression_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_port_expression_v1(source, ptr, node);
}
int parser_sv_port_expression_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_reference(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_EXPRESSION_PREV0;
   return ptr;
}
int parser_sv_port_expression_prev1_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_reference(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_EXPRESSION_PREV1_H0;
   return ptr;
}
int parser_sv_port_expression_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_reference(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_port_expression_prev1_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_PORT_EXPRESSION_PREV1;
   return ptr;
}
int parser_sv_port_reference (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_select(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_REFERENCE;
   return ptr;
}
int parser_sv_port_direction_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_input_direction(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_DIRECTION;
   return ptr;
}
int parser_sv_port_direction_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_output_direction(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_DIRECTION;
   return ptr;
}
int parser_sv_port_direction_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_inout_direction(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_DIRECTION;
   return ptr;
}
int parser_sv_port_direction (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_port_direction_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_port_direction_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_port_direction_v2(source, ptr, node);
}
int parser_sv_port_input_direction (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_PORT_INPUT_DIRECTION;
   return ptr;
}
int parser_sv_port_output_direction (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_PORT_OUTPUT_DIRECTION;
   return ptr;
}
int parser_sv_port_inout_direction (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_PORT_INOUT_DIRECTION;
   return ptr;
}
int parser_sv_ansi_port_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ANSI_PORT_DECLARATION;
   return ptr;
}
int parser_sv_module_common_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_or_generate_item_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_COMMON_ITEM;
   return ptr;
}
int parser_sv_module_common_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_continuous_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_COMMON_ITEM;
   return ptr;
}
int parser_sv_module_common_item_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_always_construct(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_COMMON_ITEM;
   return ptr;
}
int parser_sv_module_common_item_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_generate_construct(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_COMMON_ITEM;
   return ptr;
}
int parser_sv_module_common_item_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_conditional_generate_construct(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_COMMON_ITEM;
   return ptr;
}
int parser_sv_module_common_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_module_common_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_module_common_item_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_module_common_item_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_module_common_item_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_module_common_item_v4(source, ptr, node);
}
int parser_sv_module_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_ITEM;
   return ptr;
}
int parser_sv_module_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_non_port_module_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_ITEM;
   return ptr;
}
int parser_sv_module_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_module_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_module_item_v1(source, ptr, node);
}
int parser_sv_module_or_generate_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_parameter_override(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_OR_GENERATE_ITEM;
   return ptr;
}
int parser_sv_module_or_generate_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_param_instantiation(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_OR_GENERATE_ITEM;
   return ptr;
}
int parser_sv_module_or_generate_item_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_instantiation(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_OR_GENERATE_ITEM;
   return ptr;
}
int parser_sv_module_or_generate_item_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_common_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_OR_GENERATE_ITEM;
   return ptr;
}
int parser_sv_module_or_generate_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_module_or_generate_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_module_or_generate_item_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_module_or_generate_item_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_module_or_generate_item_v3(source, ptr, node);
}
int parser_sv_module_or_generate_item_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_package_or_generate_item_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_OR_GENERATE_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_non_port_module_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NON_PORT_MODULE_ITEM;
   return ptr;
}
int parser_sv_non_port_module_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_region(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NON_PORT_MODULE_ITEM;
   return ptr;
}
int parser_sv_non_port_module_item_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_or_generate_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NON_PORT_MODULE_ITEM;
   return ptr;
}
int parser_sv_non_port_module_item_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_include_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NON_PORT_MODULE_ITEM;
   return ptr;
}
int parser_sv_non_port_module_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_non_port_module_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_non_port_module_item_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_non_port_module_item_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_non_port_module_item_v3(source, ptr, node);
}
int parser_sv_parameter_override (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_defparam_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_PARAMETER_OVERRIDE;
   return ptr;
}
int parser_sv_package_or_generate_item_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PACKAGE_OR_GENERATE_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_package_or_generate_item_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PACKAGE_OR_GENERATE_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_package_or_generate_item_declaration_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PACKAGE_OR_GENERATE_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_package_or_generate_item_declaration_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PACKAGE_OR_GENERATE_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_package_or_generate_item_declaration_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_parameter_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PACKAGE_OR_GENERATE_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_package_or_generate_item_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_package_or_generate_item_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_package_or_generate_item_declaration_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_package_or_generate_item_declaration_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_package_or_generate_item_declaration_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_package_or_generate_item_declaration_v4(source, ptr, node);
}
int parser_sv_parameter_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_param_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_PARAMETER_DECLARATION;
   return ptr;
}
int parser_sv_inout_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_inout_type_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INOUT_DECLARATION;
   return ptr;
}
int parser_sv_inout_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_inout_implicit_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INOUT_DECLARATION;
   return ptr;
}
int parser_sv_inout_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_inout_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_inout_declaration_v1(source, ptr, node);
}
int parser_sv_inout_type_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_port_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_INOUT_TYPE_DECLARATION;
   return ptr;
}
int parser_sv_inout_implicit_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_INOUT_IMPLICIT_DECLARATION;
   return ptr;
}
int parser_sv_input_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_input_type_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INPUT_DECLARATION;
   return ptr;
}
int parser_sv_input_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_input_implicit_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INPUT_DECLARATION;
   return ptr;
}
int parser_sv_input_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_input_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_input_declaration_v1(source, ptr, node);
}
int parser_sv_input_type_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_port_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_INPUT_TYPE_DECLARATION;
   return ptr;
}
int parser_sv_input_implicit_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_INPUT_IMPLICIT_DECLARATION;
   return ptr;
}
int parser_sv_output_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_output_type_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OUTPUT_DECLARATION;
   return ptr;
}
int parser_sv_output_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_output_implicit_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OUTPUT_DECLARATION;
   return ptr;
}
int parser_sv_output_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_output_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_output_declaration_v1(source, ptr, node);
}
int parser_sv_output_type_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_port_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_OUTPUT_TYPE_DECLARATION;
   return ptr;
}
int parser_sv_output_implicit_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_OUTPUT_IMPLICIT_DECLARATION;
   return ptr;
}
int parser_sv_data_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_variable_decl_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_DATA_DECLARATION;
   return ptr;
}
int parser_sv_net_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_type_declaration_split_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NET_DECLARATION;
   return ptr;
}
int parser_sv_net_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_declaration_split_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NET_DECLARATION;
   return ptr;
}
int parser_sv_net_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_net_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_net_declaration_v1(source, ptr, node);
}
int parser_sv_net_type_declaration_split_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_net_decl_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_NET_TYPE_DECLARATION_SPLIT_TYPE;
   return ptr;
}
int parser_sv_net_declaration_split_implicit (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_net_decl_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_NET_DECLARATION_SPLIT_IMPLICIT;
   return ptr;
}
int parser_sv_type_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_type_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_variable_dimension_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_TYPE_DECLARATION;
   return ptr;
}
int parser_sv_data_type_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE;
   return ptr;
}
int parser_sv_data_type_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE;
   return ptr;
}
int parser_sv_data_type_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE;
   return ptr;
}
int parser_sv_data_type_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_prev3(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE;
   return ptr;
}
int parser_sv_data_type_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_prev4(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE;
   return ptr;
}
int parser_sv_data_type (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_data_type_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_data_type_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_data_type_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_data_type_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_data_type_v4(source, ptr, node);
}
int parser_sv_data_type_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_vector_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_packed_dimension_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_DATA_TYPE_PREV0;
   return ptr;
}
int parser_sv_data_type_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_struct_union_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE_PREV1;
   return ptr;
}
int parser_sv_data_type_prev2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_enum_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE_PREV2;
   return ptr;
}
int parser_sv_data_type_prev3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_atom_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE_PREV3;
   return ptr;
}
int parser_sv_data_type_prev4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_type_identifier_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE_PREV4;
   return ptr;
}
int parser_sv_integer_struct_union_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_struct_union(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_packed_keyword(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_struct_union_member_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_INTEGER_STRUCT_UNION_TYPE;
   return ptr;
}
int parser_sv_packed_keyword (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 107) /* k */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_PACKED_KEYWORD;
   return ptr;
}
int parser_sv_integer_enum_type (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_enum_base_type(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_enum_name_declaration_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_INTEGER_ENUM_TYPE;
   return ptr;
}
int parser_sv_integer_type_identifier_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_class_scope(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_type_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGER_TYPE_IDENTIFIER_TYPE;
   return ptr;
}
int parser_sv_data_type_or_implicit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE_OR_IMPLICIT;
   return ptr;
}
int parser_sv_data_type_or_implicit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_implicit_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE_OR_IMPLICIT;
   return ptr;
}
int parser_sv_data_type_or_implicit (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_data_type_or_implicit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_data_type_or_implicit_v1(source, ptr, node);
}
int parser_sv_implicit_data_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_packed_dimension_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IMPLICIT_DATA_TYPE;
   return ptr;
}
int parser_sv_enum_base_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_vector_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_packed_dimension_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_ENUM_BASE_TYPE;
   return ptr;
}
int parser_sv_enum_name_declaration_list_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ENUM_NAME_DECLARATION_LIST_H0;
   return ptr;
}
int parser_sv_enum_name_declaration_list_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_enum_name_declaration_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ENUM_NAME_DECLARATION_LIST_H1;
   return ptr;
}
int parser_sv_enum_name_declaration_list (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_enum_name_declaration_list_h0(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_enum_name_declaration_list_h1(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_ENUM_NAME_DECLARATION_LIST;
   return ptr;
}
int parser_sv_class_scope (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_class_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_CLASS_SCOPE;
   return ptr;
}
int parser_sv_class_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_class_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CLASS_TYPE;
   return ptr;
}
int parser_sv_integer_atom_type (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_INTEGER_ATOM_TYPE;
   return ptr;
}
int parser_sv_integer_vector_type_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_vector_type_bit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGER_VECTOR_TYPE;
   return ptr;
}
int parser_sv_integer_vector_type_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_vector_type_logic(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGER_VECTOR_TYPE;
   return ptr;
}
int parser_sv_integer_vector_type_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_vector_type_reg(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGER_VECTOR_TYPE;
   return ptr;
}
int parser_sv_integer_vector_type (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_integer_vector_type_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_integer_vector_type_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_integer_vector_type_v2(source, ptr, node);
}
int parser_sv_integer_vector_type_bit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_INTEGER_VECTOR_TYPE_BIT;
   return ptr;
}
int parser_sv_integer_vector_type_logic (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_INTEGER_VECTOR_TYPE_LOGIC;
   return ptr;
}
int parser_sv_integer_vector_type_reg (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_INTEGER_VECTOR_TYPE_REG;
   return ptr;
}
int parser_sv_net_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_type_split_wire(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NET_TYPE;
   return ptr;
}
int parser_sv_net_type_split_wire (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_NET_TYPE_SPLIT_WIRE;
   return ptr;
}
int parser_sv_net_port_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NET_PORT_TYPE;
   return ptr;
}
int parser_sv_struct_union_member (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_variable_dimension_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_STRUCT_UNION_MEMBER;
   return ptr;
}
int parser_sv_data_type_or_void_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DATA_TYPE_OR_VOID;
   return ptr;
}
int parser_sv_data_type_or_void_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 118) /* v */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_DATA_TYPE_OR_VOID;
   return ptr;
}
int parser_sv_data_type_or_void (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_data_type_or_void_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_data_type_or_void_v1(source, ptr, node);
}
int parser_sv_struct_union_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_struct(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STRUCT_UNION;
   return ptr;
}
int parser_sv_struct_union_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_union(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STRUCT_UNION;
   return ptr;
}
int parser_sv_struct_union (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_struct_union_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_struct_union_v1(source, ptr, node);
}
int parser_sv_struct (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_STRUCT;
   return ptr;
}
int parser_sv_union (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_UNION;
   return ptr;
}
int parser_sv_delay_value (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DELAY_VALUE;
   return ptr;
}
int parser_sv_list_of_defparam_assignments (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_defparam_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_DEFPARAM_ASSIGNMENTS;
   return ptr;
}
int parser_sv_list_of_net_decl_assignments_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_decl_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_NET_DECL_ASSIGNMENTS_H0;
   return ptr;
}
int parser_sv_list_of_net_decl_assignments (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_decl_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_net_decl_assignments_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_NET_DECL_ASSIGNMENTS;
   return ptr;
}
int parser_sv_list_of_param_assignments (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_param_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PARAM_ASSIGNMENTS;
   return ptr;
}
int parser_sv_list_of_port_identifiers_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PORT_IDENTIFIERS_H1;
   return ptr;
}
int parser_sv_list_of_port_identifiers (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_unpacked_dimension_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_list_of_port_identifiers_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_PORT_IDENTIFIERS;
   return ptr;
}
int parser_sv_list_of_tf_variable_identifiers_h2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_TF_VARIABLE_IDENTIFIERS_H2;
   return ptr;
}
int parser_sv_list_of_tf_variable_identifiers (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_tf_variable_identifiers_h2_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_TF_VARIABLE_IDENTIFIERS;
   return ptr;
}
int parser_sv_list_of_variable_decl_assignments_h3 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_decl_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_VARIABLE_DECL_ASSIGNMENTS_H3;
   return ptr;
}
int parser_sv_list_of_variable_decl_assignments (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_decl_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_variable_decl_assignments_h3_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_VARIABLE_DECL_ASSIGNMENTS;
   return ptr;
}
int parser_sv_defparam_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_parameter_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_param_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DEFPARAM_ASSIGNMENT;
   return ptr;
}
int parser_sv_net_decl_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_net_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_unpacked_dimension_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_blocking_assign_expression(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_NET_DECL_ASSIGNMENT;
   return ptr;
}
int parser_sv_param_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_param_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PARAM_ASSIGNMENT;
   return ptr;
}
int parser_sv_variable_decl_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_variable_dimension_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_VARIABLE_DECL_ASSIGNMENT;
   return ptr;
}
int parser_sv_unpacked_dimension_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unpacked_dimension_constant_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNPACKED_DIMENSION;
   return ptr;
}
int parser_sv_unpacked_dimension_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unpacked_dimension_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNPACKED_DIMENSION;
   return ptr;
}
int parser_sv_unpacked_dimension (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_unpacked_dimension_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_unpacked_dimension_v1(source, ptr, node);
}
int parser_sv_unpacked_dimension_constant_range (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_UNPACKED_DIMENSION_CONSTANT_RANGE;
   return ptr;
}
int parser_sv_unpacked_dimension_constant_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_UNPACKED_DIMENSION_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_sv_packed_dimension_list (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_packed_dimension(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_packed_dimension_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_PACKED_DIMENSION_LIST;
   return ptr;
}
int parser_sv_packed_dimension (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_PACKED_DIMENSION;
   return ptr;
}
int parser_sv_variable_dimension (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unpacked_dimension(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_VARIABLE_DIMENSION;
   return ptr;
}
int parser_sv_function_data_type_or_implicit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_or_void(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_DATA_TYPE_OR_IMPLICIT;
   return ptr;
}
int parser_sv_function_data_type_or_implicit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_implicit_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_DATA_TYPE_OR_IMPLICIT;
   return ptr;
}
int parser_sv_function_data_type_or_implicit (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_function_data_type_or_implicit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_function_data_type_or_implicit_v1(source, ptr, node);
}
int parser_sv_function_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_body_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_DECLARATION;
   return ptr;
}
int parser_sv_function_body_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_body_declaration_item_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_BODY_DECLARATION;
   return ptr;
}
int parser_sv_function_body_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_body_declaration_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_BODY_DECLARATION;
   return ptr;
}
int parser_sv_function_body_declaration_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_body_declaration_port_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_BODY_DECLARATION;
   return ptr;
}
int parser_sv_function_body_declaration_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_body_declaration_port(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_BODY_DECLARATION;
   return ptr;
}
int parser_sv_function_body_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_function_body_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_function_body_declaration_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_function_body_declaration_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_function_body_declaration_v3(source, ptr, node);
}
int parser_sv_function_body_declaration_item_implicit (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_tf_item_declaration_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_FUNCTION_BODY_DECLARATION_ITEM_IMPLICIT;
   return ptr;
}
int parser_sv_function_body_declaration_item (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_tf_item_declaration_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_FUNCTION_BODY_DECLARATION_ITEM;
   return ptr;
}
int parser_sv_function_body_declaration_port_implicit_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_BODY_DECLARATION_PORT_IMPLICIT_H0;
   return ptr;
}
int parser_sv_function_body_declaration_port_implicit (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_function_body_declaration_port_implicit_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_tf_item_declaration_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_FUNCTION_BODY_DECLARATION_PORT_IMPLICIT;
   return ptr;
}
int parser_sv_function_body_declaration_port_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_BODY_DECLARATION_PORT_H1;
   return ptr;
}
int parser_sv_function_body_declaration_port (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_function_body_declaration_port_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_tf_item_declaration_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_FUNCTION_BODY_DECLARATION_PORT;
   return ptr;
}
int parser_sv_task_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 107) /* k */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_body_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_DECLARATION;
   return ptr;
}
int parser_sv_task_body_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_body_declaration_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_BODY_DECLARATION;
   return ptr;
}
int parser_sv_task_body_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_body_declaration_port(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_BODY_DECLARATION;
   return ptr;
}
int parser_sv_task_body_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_task_body_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_task_body_declaration_v1(source, ptr, node);
}
int parser_sv_task_body_declaration_item (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_tf_item_declaration_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 107) /* k */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_TASK_BODY_DECLARATION_ITEM;
   return ptr;
}
int parser_sv_task_body_declaration_port_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_port_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_BODY_DECLARATION_PORT_H0;
   return ptr;
}
int parser_sv_task_body_declaration_port (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_port_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_task_body_declaration_port_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_tf_item_declaration_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 107) /* k */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_TASK_BODY_DECLARATION_PORT;
   return ptr;
}
int parser_sv_tf_item_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_port_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TF_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_tf_item_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_parameter_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TF_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_tf_item_declaration_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TF_ITEM_DECLARATION;
   return ptr;
}
int parser_sv_tf_item_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_tf_item_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_tf_item_declaration_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_tf_item_declaration_v2(source, ptr, node);
}
int parser_sv_function_port_list_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_PORT_LIST;
   return ptr;
}
int parser_sv_function_port_list_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_PORT_LIST;
   return ptr;
}
int parser_sv_function_port_list (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_function_port_list_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_function_port_list_v1(source, ptr, node);
}
int parser_sv_task_port_list_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_port_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_PORT_LIST;
   return ptr;
}
int parser_sv_task_port_list_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_PORT_LIST;
   return ptr;
}
int parser_sv_task_port_list (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_task_port_list_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_task_port_list_v1(source, ptr, node);
}
int parser_sv_function_port_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_item_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_PORT_ITEM;
   return ptr;
}
int parser_sv_function_port_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_item_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_PORT_ITEM;
   return ptr;
}
int parser_sv_function_port_item_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_item_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_PORT_ITEM;
   return ptr;
}
int parser_sv_function_port_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_function_port_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_function_port_item_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_function_port_item_v2(source, ptr, node);
}
int parser_sv_function_port_item_prev0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_PORT_ITEM_PREV0;
   return ptr;
}
int parser_sv_function_port_item_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_PORT_ITEM_PREV1;
   return ptr;
}
int parser_sv_function_port_item_prev2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_PORT_ITEM_PREV2;
   return ptr;
}
int parser_sv_task_port_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_port_item_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_PORT_ITEM;
   return ptr;
}
int parser_sv_task_port_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_task_port_item_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_PORT_ITEM;
   return ptr;
}
int parser_sv_task_port_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_task_port_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_task_port_item_v1(source, ptr, node);
}
int parser_sv_task_port_item_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_direction(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_PORT_ITEM_PREV0;
   return ptr;
}
int parser_sv_task_port_item_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_direction(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TASK_PORT_ITEM_PREV1;
   return ptr;
}
int parser_sv_tf_port_direction (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_direction(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TF_PORT_DIRECTION;
   return ptr;
}
int parser_sv_tf_port_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_port_declaration_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TF_PORT_DECLARATION;
   return ptr;
}
int parser_sv_tf_port_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_port_declaration_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TF_PORT_DECLARATION;
   return ptr;
}
int parser_sv_tf_port_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_tf_port_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_tf_port_declaration_v1(source, ptr, node);
}
int parser_sv_tf_port_declaration_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_port_direction(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_data_type_or_implicit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_tf_variable_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_TF_PORT_DECLARATION_PREV0;
   return ptr;
}
int parser_sv_tf_port_declaration_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_port_direction(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_tf_variable_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_TF_PORT_DECLARATION_PREV1;
   return ptr;
}
int parser_sv_module_instantiation_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_instance(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_INSTANTIATION_H0;
   return ptr;
}
int parser_sv_module_instantiation (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_instance(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_module_instantiation_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_MODULE_INSTANTIATION;
   return ptr;
}
int parser_sv_module_param_instantiation_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_instance(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_PARAM_INSTANTIATION_H1;
   return ptr;
}
int parser_sv_module_param_instantiation (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_parameter_value_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_instance(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_module_param_instantiation_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_MODULE_PARAM_INSTANTIATION;
   return ptr;
}
int parser_sv_parameter_value_assignment (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 35) /* # */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_parameter_assignments(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_PARAMETER_VALUE_ASSIGNMENT;
   return ptr;
}
int parser_sv_list_of_parameter_assignments_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_named_list_of_parameter_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PARAMETER_ASSIGNMENTS;
   return ptr;
}
int parser_sv_list_of_parameter_assignments_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_ordered_list_of_parameter_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PARAMETER_ASSIGNMENTS;
   return ptr;
}
int parser_sv_list_of_parameter_assignments (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_list_of_parameter_assignments_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_list_of_parameter_assignments_v1(source, ptr, node);
}
int parser_sv_named_list_of_parameter_assignments_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_named_list_of_parameter_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NAMED_LIST_OF_PARAMETER_ASSIGNMENTS_H0;
   return ptr;
}
int parser_sv_named_list_of_parameter_assignments (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_named_parameter_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_named_list_of_parameter_assignments_h0(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_NAMED_LIST_OF_PARAMETER_ASSIGNMENTS;
   return ptr;
}
int parser_sv_ordered_list_of_parameter_assignments_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_ordered_list_of_parameter_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ORDERED_LIST_OF_PARAMETER_ASSIGNMENTS_H1;
   return ptr;
}
int parser_sv_ordered_list_of_parameter_assignments (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_ordered_parameter_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_ordered_list_of_parameter_assignments_h1(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_ORDERED_LIST_OF_PARAMETER_ASSIGNMENTS;
   return ptr;
}
int parser_sv_named_parameter_assignment (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_expression(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_NAMED_PARAMETER_ASSIGNMENT;
   return ptr;
}
int parser_sv_ordered_parameter_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ORDERED_PARAMETER_ASSIGNMENT;
   return ptr;
}
int parser_sv_hierarchical_instance (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_name_of_instance(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_port_connections(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_HIERARCHICAL_INSTANCE;
   return ptr;
}
int parser_sv_name_of_instance (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_instance_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NAME_OF_INSTANCE;
   return ptr;
}
int parser_sv_list_of_port_connections_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_connections_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PORT_CONNECTIONS;
   return ptr;
}
int parser_sv_list_of_port_connections_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_port_connections_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PORT_CONNECTIONS;
   return ptr;
}
int parser_sv_list_of_port_connections (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_list_of_port_connections_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_list_of_port_connections_v1(source, ptr, node);
}
int parser_sv_list_of_port_connections_prev0_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_ordered_port_connection(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PORT_CONNECTIONS_PREV0_H0;
   return ptr;
}
int parser_sv_list_of_port_connections_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_ordered_port_connection(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_port_connections_prev0_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_PORT_CONNECTIONS_PREV0;
   return ptr;
}
int parser_sv_list_of_port_connections_prev1_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_named_port_connection(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_PORT_CONNECTIONS_PREV1_H1;
   return ptr;
}
int parser_sv_list_of_port_connections_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_named_port_connection(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_port_connections_prev1_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_PORT_CONNECTIONS_PREV1;
   return ptr;
}
int parser_sv_ordered_port_connection (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ORDERED_PORT_CONNECTION;
   return ptr;
}
int parser_sv_named_port_connection (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_port_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_expression(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_NAMED_PORT_CONNECTION;
   return ptr;
}
int parser_sv_generate_region (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_generate_item_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_GENERATE_REGION;
   return ptr;
}
int parser_sv_loop_generate_construct (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_initialization(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_iteration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_GENERATE_CONSTRUCT;
   return ptr;
}
int parser_sv_genvar_initialization (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENVAR_INITIALIZATION;
   return ptr;
}
int parser_sv_genvar_iteration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_iteration_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENVAR_ITERATION;
   return ptr;
}
int parser_sv_genvar_iteration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_iteration_inc_or_dec(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENVAR_ITERATION;
   return ptr;
}
int parser_sv_genvar_iteration (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_genvar_iteration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_genvar_iteration_v1(source, ptr, node);
}
int parser_sv_genvar_iteration_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENVAR_ITERATION_ASSIGNMENT;
   return ptr;
}
int parser_sv_genvar_iteration_inc_or_dec (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_inc_or_dec_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENVAR_ITERATION_INC_OR_DEC;
   return ptr;
}
int parser_sv_conditional_generate_construct_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_if_generate_construct(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONDITIONAL_GENERATE_CONSTRUCT;
   return ptr;
}
int parser_sv_conditional_generate_construct_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_generate_construct(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONDITIONAL_GENERATE_CONSTRUCT;
   return ptr;
}
int parser_sv_conditional_generate_construct (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_conditional_generate_construct_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_conditional_generate_construct_v1(source, ptr, node);
}
int parser_sv_if_generate_construct_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_if_generate_construct_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IF_GENERATE_CONSTRUCT;
   return ptr;
}
int parser_sv_if_generate_construct_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_if_generate_construct_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IF_GENERATE_CONSTRUCT;
   return ptr;
}
int parser_sv_if_generate_construct_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_if_generate_construct_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IF_GENERATE_CONSTRUCT;
   return ptr;
}
int parser_sv_if_generate_construct (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_if_generate_construct_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_if_generate_construct_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_if_generate_construct_v2(source, ptr, node);
}
int parser_sv_if_generate_construct_prev0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_if_generate_construct(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IF_GENERATE_CONSTRUCT_PREV0;
   return ptr;
}
int parser_sv_if_generate_construct_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IF_GENERATE_CONSTRUCT_PREV1;
   return ptr;
}
int parser_sv_if_generate_construct_prev2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IF_GENERATE_CONSTRUCT_PREV2;
   return ptr;
}
int parser_sv_case_generate_construct (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_case_generate_item_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_CASE_GENERATE_CONSTRUCT;
   return ptr;
}
int parser_sv_case_generate_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_generate_item_default_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_GENERATE_ITEM;
   return ptr;
}
int parser_sv_case_generate_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_generate_item_default(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_GENERATE_ITEM;
   return ptr;
}
int parser_sv_case_generate_item_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_generate_item_specific(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_GENERATE_ITEM;
   return ptr;
}
int parser_sv_case_generate_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_case_generate_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_case_generate_item_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_case_generate_item_v2(source, ptr, node);
}
int parser_sv_case_generate_item_specific (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_GENERATE_ITEM_SPECIFIC;
   return ptr;
}
int parser_sv_case_generate_item_default_null (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_CASE_GENERATE_ITEM_DEFAULT_NULL;
   return ptr;
}
int parser_sv_case_generate_item_default (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_GENERATE_ITEM_DEFAULT;
   return ptr;
}
int parser_sv_generate_block_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block_seq(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENERATE_BLOCK;
   return ptr;
}
int parser_sv_generate_block_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_block_single(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENERATE_BLOCK;
   return ptr;
}
int parser_sv_generate_block (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_generate_block_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_generate_block_v1(source, ptr, node);
}
int parser_sv_generate_block_seq (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_generate_item_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_GENERATE_BLOCK_SEQ;
   return ptr;
}
int parser_sv_generate_block_single (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_generate_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENERATE_BLOCK_SINGLE;
   return ptr;
}
int parser_sv_generate_item (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_or_generate_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENERATE_ITEM;
   return ptr;
}
int parser_sv_continuous_assign (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assign_list_of_variable_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONTINUOUS_ASSIGN;
   return ptr;
}
int parser_sv_assign_list_of_variable_assignments (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_variable_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_ASSIGN_LIST_OF_VARIABLE_ASSIGNMENTS;
   return ptr;
}
int parser_sv_list_of_variable_assignments_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_VARIABLE_ASSIGNMENTS_H0;
   return ptr;
}
int parser_sv_list_of_variable_assignments (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_variable_assignments_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_VARIABLE_ASSIGNMENTS;
   return ptr;
}
int parser_sv_always_construct (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_always_keyword(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ALWAYS_CONSTRUCT;
   return ptr;
}
int parser_sv_always_keyword_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_always_comb_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ALWAYS_KEYWORD;
   return ptr;
}
int parser_sv_always_keyword_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_always_latch_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ALWAYS_KEYWORD;
   return ptr;
}
int parser_sv_always_keyword_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_always_ff_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ALWAYS_KEYWORD;
   return ptr;
}
int parser_sv_always_keyword_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_always_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ALWAYS_KEYWORD;
   return ptr;
}
int parser_sv_always_keyword (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_always_keyword_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_always_keyword_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_always_keyword_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_always_keyword_v3(source, ptr, node);
}
int parser_sv_always_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ALWAYS_IDENTIFIER;
   return ptr;
}
int parser_sv_always_comb_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 95) /* _ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ALWAYS_COMB_IDENTIFIER;
   return ptr;
}
int parser_sv_always_latch_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 95) /* _ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ALWAYS_LATCH_IDENTIFIER;
   return ptr;
}
int parser_sv_always_ff_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 95) /* _ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ALWAYS_FF_IDENTIFIER;
   return ptr;
}
int parser_sv_blocking_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_blocking_assign_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BLOCKING_ASSIGNMENT;
   return ptr;
}
int parser_sv_blocking_assign_expression_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_BLOCKING_ASSIGN_EXPRESSION_H0;
   return ptr;
}
int parser_sv_blocking_assign_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_blocking_assign_expression_h0(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BLOCKING_ASSIGN_EXPRESSION;
   return ptr;
}
int parser_sv_operator_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OPERATOR_ASSIGNMENT;
   return ptr;
}
int parser_sv_assignment_operator_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_plus_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_minus_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_mul_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_not_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_mod_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_and_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_or_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_xor_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_shr2_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v10 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_shr3_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v11 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_shl2_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator_v12 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_assignment_operator_shl3_assign(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ASSIGNMENT_OPERATOR;
   return ptr;
}
int parser_sv_assignment_operator (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_assignment_operator_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v9(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v10(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_assignment_operator_v11(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_assignment_operator_v12(source, ptr, node);
}
int parser_sv_assignment_operator_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_plus_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 43) /* + */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_PLUS_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_minus_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 45) /* - */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_MINUS_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_mul_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_MUL_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_not_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 47) /* / */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_NOT_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_mod_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 37) /* % */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_MOD_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_and_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 38) /* & */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_AND_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_or_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 124) /* | */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_OR_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_xor_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 94) /* ^ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_XOR_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_shr2_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_SHR2_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_shr3_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_SHR3_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_shl2_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_SHL2_ASSIGN;
   return ptr;
}
int parser_sv_assignment_operator_shl3_assign (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_ASSIGNMENT_OPERATOR_SHL3_ASSIGN;
   return ptr;
}
int parser_sv_nonblocking_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_nonblocking_assign_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NONBLOCKING_ASSIGNMENT;
   return ptr;
}
int parser_sv_nonblocking_assign_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NONBLOCKING_ASSIGN_EXPRESSION;
   return ptr;
}
int parser_sv_variable_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_blocking_assign_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_VARIABLE_ASSIGNMENT;
   return ptr;
}
int parser_sv_seq_block_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_SEQ_BLOCK_H0;
   return ptr;
}
int parser_sv_seq_block_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_SEQ_BLOCK_H1;
   return ptr;
}
int parser_sv_seq_block (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_seq_block_h0(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_statement_or_null_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_seq_block_h1(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_SEQ_BLOCK;
   return ptr;
}
int parser_sv_statement_or_null_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_OR_NULL;
   return ptr;
}
int parser_sv_statement_or_null_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_null_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_OR_NULL;
   return ptr;
}
int parser_sv_statement_or_null (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_statement_or_null_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_statement_or_null_v1(source, ptr, node);
}
int parser_sv_null_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_NULL_STATEMENT;
   return ptr;
}
int parser_sv_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT;
   return ptr;
}
int parser_sv_statement_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_item_blocking_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_ITEM;
   return ptr;
}
int parser_sv_statement_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_item_nonblocking_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_ITEM;
   return ptr;
}
int parser_sv_statement_item_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_ITEM;
   return ptr;
}
int parser_sv_statement_item_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_conditional_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_ITEM;
   return ptr;
}
int parser_sv_statement_item_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_subroutine_call_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_ITEM;
   return ptr;
}
int parser_sv_statement_item_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_ITEM;
   return ptr;
}
int parser_sv_statement_item_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_procedural_timing_control_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_ITEM;
   return ptr;
}
int parser_sv_statement_item_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_seq_block(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_STATEMENT_ITEM;
   return ptr;
}
int parser_sv_statement_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_statement_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_statement_item_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_statement_item_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_statement_item_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_statement_item_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_statement_item_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_statement_item_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_statement_item_v7(source, ptr, node);
}
int parser_sv_statement_item_blocking_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_blocking_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT;
   return ptr;
}
int parser_sv_statement_item_nonblocking_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_nonblocking_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT;
   return ptr;
}
int parser_sv_procedural_timing_control_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_procedural_timing_control(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PROCEDURAL_TIMING_CONTROL_STATEMENT;
   return ptr;
}
int parser_sv_delay_control (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_si_delay_control(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DELAY_CONTROL;
   return ptr;
}
int parser_sv_si_delay_control (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 35) /* # */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_delay_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_SI_DELAY_CONTROL;
   return ptr;
}
int parser_sv_event_control_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_control_event_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_CONTROL;
   return ptr;
}
int parser_sv_event_control_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_control_asterisk(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_CONTROL;
   return ptr;
}
int parser_sv_event_control (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_event_control_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_event_control_v1(source, ptr, node);
}
int parser_sv_event_control_event_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 64) /* @ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_EVENT_CONTROL_EVENT_EXPRESSION;
   return ptr;
}
int parser_sv_event_control_asterisk (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 64) /* @ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_EVENT_CONTROL_ASTERISK;
   return ptr;
}
int parser_sv_event_expression_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION;
   return ptr;
}
int parser_sv_event_expression_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION;
   return ptr;
}
int parser_sv_event_expression_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION;
   return ptr;
}
int parser_sv_event_expression_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression_prev3(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION;
   return ptr;
}
int parser_sv_event_expression_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression_prev4(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION;
   return ptr;
}
int parser_sv_event_expression (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_event_expression_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_event_expression_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_event_expression_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_event_expression_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_event_expression_v4(source, ptr, node);
}
int parser_sv_event_expression_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_edge_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION_PREV0;
   return ptr;
}
int parser_sv_event_expression_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_edge_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION_PREV1;
   return ptr;
}
int parser_sv_event_expression_prev2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_EVENT_EXPRESSION_PREV2;
   return ptr;
}
int parser_sv_event_expression_prev3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION_PREV3;
   return ptr;
}
int parser_sv_event_expression_prev4_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EVENT_EXPRESSION_PREV4_H0;
   return ptr;
}
int parser_sv_event_expression_prev4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_event_expression_prev4_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_EVENT_EXPRESSION_PREV4;
   return ptr;
}
int parser_sv_edge_identifier_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_posedge_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EDGE_IDENTIFIER;
   return ptr;
}
int parser_sv_edge_identifier_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_negedge_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EDGE_IDENTIFIER;
   return ptr;
}
int parser_sv_edge_identifier (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_edge_identifier_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_edge_identifier_v1(source, ptr, node);
}
int parser_sv_posedge_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_POSEDGE_IDENTIFIER;
   return ptr;
}
int parser_sv_negedge_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_NEGEDGE_IDENTIFIER;
   return ptr;
}
int parser_sv_procedural_timing_control_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_delay_control(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PROCEDURAL_TIMING_CONTROL;
   return ptr;
}
int parser_sv_procedural_timing_control_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_event_control(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PROCEDURAL_TIMING_CONTROL;
   return ptr;
}
int parser_sv_procedural_timing_control (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_procedural_timing_control_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_procedural_timing_control_v1(source, ptr, node);
}
int parser_sv_conditional_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_if_else_conditional_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONDITIONAL_STATEMENT;
   return ptr;
}
int parser_sv_conditional_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_if_conditional_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONDITIONAL_STATEMENT;
   return ptr;
}
int parser_sv_conditional_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_conditional_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_conditional_statement_v1(source, ptr, node);
}
int parser_sv_if_else_conditional_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_unique_priority(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_cond_predicate(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IF_ELSE_CONDITIONAL_STATEMENT;
   return ptr;
}
int parser_sv_if_conditional_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_unique_priority(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_cond_predicate(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_IF_CONDITIONAL_STATEMENT;
   return ptr;
}
int parser_sv_unique_priority_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unique_priority_unique(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNIQUE_PRIORITY;
   return ptr;
}
int parser_sv_unique_priority_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unique_priority_unique0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNIQUE_PRIORITY;
   return ptr;
}
int parser_sv_unique_priority_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unique_priority_priority(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNIQUE_PRIORITY;
   return ptr;
}
int parser_sv_unique_priority (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_unique_priority_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unique_priority_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_unique_priority_v2(source, ptr, node);
}
int parser_sv_unique_priority_unique (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 113) /* q */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_UNIQUE_PRIORITY_UNIQUE;
   return ptr;
}
int parser_sv_unique_priority_unique0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 113) /* q */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 48) /* 0 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_UNIQUE_PRIORITY_UNIQUE0;
   return ptr;
}
int parser_sv_unique_priority_priority (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_UNIQUE_PRIORITY_PRIORITY;
   return ptr;
}
int parser_sv_cond_predicate_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_bracket_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_COND_PREDICATE;
   return ptr;
}
int parser_sv_cond_predicate_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unary_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_COND_PREDICATE;
   return ptr;
}
int parser_sv_cond_predicate_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_COND_PREDICATE;
   return ptr;
}
int parser_sv_cond_predicate (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_cond_predicate_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_cond_predicate_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_cond_predicate_v2(source, ptr, node);
}
int parser_sv_case_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_unique_priority(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_keyword(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_case_item_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_CASE_STATEMENT;
   return ptr;
}
int parser_sv_case_keyword_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_keyword_casez(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_KEYWORD;
   return ptr;
}
int parser_sv_case_keyword_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_keyword_casex(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_KEYWORD;
   return ptr;
}
int parser_sv_case_keyword_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_keyword_case(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_KEYWORD;
   return ptr;
}
int parser_sv_case_keyword (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_case_keyword_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_case_keyword_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_case_keyword_v2(source, ptr, node);
}
int parser_sv_case_keyword_case (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_CASE_KEYWORD_CASE;
   return ptr;
}
int parser_sv_case_keyword_casez (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 122) /* z */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_CASE_KEYWORD_CASEZ;
   return ptr;
}
int parser_sv_case_keyword_casex (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 120) /* x */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_CASE_KEYWORD_CASEX;
   return ptr;
}
int parser_sv_case_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_EXPRESSION;
   return ptr;
}
int parser_sv_case_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_default_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_ITEM;
   return ptr;
}
int parser_sv_case_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_expression_item(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_ITEM;
   return ptr;
}
int parser_sv_case_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_case_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_case_item_v1(source, ptr, node);
}
int parser_sv_case_default_item (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_DEFAULT_ITEM;
   return ptr;
}
int parser_sv_case_expression_item (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_item_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_EXPRESSION_ITEM;
   return ptr;
}
int parser_sv_case_item_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CASE_ITEM_EXPRESSION;
   return ptr;
}
int parser_sv_loop_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_repeat_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_STATEMENT;
   return ptr;
}
int parser_sv_loop_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_while_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_STATEMENT;
   return ptr;
}
int parser_sv_loop_statement_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_do_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_STATEMENT;
   return ptr;
}
int parser_sv_loop_statement_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_foreach_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_STATEMENT;
   return ptr;
}
int parser_sv_loop_statement_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_for_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_STATEMENT;
   return ptr;
}
int parser_sv_loop_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_loop_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_loop_statement_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_loop_statement_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_loop_statement_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_loop_statement_v4(source, ptr, node);
}
int parser_sv_loop_repeat_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_REPEAT_STATEMENT;
   return ptr;
}
int parser_sv_loop_while_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_WHILE_STATEMENT;
   return ptr;
}
int parser_sv_loop_do_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_LOOP_DO_STATEMENT;
   return ptr;
}
int parser_sv_loop_foreach_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_ps_or_hierarchical_array_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_variables(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_FOREACH_STATEMENT;
   return ptr;
}
int parser_sv_loop_for_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_for_initialization(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_for_step(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_or_null(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_FOR_STATEMENT;
   return ptr;
}
int parser_sv_for_initialization_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_variable_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FOR_INITIALIZATION;
   return ptr;
}
int parser_sv_for_initialization_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integer_variable_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FOR_INITIALIZATION;
   return ptr;
}
int parser_sv_for_initialization_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_variable_declarations(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FOR_INITIALIZATION;
   return ptr;
}
int parser_sv_for_initialization (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_for_initialization_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_for_initialization_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_for_initialization_v2(source, ptr, node);
}
int parser_sv_integer_variable_assignment (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGER_VARIABLE_ASSIGNMENT;
   return ptr;
}
int parser_sv_list_of_variable_declarations_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_for_variable_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_OF_VARIABLE_DECLARATIONS_H0;
   return ptr;
}
int parser_sv_list_of_variable_declarations (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_for_variable_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_of_variable_declarations_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_VARIABLE_DECLARATIONS;
   return ptr;
}
int parser_sv_for_variable_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FOR_VARIABLE_DECLARATION;
   return ptr;
}
int parser_sv_for_step (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_for_step_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FOR_STEP;
   return ptr;
}
int parser_sv_for_step_assignment (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_variable_assignments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FOR_STEP_ASSIGNMENT;
   return ptr;
}
int parser_sv_loop_variables_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_index_variable_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LOOP_VARIABLES_H1;
   return ptr;
}
int parser_sv_loop_variables (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_index_variable_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_loop_variables_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LOOP_VARIABLES;
   return ptr;
}
int parser_sv_subroutine_call_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_SUBROUTINE_CALL_STATEMENT;
   return ptr;
}
int parser_sv_concatenation (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_expression_list_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_CONCATENATION;
   return ptr;
}
int parser_sv_expression_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION_LIST;
   return ptr;
}
int parser_sv_constant_concatenation (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_constant_expression_list_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_CONSTANT_CONCATENATION;
   return ptr;
}
int parser_sv_constant_expression_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION_LIST;
   return ptr;
}
int parser_sv_multiple_concatenation (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_concatenation(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_MULTIPLE_CONCATENATION;
   return ptr;
}
int parser_sv_constant_function_call (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_subroutine_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_FUNCTION_CALL;
   return ptr;
}
int parser_sv_tf_call (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_arguments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_TF_CALL;
   return ptr;
}
int parser_sv_system_tf_call (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_system_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_list_of_arguments(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_SYSTEM_TF_CALL;
   return ptr;
}
int parser_sv_subroutine_call_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_tf_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_SUBROUTINE_CALL;
   return ptr;
}
int parser_sv_subroutine_call_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_system_tf_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_SUBROUTINE_CALL;
   return ptr;
}
int parser_sv_subroutine_call (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_subroutine_call_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_subroutine_call_v1(source, ptr, node);
}
int parser_sv_function_subroutine_call (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_subroutine_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_FUNCTION_SUBROUTINE_CALL;
   return ptr;
}
int parser_sv_list_of_arguments (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_expression_list_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_LIST_OF_ARGUMENTS;
   return ptr;
}
int parser_sv_inc_or_dec_expression_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_inc_or_dec_expression_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INC_OR_DEC_EXPRESSION;
   return ptr;
}
int parser_sv_inc_or_dec_expression_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_inc_or_dec_expression_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INC_OR_DEC_EXPRESSION;
   return ptr;
}
int parser_sv_inc_or_dec_expression (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_inc_or_dec_expression_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_inc_or_dec_expression_v1(source, ptr, node);
}
int parser_sv_inc_or_dec_expression_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_inc_or_dec_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INC_OR_DEC_EXPRESSION_PREV0;
   return ptr;
}
int parser_sv_inc_or_dec_expression_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_inc_or_dec_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INC_OR_DEC_EXPRESSION_PREV1;
   return ptr;
}
int parser_sv_conditional_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_cond_predicate(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 63) /* ? */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONDITIONAL_EXPRESSION;
   return ptr;
}
int parser_sv_constant_expression_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression_binary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_sv_constant_expression_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_trinary_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_sv_constant_expression_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unary_constant_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_sv_constant_expression_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_sv_constant_expression (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_constant_expression_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_constant_expression_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_constant_expression_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_constant_expression_v3(source, ptr, node);
}
int parser_sv_constant_expression_binary_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression_binary_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION_BINARY;
   return ptr;
}
int parser_sv_constant_expression_binary_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression_binary_unary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION_BINARY;
   return ptr;
}
int parser_sv_constant_expression_binary (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_constant_expression_binary_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_constant_expression_binary_v1(source, ptr, node);
}
int parser_sv_constant_expression_binary_primary (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION_BINARY_PRIMARY;
   return ptr;
}
int parser_sv_constant_expression_binary_unary (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unary_constant_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_EXPRESSION_BINARY_UNARY;
   return ptr;
}
int parser_sv_unary_constant_primary (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_CONSTANT_PRIMARY;
   return ptr;
}
int parser_sv_constant_trinary_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_trinary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_TRINARY_EXPRESSION;
   return ptr;
}
int parser_sv_trinary_operator (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_operator_conditional(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TRINARY_OPERATOR;
   return ptr;
}
int parser_sv_operator_conditional (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 63) /* ? */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_OPERATOR_CONDITIONAL;
   return ptr;
}
int parser_sv_constant_bracket_mintypmax_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_mintypmax_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_CONSTANT_BRACKET_MINTYPMAX_EXPRESSION;
   return ptr;
}
int parser_sv_constant_mintypmax_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_MINTYPMAX_EXPRESSION;
   return ptr;
}
int parser_sv_constant_param_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_PARAM_EXPRESSION;
   return ptr;
}
int parser_sv_constant_part_select_range (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_PART_SELECT_RANGE;
   return ptr;
}
int parser_sv_constant_range (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_RANGE;
   return ptr;
}
int parser_sv_expression_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_conditional_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION;
   return ptr;
}
int parser_sv_expression_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression_binary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION;
   return ptr;
}
int parser_sv_expression_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unary_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION;
   return ptr;
}
int parser_sv_expression_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_inc_or_dec_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION;
   return ptr;
}
int parser_sv_expression_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION;
   return ptr;
}
int parser_sv_expression (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_expression_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_expression_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_expression_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_expression_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_expression_v4(source, ptr, node);
}
int parser_sv_bracket_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_BRACKET_EXPRESSION;
   return ptr;
}
int parser_sv_expression_binary_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression_binary_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION_BINARY;
   return ptr;
}
int parser_sv_expression_binary_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression_binary_unary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION_BINARY;
   return ptr;
}
int parser_sv_expression_binary (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_expression_binary_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_expression_binary_v1(source, ptr, node);
}
int parser_sv_expression_binary_primary (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION_BINARY_PRIMARY;
   return ptr;
}
int parser_sv_expression_binary_unary (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unary_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_EXPRESSION_BINARY_UNARY;
   return ptr;
}
int parser_sv_unary_primary (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unary_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_PRIMARY;
   return ptr;
}
int parser_sv_mintypmax_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MINTYPMAX_EXPRESSION;
   return ptr;
}
int parser_sv_part_select_range_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PART_SELECT_RANGE;
   return ptr;
}
int parser_sv_part_select_range_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_indexed_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PART_SELECT_RANGE;
   return ptr;
}
int parser_sv_part_select_range (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_part_select_range_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_part_select_range_v1(source, ptr, node);
}
int parser_sv_indexed_range (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_primary(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INDEXED_RANGE;
   return ptr;
}
int parser_sv_genvar_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENVAR_EXPRESSION;
   return ptr;
}
int parser_sv_constant_primary_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_concatenation(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_PRIMARY;
   return ptr;
}
int parser_sv_constant_primary_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_function_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_PRIMARY;
   return ptr;
}
int parser_sv_constant_primary_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_primary_literal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_PRIMARY;
   return ptr;
}
int parser_sv_constant_primary_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_PRIMARY;
   return ptr;
}
int parser_sv_constant_primary_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_bracket_mintypmax_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CONSTANT_PRIMARY;
   return ptr;
}
int parser_sv_constant_primary (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_constant_primary_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_constant_primary_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_constant_primary_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_constant_primary_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_constant_primary_v4(source, ptr, node);
}
int parser_sv_primary_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_concatenation(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PRIMARY;
   return ptr;
}
int parser_sv_primary_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_multiple_concatenation(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PRIMARY;
   return ptr;
}
int parser_sv_primary_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_subroutine_call(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PRIMARY;
   return ptr;
}
int parser_sv_primary_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_bracket_mintypmax_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PRIMARY;
   return ptr;
}
int parser_sv_primary_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_identifier_select(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PRIMARY;
   return ptr;
}
int parser_sv_primary_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_primary_literal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PRIMARY;
   return ptr;
}
int parser_sv_primary (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_primary_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_primary_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_primary_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_primary_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_primary_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_primary_v5(source, ptr, node);
}
int parser_sv_bracket_mintypmax_expression (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_mintypmax_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_BRACKET_MINTYPMAX_EXPRESSION;
   return ptr;
}
int parser_sv_hierarchical_identifier_select (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_select_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_HIERARCHICAL_IDENTIFIER_SELECT;
   return ptr;
}
int parser_sv_primary_literal (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PRIMARY_LITERAL;
   return ptr;
}
int parser_sv_bit_select (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_BIT_SELECT;
   return ptr;
}
int parser_sv_select_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_select_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_SELECT;
   return ptr;
}
int parser_sv_select_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_bit_select(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_SELECT;
   return ptr;
}
int parser_sv_select (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_select_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_select_v1(source, ptr, node);
}
int parser_sv_select_range (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_part_select_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_SELECT_RANGE;
   return ptr;
}
int parser_sv_constant_bit_select_list (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_bit_select(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_constant_bit_select_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_CONSTANT_BIT_SELECT_LIST;
   return ptr;
}
int parser_sv_constant_bit_select (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_CONSTANT_BIT_SELECT;
   return ptr;
}
int parser_sv_constant_select_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_part_select_range(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_CONSTANT_SELECT_H0;
   return ptr;
}
int parser_sv_constant_select (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_bit_select(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_constant_select_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_CONSTANT_SELECT;
   return ptr;
}
int parser_sv_variable_lvalue_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_single_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_VARIABLE_LVALUE;
   return ptr;
}
int parser_sv_variable_lvalue_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_concat_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_VARIABLE_LVALUE;
   return ptr;
}
int parser_sv_variable_lvalue (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_variable_lvalue_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_variable_lvalue_v1(source, ptr, node);
}
int parser_sv_variable_single_lvalue (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_variable_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_select_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_VARIABLE_SINGLE_LVALUE;
   return ptr;
}
int parser_sv_variable_concat_lvalue (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_variable_lvalue_list_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_VARIABLE_CONCAT_LVALUE;
   return ptr;
}
int parser_sv_variable_lvalue_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_variable_lvalue(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_VARIABLE_LVALUE_LIST;
   return ptr;
}
int parser_sv_unary_operator_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_plus(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_minus(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_nand(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_nor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_nxor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_exclamation(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_tilde(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_and(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_or(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_xor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNARY_OPERATOR;
   return ptr;
}
int parser_sv_unary_operator (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_unary_operator_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unary_operator_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unary_operator_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unary_operator_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unary_operator_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unary_operator_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unary_operator_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unary_operator_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_unary_operator_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_unary_operator_v9(source, ptr, node);
}
int parser_operator_exclamation (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 33) /* ! */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_EXCLAMATION;
   return ptr;
}
int parser_operator_tilde (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 126) /* ~ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_TILDE;
   return ptr;
}
int parser_sv_binary_operator_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_plus(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_minus(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_pow(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_mul(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_asr(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_asl(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_lsr(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_lsl(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_div(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_mod(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v10 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_case_equal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v11 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_case_inequal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v12 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_wildcard_equal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v13 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_wildcard_inequal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v14 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_logical_equal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v15 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_logical_inequal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v16 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_lesser_equal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v17 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_greater_equal(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v18 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_land(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v19 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_and(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v20 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_lor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v21 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_or(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v22 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_nxor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v23 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_xor(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v24 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_lesser(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator_v25 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_operator_greater(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_OPERATOR;
   return ptr;
}
int parser_sv_binary_operator (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_binary_operator_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v9(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v10(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v11(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v12(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v13(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v14(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v15(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v16(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v17(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v18(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v19(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v20(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v21(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v22(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v23(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_operator_v24(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_binary_operator_v25(source, ptr, node);
}
int parser_operator_plus (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 43) /* + */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_PLUS;
   return ptr;
}
int parser_operator_minus (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 45) /* - */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_MINUS;
   return ptr;
}
int parser_operator_pow (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_POW;
   return ptr;
}
int parser_operator_mul (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_MUL;
   return ptr;
}
int parser_operator_div (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 47) /* / */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_DIV;
   return ptr;
}
int parser_operator_mod (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 37) /* % */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_MOD;
   return ptr;
}
int parser_operator_logical_equal (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_LOGICAL_EQUAL;
   return ptr;
}
int parser_operator_logical_inequal (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 33) /* ! */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_LOGICAL_INEQUAL;
   return ptr;
}
int parser_operator_case_equal (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_CASE_EQUAL;
   return ptr;
}
int parser_operator_case_inequal (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 33) /* ! */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_CASE_INEQUAL;
   return ptr;
}
int parser_operator_wildcard_equal_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 63) /* ? */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_WILDCARD_EQUAL;
   return ptr;
}
int parser_operator_wildcard_equal_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 63) /* ? */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_WILDCARD_EQUAL;
   return ptr;
}
int parser_operator_wildcard_equal (string &source, int ptr, NODE *node) {
   int newPtr = parser_operator_wildcard_equal_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_operator_wildcard_equal_v1(source, ptr, node);
}
int parser_operator_wildcard_inequal_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 33) /* ! */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 63) /* ? */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_WILDCARD_INEQUAL;
   return ptr;
}
int parser_operator_wildcard_inequal_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 33) /* ! */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 63) /* ? */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_WILDCARD_INEQUAL;
   return ptr;
}
int parser_operator_wildcard_inequal (string &source, int ptr, NODE *node) {
   int newPtr = parser_operator_wildcard_inequal_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_operator_wildcard_inequal_v1(source, ptr, node);
}
int parser_operator_lesser_equal (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_LESSER_EQUAL;
   return ptr;
}
int parser_operator_greater_equal (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_GREATER_EQUAL;
   return ptr;
}
int parser_operator_land (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 38) /* & */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 38) /* & */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_LAND;
   return ptr;
}
int parser_operator_and (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 38) /* & */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_AND;
   return ptr;
}
int parser_operator_nand (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 126) /* ~ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 38) /* & */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_NAND;
   return ptr;
}
int parser_operator_lor (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 124) /* | */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 124) /* | */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_LOR;
   return ptr;
}
int parser_operator_or (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 124) /* | */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_OR;
   return ptr;
}
int parser_operator_nor (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 126) /* ~ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 124) /* | */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_NOR;
   return ptr;
}
int parser_operator_xor (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 94) /* ^ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_XOR;
   return ptr;
}
int parser_operator_nxor_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 126) /* ~ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 94) /* ^ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_NXOR;
   return ptr;
}
int parser_operator_nxor_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 94) /* ^ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 126) /* ~ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_NXOR;
   return ptr;
}
int parser_operator_nxor (string &source, int ptr, NODE *node) {
   int newPtr = parser_operator_nxor_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_operator_nxor_v1(source, ptr, node);
}
int parser_operator_lsr (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_LSR;
   return ptr;
}
int parser_operator_lsl (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_LSL;
   return ptr;
}
int parser_operator_asr (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_ASR;
   return ptr;
}
int parser_operator_asl (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_ASL;
   return ptr;
}
int parser_operator_lesser (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_LESSER;
   return ptr;
}
int parser_operator_greater (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_OPERATOR_GREATER;
   return ptr;
}
int parser_inc_or_dec_operator_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_inc_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_INC_OR_DEC_OPERATOR;
   return ptr;
}
int parser_inc_or_dec_operator_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_dec_operator(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_INC_OR_DEC_OPERATOR;
   return ptr;
}
int parser_inc_or_dec_operator (string &source, int ptr, NODE *node) {
   int newPtr = parser_inc_or_dec_operator_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_inc_or_dec_operator_v1(source, ptr, node);
}
int parser_inc_operator (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 43) /* + */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 43) /* + */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_INC_OPERATOR;
   return ptr;
}
int parser_dec_operator (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 45) /* - */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 45) /* - */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_DEC_OPERATOR;
   return ptr;
}
int parser_sv_number (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_integral_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NUMBER;
   return ptr;
}
int parser_sv_integral_number_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGRAL_NUMBER;
   return ptr;
}
int parser_sv_integral_number_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGRAL_NUMBER;
   return ptr;
}
int parser_sv_integral_number_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGRAL_NUMBER;
   return ptr;
}
int parser_sv_integral_number_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INTEGRAL_NUMBER;
   return ptr;
}
int parser_sv_integral_number (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_integral_number_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_integral_number_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_integral_number_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_integral_number_v3(source, ptr, node);
}
int parser_sv_decimal_number_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev3(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev4(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev5(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev6(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev7(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_number_prev8(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER;
   return ptr;
}
int parser_sv_decimal_number (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_decimal_number_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_number_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_number_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_number_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_number_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_number_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_number_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_number_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_decimal_number_v8(source, ptr, node);
}
int parser_sv_decimal_number_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_cpp_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV0;
   return ptr;
}
int parser_sv_decimal_number_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV1;
   return ptr;
}
int parser_sv_decimal_number_prev2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_x_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_us_digit_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV2;
   return ptr;
}
int parser_sv_decimal_number_prev3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_z_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_us_digit_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV3;
   return ptr;
}
int parser_sv_decimal_number_prev4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV4;
   return ptr;
}
int parser_sv_decimal_number_prev5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_x_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_us_digit_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV5;
   return ptr;
}
int parser_sv_decimal_number_prev6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_z_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_us_digit_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV6;
   return ptr;
}
int parser_sv_decimal_number_prev7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV7;
   return ptr;
}
int parser_sv_decimal_number_prev8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_zero_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_NUMBER_PREV8;
   return ptr;
}
int parser_sv_binary_number_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_number_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_NUMBER;
   return ptr;
}
int parser_sv_binary_number_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_number_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_NUMBER;
   return ptr;
}
int parser_sv_binary_number (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_binary_number_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_binary_number_v1(source, ptr, node);
}
int parser_sv_binary_number_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_NUMBER_PREV0;
   return ptr;
}
int parser_sv_binary_number_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_NUMBER_PREV1;
   return ptr;
}
int parser_sv_octal_number_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_number_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OCTAL_NUMBER;
   return ptr;
}
int parser_sv_octal_number_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_number_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OCTAL_NUMBER;
   return ptr;
}
int parser_sv_octal_number (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_octal_number_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_octal_number_v1(source, ptr, node);
}
int parser_sv_octal_number_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OCTAL_NUMBER_PREV0;
   return ptr;
}
int parser_sv_octal_number_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OCTAL_NUMBER_PREV1;
   return ptr;
}
int parser_sv_hex_number_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_number_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HEX_NUMBER;
   return ptr;
}
int parser_sv_hex_number_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_number_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HEX_NUMBER;
   return ptr;
}
int parser_sv_hex_number (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_hex_number_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_hex_number_v1(source, ptr, node);
}
int parser_sv_hex_number_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HEX_NUMBER_PREV0;
   return ptr;
}
int parser_sv_hex_number_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HEX_NUMBER_PREV1;
   return ptr;
}
int parser_cpp_unsigned_number_old (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 48) /* 0 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 120) /* x */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_value(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 85) /* U */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_CPP_UNSIGNED_NUMBER_OLD;
   return ptr;
}
int parser_sv_unsigned_number_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNSIGNED_NUMBER;
   return ptr;
}
int parser_sv_unsigned_number_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unsigned_number_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_UNSIGNED_NUMBER;
   return ptr;
}
int parser_sv_unsigned_number (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_unsigned_number_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_unsigned_number_v1(source, ptr, node);
}
int parser_sv_unsigned_number_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_decimal_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_unsigned_number(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_UNSIGNED_NUMBER_PREV0;
   return ptr;
}
int parser_sv_unsigned_number_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_us_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_unsigned_number(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_UNSIGNED_NUMBER_PREV1;
   return ptr;
}
int parser_sv_zero_number (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_0_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ZERO_NUMBER;
   return ptr;
}
int parser_sv_binary_value_digit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_value_digit_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_VALUE_DIGIT;
   return ptr;
}
int parser_sv_binary_value_digit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_value_digit_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_VALUE_DIGIT;
   return ptr;
}
int parser_sv_binary_value_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_binary_value_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_binary_value_digit_v1(source, ptr, node);
}
int parser_sv_binary_value_digit_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_binary_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_binary_value_digit(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_BINARY_VALUE_DIGIT_PREV0;
   return ptr;
}
int parser_sv_binary_value_digit_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_us_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_binary_value_digit(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_BINARY_VALUE_DIGIT_PREV1;
   return ptr;
}
int parser_sv_binary_value (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 48) /* 0 */  | (source.at(ptr) == 49) /* 1 */  | (source.at(ptr) == 120) /* x */  | (source.at(ptr) == 88) /* X */  | (source.at(ptr) == 122) /* z */  | (source.at(ptr) == 90) /* Z */  | (source.at(ptr) == 63) /* ? */  | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while ((source.at(ptr) == 48) /* 0 */  | (source.at(ptr) == 49) /* 1 */  | (source.at(ptr) == 120) /* x */  | (source.at(ptr) == 88) /* X */  | (source.at(ptr) == 122) /* z */  | (source.at(ptr) == 90) /* Z */  | (source.at(ptr) == 63) /* ? */  | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_SV_BINARY_VALUE;
   return ptr;
}
int parser_sv_octal_value_digit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_value_digit_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OCTAL_VALUE_DIGIT;
   return ptr;
}
int parser_sv_octal_value_digit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_value_digit_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OCTAL_VALUE_DIGIT;
   return ptr;
}
int parser_sv_octal_value_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_octal_value_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_octal_value_digit_v1(source, ptr, node);
}
int parser_sv_octal_value_digit_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_octal_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_octal_value_digit(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_OCTAL_VALUE_DIGIT_PREV0;
   return ptr;
}
int parser_sv_octal_value_digit_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_us_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_octal_value_digit(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_OCTAL_VALUE_DIGIT_PREV1;
   return ptr;
}
int parser_sv_octal_value (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if (((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 55) /* 7 */ ) | (source.at(ptr) == 120) /* x */  | (source.at(ptr) == 88) /* X */  | (source.at(ptr) == 122) /* z */  | (source.at(ptr) == 90) /* Z */  | (source.at(ptr) == 63) /* ? */  | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 55) /* 7 */ ) | (source.at(ptr) == 120) /* x */  | (source.at(ptr) == 88) /* X */  | (source.at(ptr) == 122) /* z */  | (source.at(ptr) == 90) /* Z */  | (source.at(ptr) == 63) /* ? */  | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_SV_OCTAL_VALUE;
   return ptr;
}
int parser_sv_hex_value_digit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_value_digit_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HEX_VALUE_DIGIT;
   return ptr;
}
int parser_sv_hex_value_digit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_value_digit_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HEX_VALUE_DIGIT;
   return ptr;
}
int parser_sv_hex_value_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_hex_value_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_hex_value_digit_v1(source, ptr, node);
}
int parser_sv_hex_value_digit_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hex_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_hex_value_digit(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_HEX_VALUE_DIGIT_PREV0;
   return ptr;
}
int parser_sv_hex_value_digit_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_us_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_hex_value_digit(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_HEX_VALUE_DIGIT_PREV1;
   return ptr;
}
int parser_sv_hex_value (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if (((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | ((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 102) /* f */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 70) /* F */ ) | (source.at(ptr) == 120) /* x */  | (source.at(ptr) == 88) /* X */  | (source.at(ptr) == 122) /* z */  | (source.at(ptr) == 90) /* Z */  | (source.at(ptr) == 63) /* ? */  | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | ((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 102) /* f */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 70) /* F */ ) | (source.at(ptr) == 120) /* x */  | (source.at(ptr) == 88) /* X */  | (source.at(ptr) == 122) /* z */  | (source.at(ptr) == 90) /* Z */  | (source.at(ptr) == 63) /* ? */  | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_SV_HEX_VALUE;
   return ptr;
}
int parser_sv_decimal_base_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_unsigned_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_BASE;
   return ptr;
}
int parser_sv_decimal_base_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_decimal_signed_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_DECIMAL_BASE;
   return ptr;
}
int parser_sv_decimal_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_decimal_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_decimal_base_v1(source, ptr, node);
}
int parser_sv_decimal_unsigned_base_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_DECIMAL_UNSIGNED_BASE;
   return ptr;
}
int parser_sv_decimal_unsigned_base_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 68) /* D */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_DECIMAL_UNSIGNED_BASE;
   return ptr;
}
int parser_sv_decimal_unsigned_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_decimal_unsigned_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_decimal_unsigned_base_v1(source, ptr, node);
}
int parser_sv_decimal_signed_base_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_DECIMAL_SIGNED_BASE;
   return ptr;
}
int parser_sv_decimal_signed_base_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 83) /* S */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_DECIMAL_SIGNED_BASE;
   return ptr;
}
int parser_sv_decimal_signed_base_v2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 68) /* D */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_DECIMAL_SIGNED_BASE;
   return ptr;
}
int parser_sv_decimal_signed_base_v3 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 83) /* S */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 68) /* D */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_DECIMAL_SIGNED_BASE;
   return ptr;
}
int parser_sv_decimal_signed_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_decimal_signed_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_signed_base_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_decimal_signed_base_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_decimal_signed_base_v3(source, ptr, node);
}
int parser_sv_binary_base_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_unsigned_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_BASE;
   return ptr;
}
int parser_sv_binary_base_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_binary_signed_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_BINARY_BASE;
   return ptr;
}
int parser_sv_binary_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_binary_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_binary_base_v1(source, ptr, node);
}
int parser_sv_binary_unsigned_base_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_BINARY_UNSIGNED_BASE;
   return ptr;
}
int parser_sv_binary_unsigned_base_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 66) /* B */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_BINARY_UNSIGNED_BASE;
   return ptr;
}
int parser_sv_binary_unsigned_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_binary_unsigned_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_binary_unsigned_base_v1(source, ptr, node);
}
int parser_sv_binary_signed_base_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_BINARY_SIGNED_BASE;
   return ptr;
}
int parser_sv_binary_signed_base_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 83) /* S */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_BINARY_SIGNED_BASE;
   return ptr;
}
int parser_sv_binary_signed_base_v2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 66) /* B */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_BINARY_SIGNED_BASE;
   return ptr;
}
int parser_sv_binary_signed_base_v3 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 83) /* S */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 66) /* B */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_BINARY_SIGNED_BASE;
   return ptr;
}
int parser_sv_binary_signed_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_binary_signed_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_signed_base_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_binary_signed_base_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_binary_signed_base_v3(source, ptr, node);
}
int parser_sv_octal_base_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_unsigned_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OCTAL_BASE;
   return ptr;
}
int parser_sv_octal_base_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_octal_signed_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_OCTAL_BASE;
   return ptr;
}
int parser_sv_octal_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_octal_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_octal_base_v1(source, ptr, node);
}
int parser_sv_octal_unsigned_base_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_OCTAL_UNSIGNED_BASE;
   return ptr;
}
int parser_sv_octal_unsigned_base_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 79) /* O */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_OCTAL_UNSIGNED_BASE;
   return ptr;
}
int parser_sv_octal_unsigned_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_octal_unsigned_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_octal_unsigned_base_v1(source, ptr, node);
}
int parser_sv_octal_signed_base_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_OCTAL_SIGNED_BASE;
   return ptr;
}
int parser_sv_octal_signed_base_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 83) /* S */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_OCTAL_SIGNED_BASE;
   return ptr;
}
int parser_sv_octal_signed_base_v2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 79) /* O */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_OCTAL_SIGNED_BASE;
   return ptr;
}
int parser_sv_octal_signed_base_v3 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 83) /* S */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 79) /* O */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_OCTAL_SIGNED_BASE;
   return ptr;
}
int parser_sv_octal_signed_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_octal_signed_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_octal_signed_base_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_octal_signed_base_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_octal_signed_base_v3(source, ptr, node);
}
int parser_sv_hex_base_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_unsigned_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HEX_BASE;
   return ptr;
}
int parser_sv_hex_base_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hex_signed_base(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HEX_BASE;
   return ptr;
}
int parser_sv_hex_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_hex_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_hex_base_v1(source, ptr, node);
}
int parser_sv_hex_unsigned_base_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_HEX_UNSIGNED_BASE;
   return ptr;
}
int parser_sv_hex_unsigned_base_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 72) /* H */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_HEX_UNSIGNED_BASE;
   return ptr;
}
int parser_sv_hex_unsigned_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_hex_unsigned_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_hex_unsigned_base_v1(source, ptr, node);
}
int parser_sv_hex_signed_base_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_HEX_SIGNED_BASE;
   return ptr;
}
int parser_sv_hex_signed_base_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 83) /* S */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_HEX_SIGNED_BASE;
   return ptr;
}
int parser_sv_hex_signed_base_v2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 72) /* H */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_HEX_SIGNED_BASE;
   return ptr;
}
int parser_sv_hex_signed_base_v3 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 39) /* ' */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 83) /* S */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 72) /* H */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SV_HEX_SIGNED_BASE;
   return ptr;
}
int parser_sv_hex_signed_base (string &source, int ptr, NODE *node) {
   int newPtr = parser_sv_hex_signed_base_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_hex_signed_base_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_sv_hex_signed_base_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_sv_hex_signed_base_v3(source, ptr, node);
}
int parser_decimal_digit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_0_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_1_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_2_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_3_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_4_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_5_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_6_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_7_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_8_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_9_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_DECIMAL_DIGIT;
   return ptr;
}
int parser_decimal_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_decimal_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_decimal_digit_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_decimal_digit_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_decimal_digit_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_decimal_digit_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_decimal_digit_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_decimal_digit_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_decimal_digit_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_decimal_digit_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_decimal_digit_v9(source, ptr, node);
}
int parser_binary_digit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_x_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_BINARY_DIGIT;
   return ptr;
}
int parser_binary_digit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_z_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_BINARY_DIGIT;
   return ptr;
}
int parser_binary_digit_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_0_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_BINARY_DIGIT;
   return ptr;
}
int parser_binary_digit_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_1_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_BINARY_DIGIT;
   return ptr;
}
int parser_binary_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_binary_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_binary_digit_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_binary_digit_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_binary_digit_v3(source, ptr, node);
}
int parser_octal_digit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_x_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_z_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_0_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_1_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_2_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_3_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_4_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_5_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_6_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_7_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_OCTAL_DIGIT;
   return ptr;
}
int parser_octal_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_octal_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_octal_digit_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_octal_digit_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_octal_digit_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_octal_digit_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_octal_digit_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_octal_digit_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_octal_digit_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_octal_digit_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_octal_digit_v9(source, ptr, node);
}
int parser_hex_digit_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_x_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_z_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_0_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_1_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_2_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_3_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_4_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_5_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_6_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_7_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v10 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_8_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v11 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_9_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v12 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_a_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v13 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_b_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v14 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_c_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v15 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_d_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v16 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_e_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit_v17 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_f_digit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HEX_DIGIT;
   return ptr;
}
int parser_hex_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_hex_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v9(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v10(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v11(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v12(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v13(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v14(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v15(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_hex_digit_v16(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_hex_digit_v17(source, ptr, node);
}
int parser_x_digit_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 120) /* x */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_X_DIGIT;
   return ptr;
}
int parser_x_digit_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 88) /* X */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_X_DIGIT;
   return ptr;
}
int parser_x_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_x_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_x_digit_v1(source, ptr, node);
}
int parser_z_digit_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 122) /* z */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_Z_DIGIT;
   return ptr;
}
int parser_z_digit_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 90) /* Z */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_Z_DIGIT;
   return ptr;
}
int parser_z_digit_v2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 63) /* ? */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_Z_DIGIT;
   return ptr;
}
int parser_z_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_z_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_z_digit_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_z_digit_v2(source, ptr, node);
}
int parser_0_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 48) /* 0 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_0_DIGIT;
   return ptr;
}
int parser_1_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 49) /* 1 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_1_DIGIT;
   return ptr;
}
int parser_2_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 50) /* 2 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_2_DIGIT;
   return ptr;
}
int parser_3_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 51) /* 3 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_3_DIGIT;
   return ptr;
}
int parser_4_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 52) /* 4 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_4_DIGIT;
   return ptr;
}
int parser_5_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 53) /* 5 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_5_DIGIT;
   return ptr;
}
int parser_6_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 54) /* 6 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_6_DIGIT;
   return ptr;
}
int parser_7_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 55) /* 7 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_7_DIGIT;
   return ptr;
}
int parser_8_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 56) /* 8 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_8_DIGIT;
   return ptr;
}
int parser_9_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 57) /* 9 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_9_DIGIT;
   return ptr;
}
int parser_a_digit_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_A_DIGIT;
   return ptr;
}
int parser_a_digit_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 65) /* A */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_A_DIGIT;
   return ptr;
}
int parser_a_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_a_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_a_digit_v1(source, ptr, node);
}
int parser_b_digit_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_B_DIGIT;
   return ptr;
}
int parser_b_digit_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 66) /* B */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_B_DIGIT;
   return ptr;
}
int parser_b_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_b_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_b_digit_v1(source, ptr, node);
}
int parser_c_digit_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_C_DIGIT;
   return ptr;
}
int parser_c_digit_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 67) /* C */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_C_DIGIT;
   return ptr;
}
int parser_c_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_c_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_c_digit_v1(source, ptr, node);
}
int parser_d_digit_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_D_DIGIT;
   return ptr;
}
int parser_d_digit_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 68) /* D */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_D_DIGIT;
   return ptr;
}
int parser_d_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_d_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_d_digit_v1(source, ptr, node);
}
int parser_e_digit_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_E_DIGIT;
   return ptr;
}
int parser_e_digit_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 69) /* E */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_E_DIGIT;
   return ptr;
}
int parser_e_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_e_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_e_digit_v1(source, ptr, node);
}
int parser_f_digit_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_F_DIGIT;
   return ptr;
}
int parser_f_digit_v1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 70) /* F */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_F_DIGIT;
   return ptr;
}
int parser_f_digit (string &source, int ptr, NODE *node) {
   int newPtr = parser_f_digit_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_f_digit_v1(source, ptr, node);
}
int parser_us_digit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 95) /* _ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_US_DIGIT;
   return ptr;
}
int parser_sv_attribute_instance (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_attr_spec(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_list_attr_spec_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 42) /* * */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SV_ATTRIBUTE_INSTANCE;
   return ptr;
}
int parser_sv_attr_spec_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_ATTR_SPEC_H0;
   return ptr;
}
int parser_sv_attr_spec (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_attr_spec_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_ATTR_SPEC;
   return ptr;
}
int parser_sv_list_attr_spec (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_attr_spec(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_LIST_ATTR_SPEC;
   return ptr;
}
int parser_sv_class_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_CLASS_IDENTIFIER;
   return ptr;
}
int parser_sv_tf_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TF_IDENTIFIER;
   return ptr;
}
int parser_sv_genvar_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_GENVAR_IDENTIFIER;
   return ptr;
}
int parser_sv_hierarchical_array_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HIERARCHICAL_ARRAY_IDENTIFIER;
   return ptr;
}
int parser_sv_hierarchical_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_hierarchical_identifier_list_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_SV_HIERARCHICAL_IDENTIFIER;
   return ptr;
}
int parser_sv_hierarchical_identifier_list (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_constant_bit_select_list(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HIERARCHICAL_IDENTIFIER_LIST;
   return ptr;
}
int parser_sv_hierarchical_parameter_identifier_h1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_parameter_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HIERARCHICAL_PARAMETER_IDENTIFIER_H1;
   return ptr;
}
int parser_sv_hierarchical_parameter_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_hierarchical_parameter_identifier_h1(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_SV_HIERARCHICAL_PARAMETER_IDENTIFIER;
   return ptr;
}
int parser_sv_hierarchical_variable_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_HIERARCHICAL_VARIABLE_IDENTIFIER;
   return ptr;
}
int parser_sv_index_variable_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INDEX_VARIABLE_IDENTIFIER;
   return ptr;
}
int parser_sv_instance_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_INSTANCE_IDENTIFIER;
   return ptr;
}
int parser_sv_module_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_MODULE_IDENTIFIER;
   return ptr;
}
int parser_sv_net_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_NET_IDENTIFIER;
   return ptr;
}
int parser_sv_port_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PORT_IDENTIFIER;
   return ptr;
}
int parser_sv_ps_or_hierarchical_array_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_hierarchical_array_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_PS_OR_HIERARCHICAL_ARRAY_IDENTIFIER;
   return ptr;
}
int parser_sv_type_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_TYPE_IDENTIFIER;
   return ptr;
}
int parser_sv_variable_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SV_VARIABLE_IDENTIFIER;
   return ptr;
}
int parser_hierarchical_name_h2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_HIERARCHICAL_NAME_H2;
   return ptr;
}
int parser_hierarchical_name (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_hierarchical_name_h2_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_HIERARCHICAL_NAME;
   return ptr;
}
int parser_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_SI;
   return ptr;
}
int parser_list_of_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_LIST_OF_SI;
   return ptr;
}
int parser_system_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 36) /* $ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_SYSTEM_SI;
   return ptr;
}
int parser_simple_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_SIMPLE_IDENTIFIER;
   return ptr;
}
int parser_usi (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_USI;
   return ptr;
}
int parser_list_of_usi (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_usi(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_LIST_OF_USI;
   return ptr;
}
int parser_semikolon (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_SEMIKOLON;
   return ptr;
}
int parser_pdvl_grammar (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 60) /* < */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 34) /* " */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_declaration_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 34) /* " */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_GRAMMAR;
   return ptr;
}
int parser_pdvl_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_build_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DECLARATION;
   return ptr;
}
int parser_pdvl_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cluster_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DECLARATION;
   return ptr;
}
int parser_pdvl_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_declaration_v1(source, ptr, node);
}
int parser_pdvl_cluster_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cluster_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_CLUSTER_DECLARATION;
   return ptr;
}
int parser_pdvl_cluster_identifier_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cluster_cl_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_IDENTIFIER;
   return ptr;
}
int parser_pdvl_cluster_identifier_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cluster_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_IDENTIFIER;
   return ptr;
}
int parser_pdvl_cluster_identifier (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_cluster_identifier_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_cluster_identifier_v1(source, ptr, node);
}
int parser_pdvl_cluster_cl_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 99) /* c */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 108) /* l */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_PDVL_CLUSTER_CL_SI;
   return ptr;
}
int parser_pdvl_cluster_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_SI;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_sub_cluster_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_parameter_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_type_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_event_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_item_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_reg_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_latch_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_data_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_if_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v10 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_case_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v11 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_foreach_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v12 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_for_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v13 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v14 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body_v15 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_theorem_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CLUSTER_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_cluster_declaration_body (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_cluster_declaration_body_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v9(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v10(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v11(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v12(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v13(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cluster_declaration_body_v14(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_cluster_declaration_body_v15(source, ptr, node);
}
int parser_pdvl_sub_cluster_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cluster_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_SUB_CLUSTER_DECLARATION;
   return ptr;
}
int parser_pdvl_item_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_attribute_instance(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_blocking_assign_expression(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_ITEM_DECLARATION;
   return ptr;
}
int parser_pdvl_reg_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_attribute_instance(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_macro_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_REG_DECLARATION;
   return ptr;
}
int parser_pdvl_latch_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_attribute_instance(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_macro_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_LATCH_DECLARATION;
   return ptr;
}
int parser_pdvl_identifier_type_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE;
   return ptr;
}
int parser_pdvl_identifier_type_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE;
   return ptr;
}
int parser_pdvl_identifier_type_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE;
   return ptr;
}
int parser_pdvl_identifier_type_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type_prev3(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE;
   return ptr;
}
int parser_pdvl_identifier_type_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type_prev4(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE;
   return ptr;
}
int parser_pdvl_identifier_type_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type_prev5(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE;
   return ptr;
}
int parser_pdvl_identifier_type_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type_prev6(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE;
   return ptr;
}
int parser_pdvl_identifier_type_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_type_prev7(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE;
   return ptr;
}
int parser_pdvl_identifier_type (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_identifier_type_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_identifier_type_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_identifier_type_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_identifier_type_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_identifier_type_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_identifier_type_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_identifier_type_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_identifier_type_v7(source, ptr, node);
}
int parser_pdvl_identifier_type_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_packed_dimension_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_unpacked_dimension_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE_PREV0;
   return ptr;
}
int parser_pdvl_identifier_type_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_packed_dimension_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE_PREV1;
   return ptr;
}
int parser_pdvl_identifier_type_prev2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_enum_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE_PREV2;
   return ptr;
}
int parser_pdvl_identifier_type_prev3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_unpacked_dimension_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE_PREV3;
   return ptr;
}
int parser_pdvl_identifier_type_prev4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_struct_or_union_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_unpacked_dimension_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE_PREV4;
   return ptr;
}
int parser_pdvl_identifier_type_prev5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_struct_or_union_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE_PREV5;
   return ptr;
}
int parser_pdvl_identifier_type_prev6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_type_identifier_data_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE_PREV6;
   return ptr;
}
int parser_pdvl_identifier_type_prev7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_identifier_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_IDENTIFIER_TYPE_PREV7;
   return ptr;
}
int parser_pdvl_identifier_list (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_list_of_si_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_PDVL_IDENTIFIER_LIST;
   return ptr;
}
int parser_pdvl_packed_dimension_list (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_packed_or_c_style(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_packed_dimension_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_PACKED_DIMENSION_LIST;
   return ptr;
}
int parser_pdvl_packed_or_c_style_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_packed_dimension(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_PACKED_OR_C_STYLE;
   return ptr;
}
int parser_pdvl_packed_or_c_style_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_c_style_dimension(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_PACKED_OR_C_STYLE;
   return ptr;
}
int parser_pdvl_packed_or_c_style (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_packed_or_c_style_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_packed_or_c_style_v1(source, ptr, node);
}
int parser_pdvl_c_style_dimension (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 91) /* [ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 93) /* ] */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_C_STYLE_DIMENSION;
   return ptr;
}
int parser_pdvl_unpacked_dimension_list (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_unpacked_dimension(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_unpacked_dimension_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_UNPACKED_DIMENSION_LIST;
   return ptr;
}
int parser_pdvl_enum_data_type (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_packed_dimension_list(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_enum_name_declaration_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_ENUM_DATA_TYPE;
   return ptr;
}
int parser_pdvl_struct_or_union_data_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_struct_union(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_packed_keyword(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_sv_struct_union_member_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_STRUCT_OR_UNION_DATA_TYPE;
   return ptr;
}
int parser_pdvl_type_identifier_data_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_class_scope(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_type_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TYPE_IDENTIFIER_DATA_TYPE;
   return ptr;
}
int parser_pdvl_transaction_macro_list_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_macro_list_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_MACRO_LIST;
   return ptr;
}
int parser_pdvl_transaction_macro_list_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_macro_list_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_MACRO_LIST;
   return ptr;
}
int parser_pdvl_transaction_macro_list (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_transaction_macro_list_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_transaction_macro_list_v1(source, ptr, node);
}
int parser_pdvl_transaction_macro_list_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_transaction_macro_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_TRANSACTION_MACRO_LIST_PREV0;
   return ptr;
}
int parser_pdvl_transaction_macro_list_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_data_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_macro_list(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_TRANSACTION_MACRO_LIST_PREV1;
   return ptr;
}
int parser_pdvl_data_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_data_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_tf_port_list_brackets(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_data_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_DATA_DECLARATION;
   return ptr;
}
int parser_pdvl_data_identifier_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_data_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DATA_IDENTIFIER;
   return ptr;
}
int parser_pdvl_data_identifier_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_and_data_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DATA_IDENTIFIER;
   return ptr;
}
int parser_pdvl_data_identifier_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_data_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DATA_IDENTIFIER;
   return ptr;
}
int parser_pdvl_data_identifier (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_data_identifier_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_data_identifier_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_data_identifier_v2(source, ptr, node);
}
int parser_pdvl_data_identifier_by_name (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 100) /* d */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_PDVL_DATA_IDENTIFIER_BY_NAME;
   return ptr;
}
int parser_pdvl_transaction_and_data_identifier_by_name (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 116) /* t */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 114) /* r */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 100) /* d */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_PDVL_TRANSACTION_AND_DATA_IDENTIFIER_BY_NAME;
   return ptr;
}
int parser_pdvl_data_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DATA_SI;
   return ptr;
}
int parser_pdvl_data_declaration_body_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_statement_item_blocking_assignment(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DATA_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_data_declaration_body_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_case_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DATA_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_data_declaration_body_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_conditional_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DATA_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_data_declaration_body_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_loop_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_DATA_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_data_declaration_body (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_data_declaration_body_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_data_declaration_body_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_data_declaration_body_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_data_declaration_body_v3(source, ptr, node);
}
int parser_pdvl_cond_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_declaration_level_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_DECLARATION;
   return ptr;
}
int parser_pdvl_cond_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_declaration_body_port(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_DECLARATION;
   return ptr;
}
int parser_pdvl_cond_declaration_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_declaration_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_DECLARATION;
   return ptr;
}
int parser_pdvl_cond_declaration_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_declaration_level(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_DECLARATION;
   return ptr;
}
int parser_pdvl_cond_declaration_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_declaration_reg(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_DECLARATION;
   return ptr;
}
int parser_pdvl_cond_declaration_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_declaration_simple(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_DECLARATION;
   return ptr;
}
int parser_pdvl_cond_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_cond_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cond_declaration_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cond_declaration_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cond_declaration_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_cond_declaration_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_cond_declaration_v5(source, ptr, node);
}
int parser_pdvl_cond_declaration_level_body (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_level_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_signal_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cond_conditional_statement_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_COND_DECLARATION_LEVEL_BODY;
   return ptr;
}
int parser_pdvl_cond_declaration_body_port (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_tf_port_list_brackets(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_cond_conditional_statement_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_COND_DECLARATION_BODY_PORT;
   return ptr;
}
int parser_pdvl_cond_declaration_body (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_attribute_instance(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_cond_conditional_statement_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_COND_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_tf_port_list_brackets_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TF_PORT_LIST_BRACKETS_H0;
   return ptr;
}
int parser_pdvl_tf_port_list_brackets (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_function_port_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_tf_port_list_brackets_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_TF_PORT_LIST_BRACKETS;
   return ptr;
}
int parser_pdvl_cond_declaration_level (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_level_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_signal_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_COND_DECLARATION_LEVEL;
   return ptr;
}
int parser_pdvl_level_identifier_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_high_level_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LEVEL_IDENTIFIER;
   return ptr;
}
int parser_pdvl_level_identifier_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_low_level_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LEVEL_IDENTIFIER;
   return ptr;
}
int parser_pdvl_level_identifier (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_level_identifier_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_level_identifier_v1(source, ptr, node);
}
int parser_pdvl_high_level_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_HIGH_LEVEL_IDENTIFIER;
   return ptr;
}
int parser_pdvl_low_level_identifier (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_LOW_LEVEL_IDENTIFIER;
   return ptr;
}
int parser_pdvl_cond_signal_name (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_SIGNAL_NAME;
   return ptr;
}
int parser_pdvl_cond_declaration_reg (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_cond_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_COND_DECLARATION_REG;
   return ptr;
}
int parser_pdvl_cond_declaration_simple (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_attribute_instance(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_cond_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_COND_DECLARATION_SIMPLE;
   return ptr;
}
int parser_pdvl_list_of_cond_identifiers_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_cond_identifiers_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_COND_IDENTIFIERS;
   return ptr;
}
int parser_pdvl_list_of_cond_identifiers_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_cond_identifiers_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_COND_IDENTIFIERS;
   return ptr;
}
int parser_pdvl_list_of_cond_identifiers (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_list_of_cond_identifiers_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_list_of_cond_identifiers_v1(source, ptr, node);
}
int parser_pdvl_list_of_cond_identifiers_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_COND_IDENTIFIERS_SI;
   return ptr;
}
int parser_pdvl_list_of_cond_identifiers_by_name (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_list_of_cond_identifiers_by_name_extension_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_PDVL_LIST_OF_COND_IDENTIFIERS_BY_NAME;
   return ptr;
}
int parser_pdvl_list_of_cond_identifiers_by_name_extension (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_COND_IDENTIFIERS_BY_NAME_EXTENSION;
   return ptr;
}
int parser_pdvl_cond_identifier_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_IDENTIFIER;
   return ptr;
}
int parser_pdvl_cond_identifier_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_cond_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_IDENTIFIER;
   return ptr;
}
int parser_pdvl_cond_identifier (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_cond_identifier_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_cond_identifier_v1(source, ptr, node);
}
int parser_pdvl_cond_identifier_by_name (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 99) /* c */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_PDVL_COND_IDENTIFIER_BY_NAME;
   return ptr;
}
int parser_pdvl_cond_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_COND_SI;
   return ptr;
}
int parser_pdvl_cond_conditional_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_implicit_cond_handle(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_COND_CONDITIONAL_STATEMENT;
   return ptr;
}
int parser_pdvl_implicit_cond_handle (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_IMPLICIT_COND_HANDLE;
   return ptr;
}
int parser_pdvl_cond_macro_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_data_declaration_body_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_COND_MACRO_LIST;
   return ptr;
}
int parser_pdvl_event_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_event_identifiers(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_edge_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_event_signal_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_EVENT_DECLARATION;
   return ptr;
}
int parser_pdvl_list_of_event_identifiers_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_event_identifiers_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_EVENT_IDENTIFIERS;
   return ptr;
}
int parser_pdvl_list_of_event_identifiers_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_event_identifiers_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_EVENT_IDENTIFIERS;
   return ptr;
}
int parser_pdvl_list_of_event_identifiers (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_list_of_event_identifiers_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_list_of_event_identifiers_v1(source, ptr, node);
}
int parser_pdvl_list_of_event_identifiers_si_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_EVENT_IDENTIFIERS_SI_H0;
   return ptr;
}
int parser_pdvl_list_of_event_identifiers_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 118) /* v */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_list_of_event_identifiers_si_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_PDVL_LIST_OF_EVENT_IDENTIFIERS_SI;
   return ptr;
}
int parser_pdvl_list_of_event_identifiers_by_name (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_event_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_list_of_event_identifiers_by_name_extension_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_PDVL_LIST_OF_EVENT_IDENTIFIERS_BY_NAME;
   return ptr;
}
int parser_pdvl_list_of_event_identifiers_by_name_extension (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_event_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_EVENT_IDENTIFIERS_BY_NAME_EXTENSION;
   return ptr;
}
int parser_pdvl_event_identifier_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_event_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_EVENT_IDENTIFIER;
   return ptr;
}
int parser_pdvl_event_identifier_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_event_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_EVENT_IDENTIFIER;
   return ptr;
}
int parser_pdvl_event_identifier (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_event_identifier_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_event_identifier_v1(source, ptr, node);
}
int parser_pdvl_event_identifier_by_name (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 101) /* e */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_PDVL_EVENT_IDENTIFIER_BY_NAME;
   return ptr;
}
int parser_pdvl_event_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 118) /* v */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_EVENT_SI;
   return ptr;
}
int parser_pdvl_event_signal_name (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_EVENT_SIGNAL_NAME;
   return ptr;
}
int parser_pdvl_transaction_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_declaration_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_DECLARATION;
   return ptr;
}
int parser_pdvl_transaction_declaration_body (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_transaction_replace(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_statement_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_TRANSACTION_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_transaction_replace (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_TRANSACTION_REPLACE;
   return ptr;
}
int parser_pdvl_transaction_identifier_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_IDENTIFIER;
   return ptr;
}
int parser_pdvl_transaction_identifier_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_IDENTIFIER;
   return ptr;
}
int parser_pdvl_transaction_identifier (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_transaction_identifier_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_transaction_identifier_v1(source, ptr, node);
}
int parser_pdvl_transaction_identifier_by_name (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 116) /* t */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 114) /* r */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME;
   return ptr;
}
int parser_pdvl_transaction_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_SI;
   return ptr;
}
int parser_pdvl_transaction_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_finite_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_pipe_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_priority_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_unique_single(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_unique_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_unique0_single(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_unique0_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_next_state_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_emit_delayed_event(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v10 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_do_not_emit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement_v11 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_emit(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_transaction_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v9(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_statement_v10(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_transaction_statement_v11(source, ptr, node);
}
int parser_pdvl_transaction_body (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_transaction_statement_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_TRANSACTION_BODY;
   return ptr;
}
int parser_pdvl_priority_unique_propagate (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 103) /* g */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_PRIORITY_UNIQUE_PROPAGATE;
   return ptr;
}
int parser_pdvl_transaction_priority_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_priority_unique_propagate(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_priority_unique_list_entry_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_priority_unique_default_entry(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_TRANSACTION_PRIORITY_LIST;
   return ptr;
}
int parser_pdvl_transaction_priority_unique_list_entry (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_single_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY;
   return ptr;
}
int parser_pdvl_transaction_priority_unique_default_entry (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_default_single_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY;
   return ptr;
}
int parser_pdvl_transaction_unique_single (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 113) /* q */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_priority_unique_propagate(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_priority_unique_list_entry(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_UNIQUE_SINGLE;
   return ptr;
}
int parser_pdvl_transaction_unique_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 113) /* q */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_priority_unique_propagate(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_priority_unique_list_entry_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_priority_unique_default_entry(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_TRANSACTION_UNIQUE_LIST;
   return ptr;
}
int parser_pdvl_transaction_unique0_single (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 113) /* q */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 48) /* 0 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_priority_unique_propagate(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_priority_unique_list_entry(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   if (appended) ptrNode -> next = subNode;
   else ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_UNIQUE0_SINGLE;
   return ptr;
}
int parser_pdvl_transaction_unique0_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 113) /* q */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 48) /* 0 */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_priority_unique_propagate(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_priority_unique_list_entry_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_priority_unique_default_entry(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      if (appended) ptrNode -> next = subNode;
      else ptrNode -> sub = subNode;
      appended = true;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_TRANSACTION_UNIQUE0_LIST;
   return ptr;
}
int parser_pdvl_transaction_state_body (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_semikolon(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_TRANSACTION_STATE_BODY;
   return ptr;
}
int parser_pdvl_transaction_state_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_STATE_STATEMENT;
   return ptr;
}
int parser_pdvl_if_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_else_if_declaration_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_else_declaration(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_IF_DECLARATION;
   return ptr;
}
int parser_pdvl_else_if_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_ELSE_IF_DECLARATION;
   return ptr;
}
int parser_pdvl_else_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_ELSE_DECLARATION;
   return ptr;
}
int parser_pdvl_case_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_case_declaration_item_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_CASE_DECLARATION;
   return ptr;
}
int parser_pdvl_case_declaration_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_case_declaration_default(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CASE_DECLARATION_ITEM;
   return ptr;
}
int parser_pdvl_case_declaration_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_case_declaration_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CASE_DECLARATION_ITEM;
   return ptr;
}
int parser_pdvl_case_declaration_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_case_declaration_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_case_declaration_item_v1(source, ptr, node);
}
int parser_pdvl_case_declaration_constant_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_CASE_DECLARATION_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_pdvl_case_declaration_default (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_CASE_DECLARATION_DEFAULT;
   return ptr;
}
int parser_pdvl_for_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_initialization(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_iteration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_FOR_DECLARATION;
   return ptr;
}
int parser_pdvl_foreach_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_foreach_list_def(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_FOREACH_DECLARATION;
   return ptr;
}
int parser_pdvl_at_condition (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_condition_control(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_condition_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_AT_CONDITION;
   return ptr;
}
int parser_pdvl_condition_control_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_false_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CONDITION_CONTROL;
   return ptr;
}
int parser_pdvl_condition_control_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_true_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CONDITION_CONTROL;
   return ptr;
}
int parser_pdvl_condition_control (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_condition_control_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_condition_control_v1(source, ptr, node);
}
int parser_pdvl_at_false_condition (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 64) /* @ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 33) /* ! */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_AT_FALSE_CONDITION;
   return ptr;
}
int parser_pdvl_at_true_condition (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 64) /* @ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_AT_TRUE_CONDITION;
   return ptr;
}
int parser_pdvl_condition_expression_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_condition_expression_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CONDITION_EXPRESSION;
   return ptr;
}
int parser_pdvl_condition_expression_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_condition_expression_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CONDITION_EXPRESSION;
   return ptr;
}
int parser_pdvl_condition_expression (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_condition_expression_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_condition_expression_v1(source, ptr, node);
}
int parser_pdvl_condition_expression_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_expression_list_brackets(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_CONDITION_EXPRESSION_PREV0;
   return ptr;
}
int parser_pdvl_condition_expression_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_CONDITION_EXPRESSION_PREV1;
   return ptr;
}
int parser_pdvl_expression_list_brackets (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_sv_expression_list_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_EXPRESSION_LIST_BRACKETS;
   return ptr;
}
int parser_pdvl_at_keyword_prio (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 120) /* x */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_AT_KEYWORD_PRIO;
   return ptr;
}
int parser_pdvl_at_keyword (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_keyword_prio(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_AT_KEYWORD;
   return ptr;
}
int parser_pdvl_transaction_at_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_single_else_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_AT_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_at_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_single_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_AT_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_at_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_transaction_at_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_transaction_at_statement_v1(source, ptr, node);
}
int parser_pdvl_transaction_at_single_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_semikolon(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_default_single_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_semikolon(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_TRANSACTION_DEFAULT_SINGLE_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_at_single_else_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_single_else_statement_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_at_single_else_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_single_else_statement_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_at_single_else_statement_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_single_else_statement_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_at_single_else_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_transaction_at_single_else_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_transaction_at_single_else_statement_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_transaction_at_single_else_statement_v2(source, ptr, node);
}
int parser_pdvl_transaction_at_single_else_statement_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_semikolon(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV0;
   return ptr;
}
int parser_pdvl_transaction_at_single_else_statement_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_single_else_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_semikolon(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV1;
   return ptr;
}
int parser_pdvl_transaction_at_single_else_statement_prev2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_at_condition(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_at_single_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_semikolon(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV2;
   return ptr;
}
int parser_pdvl_transaction_finite_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_finite_keyword(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_transaction_finite_one_hot_keyword_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_finite_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_transaction_finite_case_item_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_TRANSACTION_FINITE_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_finite_keyword (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_TRANSACTION_FINITE_KEYWORD;
   return ptr;
}
int parser_pdvl_transaction_finite_one_hot_keyword (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 95) /* _ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_TRANSACTION_FINITE_ONE_HOT_KEYWORD;
   return ptr;
}
int parser_pdvl_transaction_finite_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_FINITE_IDENTIFIER;
   return ptr;
}
int parser_pdvl_transaction_finite_case_item (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_FINITE_CASE_ITEM;
   return ptr;
}
int parser_pdvl_transaction_pipe_statement_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_pipe_const_transaction_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_PIPE_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_pipe_statement_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_pipe_range_transaction_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_TRANSACTION_PIPE_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_pipe_statement (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_transaction_pipe_statement_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_transaction_pipe_statement_v1(source, ptr, node);
}
int parser_pdvl_pipe_const_transaction_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_pipe_keyword(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_PIPE_CONST_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_pipe_range_transaction_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_pipe_keyword(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_packed_dimension(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_transaction_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_PIPE_RANGE_TRANSACTION_STATEMENT;
   return ptr;
}
int parser_pdvl_transaction_pipe_keyword (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   node -> id = G_PDVL_TRANSACTION_PIPE_KEYWORD;
   return ptr;
}
int parser_pdvl_next_state_statement (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 35) /* # */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_NEXT_STATE_STATEMENT;
   return ptr;
}
int parser_pdvl_emit_delayed_event (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_delay_control(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_EMIT_DELAYED_EVENT;
   return ptr;
}
int parser_pdvl_emit (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_expression_list_brackets(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_EMIT;
   return ptr;
}
int parser_pdvl_do_not_emit (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 33) /* ! */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_DO_NOT_EMIT;
   return ptr;
}
int parser_pdvl_build_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 98) /* b */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_build_command_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_BUILD_COMMAND;
   return ptr;
}
int parser_pdvl_build_command_body_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_parameter_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_place_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_uniquify_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_join_body_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v4 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_join_cluster_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v5 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_remove_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v6 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_replace_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v7 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_move_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v8 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_route_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v9 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_if_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v10 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_case_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v11 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_for_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body_v12 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_foreach_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_BUILD_COMMAND_BODY;
   return ptr;
}
int parser_pdvl_build_command_body (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_build_command_body_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v3(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v4(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v5(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v6(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v7(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v8(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v9(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v10(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_pdvl_build_command_body_v11(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_build_command_body_v12(source, ptr, node);
}
int parser_pdvl_uniquify_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 113) /* q */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 121) /* y */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_UNIQUIFY_COMMAND;
   return ptr;
}
int parser_pdvl_place_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_module_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_PLACE_COMMAND;
   return ptr;
}
int parser_pdvl_join_body_command_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_join_body_command_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_JOIN_BODY_COMMAND;
   return ptr;
}
int parser_pdvl_join_body_command_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_join_body_command_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_JOIN_BODY_COMMAND;
   return ptr;
}
int parser_pdvl_join_body_command (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_join_body_command_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_join_body_command_v1(source, ptr, node);
}
int parser_pdvl_join_body_command_prev0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 106) /* j */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_join_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_JOIN_BODY_COMMAND_PREV0;
   return ptr;
}
int parser_pdvl_join_body_command_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 106) /* j */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_join_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_semikolon(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_JOIN_BODY_COMMAND_PREV1;
   return ptr;
}
int parser_pdvl_join_body (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_cluster_declaration_body_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_JOIN_BODY;
   return ptr;
}
int parser_pdvl_join_cluster_command_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_join_cluster_body_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_JOIN_CLUSTER_COMMAND;
   return ptr;
}
int parser_pdvl_join_cluster_command_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_join_cluster_single_command(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_JOIN_CLUSTER_COMMAND;
   return ptr;
}
int parser_pdvl_join_cluster_command (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_join_cluster_command_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_join_cluster_command_v1(source, ptr, node);
}
int parser_pdvl_join_cluster_body_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 106) /* j */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_join_cluster_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_JOIN_CLUSTER_BODY_COMMAND;
   return ptr;
}
int parser_pdvl_join_cluster_body (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_hierarchical_name(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_JOIN_CLUSTER_BODY;
   return ptr;
}
int parser_pdvl_join_cluster_single_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 106) /* j */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_hierarchical_name(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_JOIN_CLUSTER_SINGLE_COMMAND;
   return ptr;
}
int parser_pdvl_replace_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_REPLACE_COMMAND;
   return ptr;
}
int parser_pdvl_remove_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 118) /* v */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_list_of_si_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_REMOVE_COMMAND;
   return ptr;
}
int parser_pdvl_move_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 118) /* v */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_list_of_si_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_MOVE_COMMAND;
   return ptr;
}
int parser_pdvl_route_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_hierarchical_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_route_signal_identifier_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_ROUTE_COMMAND;
   return ptr;
}
int parser_pdvl_route_signal_identifier (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_ROUTE_SIGNAL_IDENTIFIER;
   return ptr;
}
int parser_pdvl_if_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_build_command_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_else_if_command_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_pdvl_else_command(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      ptrNode = subNode; }
   else delete subNode;
   node -> id = G_PDVL_IF_COMMAND;
   return ptr;
}
int parser_pdvl_else_if_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_build_command_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_ELSE_IF_COMMAND;
   return ptr;
}
int parser_pdvl_else_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_build_command_body_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_ELSE_COMMAND;
   return ptr;
}
int parser_pdvl_case_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_case_command_item_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 115) /* s */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_CASE_COMMAND;
   return ptr;
}
int parser_pdvl_case_command_item_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_case_command_default(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CASE_COMMAND_ITEM;
   return ptr;
}
int parser_pdvl_case_command_item_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_case_command_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_CASE_COMMAND_ITEM;
   return ptr;
}
int parser_pdvl_case_command_item (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_case_command_item_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_case_command_item_v1(source, ptr, node);
}
int parser_pdvl_case_command_constant_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_list_of_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_build_command_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_CASE_COMMAND_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_pdvl_list_of_constant_expression_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_LIST_OF_CONSTANT_EXPRESSION_H0;
   return ptr;
}
int parser_pdvl_list_of_constant_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_list_of_constant_expression_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_PDVL_LIST_OF_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_pdvl_case_command_default (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 108) /* l */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_build_command_body_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_CASE_COMMAND_DEFAULT;
   return ptr;
}
int parser_pdvl_for_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_initialization(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 59) /* ; */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_genvar_iteration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_build_command_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_FOR_COMMAND;
   return ptr;
}
int parser_pdvl_foreach_command (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_foreach_list_def(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_pdvl_build_command_body_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_FOREACH_COMMAND;
   return ptr;
}
int parser_pdvl_foreach_list_def_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_foreach_list(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_FOREACH_LIST_DEF;
   return ptr;
}
int parser_pdvl_foreach_list_def_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_foreach_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_FOREACH_LIST_DEF;
   return ptr;
}
int parser_pdvl_foreach_list_def (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_foreach_list_def_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_foreach_list_def_v1(source, ptr, node);
}
int parser_pdvl_foreach_list (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_usi(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_list_of_usi_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_FOREACH_LIST;
   return ptr;
}
int parser_pdvl_foreach_constant_expression (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_constant_expression(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_FOREACH_CONSTANT_EXPRESSION;
   return ptr;
}
int parser_gallina_grammar (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_declaration_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GALLINA_GRAMMAR;
   return ptr;
}
int parser_ga_declaration_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_inductive_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_DECLARATION;
   return ptr;
}
int parser_ga_declaration_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_definition_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_DECLARATION;
   return ptr;
}
int parser_ga_declaration_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_fixpoint_declaration(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_DECLARATION;
   return ptr;
}
int parser_ga_declaration (string &source, int ptr, NODE *node) {
   int newPtr = parser_ga_declaration_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_ga_declaration_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_ga_declaration_v2(source, ptr, node);
}
int parser_ga_inductive_declaration_h0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_inductive_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_INDUCTIVE_DECLARATION_H0;
   return ptr;
}
int parser_ga_inductive_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 73) /* I */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 117) /* u */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 118) /* v */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_inductive_declaration_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_INDUCTIVE_DECLARATION;
   return ptr;
}
int parser_ga_inductive_term_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_inductive_term_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_INDUCTIVE_TERM;
   return ptr;
}
int parser_ga_inductive_term_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_inductive_term_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_INDUCTIVE_TERM;
   return ptr;
}
int parser_ga_inductive_term (string &source, int ptr, NODE *node) {
   int newPtr = parser_ga_inductive_term_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_ga_inductive_term_v1(source, ptr, node);
}
int parser_ga_inductive_term_prev0_h0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_args(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_INDUCTIVE_TERM_PREV0_H0;
   return ptr;
}
int parser_ga_inductive_term_prev0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 124) /* | */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_inductive_term_prev0_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GA_INDUCTIVE_TERM_PREV0;
   return ptr;
}
int parser_ga_inductive_term_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 124) /* | */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_INDUCTIVE_TERM_PREV1;
   return ptr;
}
int parser_ga_definition_declaration_h1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_args(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_DEFINITION_DECLARATION_H1;
   return ptr;
}
int parser_ga_definition_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 68) /* D */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 102) /* f */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_definition_declaration_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_DEFINITION_DECLARATION;
   return ptr;
}
int parser_ga_fixpoint_declaration_h2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_args(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_FIXPOINT_DECLARATION_H2;
   return ptr;
}
int parser_ga_fixpoint_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 70) /* F */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 120) /* x */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 112) /* p */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_fixpoint_declaration_h2_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_FIXPOINT_DECLARATION;
   return ptr;
}
int parser_ga_args_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_args_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_ARGS;
   return ptr;
}
int parser_ga_args_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_args_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_ARGS;
   return ptr;
}
int parser_ga_args (string &source, int ptr, NODE *node) {
   int newPtr = parser_ga_args_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_ga_args_v1(source, ptr, node);
}
int parser_ga_args_prev0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_ARGS_PREV0;
   return ptr;
}
int parser_ga_args_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_type(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_ARGS_PREV1;
   return ptr;
}
int parser_ga_type (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TYPE;
   return ptr;
}
int parser_pdvl_theorem_declaration (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_theorem_declaration_body(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_THEOREM_DECLARATION;
   return ptr;
}
int parser_pdvl_theorem_declaration_body (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_theorem_identifier(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 123) /* { */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_theorem_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 125) /* } */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_PDVL_THEOREM_DECLARATION_BODY;
   return ptr;
}
int parser_pdvl_theorem_identifier_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_theorem_identifier_by_name(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_THEOREM_IDENTIFIER;
   return ptr;
}
int parser_pdvl_theorem_identifier_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_pdvl_theorem_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_THEOREM_IDENTIFIER;
   return ptr;
}
int parser_pdvl_theorem_identifier (string &source, int ptr, NODE *node) {
   int newPtr = parser_pdvl_theorem_identifier_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_pdvl_theorem_identifier_v1(source, ptr, node);
}
int parser_pdvl_theorem_identifier_by_name (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   NODE* ptrNode = node;
   node -> id = 0xffffffff;
   unsigned zip = 0;
   unsigned cnt = 0;
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 116) /* t */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 104) /* h */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if ((source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr < source.length()) while (((source.at(ptr) >= 97)  /* a */ & (source.at(ptr) <= 122) /* z */ ) | ((source.at(ptr) >= 65)  /* A */ & (source.at(ptr) <= 90) /* Z */ ) | ((source.at(ptr) >= 48)  /* 0 */ & (source.at(ptr) <= 57) /* 9 */ ) | (source.at(ptr) == 95) /* _ */ ) {
      zip += source.at(ptr) << (8 * cnt);
      if (cnt == 3) {
         NODE* subNode = new NODE();
         subNode -> id = zip;
         subNode -> sub = NULL;
         subNode -> next = NULL;
         if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
         else ptrNode -> next = subNode;
         ptrNode = subNode;
         zip = 0;
         cnt = 0; }
      else cnt ++;
      ptr++;
      if (ptr >= source.length()) break; }
   if (cnt > 0) {
      NODE* subNode = new NODE();
      subNode -> id = zip;
      subNode -> sub = NULL;
      subNode -> next = NULL;
      if (ptrNode -> id == 0xffffffff) ptrNode -> sub = subNode;
      else ptrNode -> next = subNode; }
   node -> id = G_PDVL_THEOREM_IDENTIFIER_BY_NAME;
   return ptr;
}
int parser_pdvl_theorem_si (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_PDVL_THEOREM_SI;
   return ptr;
}
int parser_pdvl_theorem_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_hypothesis_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_theorem_statement_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_PDVL_THEOREM_STATEMENT;
   return ptr;
}
int parser_ga_theorem_declaration (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 84) /* T */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 111) /* o */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 114) /* r */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 58) /* : */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_hypothesis_statement(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_theorem_statement_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GA_THEOREM_DECLARATION;
   return ptr;
}
int parser_ga_hypothesis_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_HYPOTHESIS_STATEMENT;
   return ptr;
}
int parser_ga_theorem_statement (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 46) /* . */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_THEOREM_STATEMENT;
   return ptr;
}
int parser_ga_term_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM;
   return ptr;
}
int parser_ga_term_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM;
   return ptr;
}
int parser_ga_term_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM;
   return ptr;
}
int parser_ga_term_v3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term_prev3(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM;
   return ptr;
}
int parser_ga_term (string &source, int ptr, NODE *node) {
   int newPtr = parser_ga_term_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_ga_term_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_ga_term_v2(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_ga_term_v3(source, ptr, node);
}
int parser_ga_term_prev0_h0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM_PREV0_H0;
   return ptr;
}
int parser_ga_term_prev0_h1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_match_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM_PREV0_H1;
   return ptr;
}
int parser_ga_term_prev0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 109) /* m */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 97) /* a */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 99) /* c */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si_nest(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_term_prev0_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 119) /* w */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 105) /* i */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 116) /* t */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 104) /* h */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   newPtr = parser_ga_term_prev0_h1_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 101) /* e */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 110) /* n */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 100) /* d */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_TERM_PREV0;
   return ptr;
}
int parser_ga_term_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_TERM_PREV1;
   return ptr;
}
int parser_ga_term_prev2_h2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM_PREV2_H2;
   return ptr;
}
int parser_ga_term_prev2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_term_prev2_h2_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GA_TERM_PREV2;
   return ptr;
}
int parser_ga_term_prev3_h3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM_PREV3_H3;
   return ptr;
}
int parser_ga_term_prev3 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_sv_number(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_term_prev3_h3_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GA_TERM_PREV3;
   return ptr;
}
int parser_si_nest_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si_nest_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SI_NEST;
   return ptr;
}
int parser_si_nest_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si_nest_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SI_NEST;
   return ptr;
}
int parser_si_nest (string &source, int ptr, NODE *node) {
   int newPtr = parser_si_nest_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_si_nest_v1(source, ptr, node);
}
int parser_si_nest_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si_nest(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_SI_NEST_PREV0;
   return ptr;
}
int parser_si_nest_prev1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_SI_NEST_PREV1;
   return ptr;
}
int parser_ga_match_option_v0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_match_option_prev0(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_MATCH_OPTION;
   return ptr;
}
int parser_ga_match_option_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_match_option_prev1(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_MATCH_OPTION;
   return ptr;
}
int parser_ga_match_option_v2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_match_option_prev2(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_MATCH_OPTION;
   return ptr;
}
int parser_ga_match_option (string &source, int ptr, NODE *node) {
   int newPtr = parser_ga_match_option_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   newPtr = parser_ga_match_option_v1(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_ga_match_option_v2(source, ptr, node);
}
int parser_ga_match_option_prev0_h0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_match_option(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_MATCH_OPTION_PREV0_H0;
   return ptr;
}
int parser_ga_match_option_prev0 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_match_option_prev0_h0_zom(source, ptr, subNode);
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> next = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GA_MATCH_OPTION_PREV0;
   return ptr;
}
int parser_ga_match_option_prev1_h1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_match_option(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_MATCH_OPTION_PREV1_H1;
   return ptr;
}
int parser_ga_match_option_prev1 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 95) /* _ */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_match_option_prev1_h1_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GA_MATCH_OPTION_PREV1;
   return ptr;
}
int parser_ga_match_option_prev2_h2 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_match_option(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_MATCH_OPTION_PREV2_H2;
   return ptr;
}
int parser_ga_match_option_prev2 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 44) /* , */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   subNode -> id = 0;
   int newPtr = parser_ga_match_option_prev2_h2_zom(source, ptr, subNode);
   bool appended = false;
   if (newPtr > -1) ptr = newPtr;
   if (subNode -> id > 0) {
      ptrNode -> sub = subNode;
      ptrNode = subNode;
      while (ptrNode -> next != NULL) ptrNode = ptrNode -> next; }
   else delete subNode;
   node -> id = G_GA_MATCH_OPTION_PREV2;
   return ptr;
}
int parser_ga_match_term (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 124) /* | */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_match_option(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 61) /* = */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 62) /* > */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      parserDeleteTree(false, node);
      return -1; }
   ptrNode -> next = subNode;
   ptrNode = subNode;
   node -> id = G_GA_MATCH_TERM;
   return ptr;
}
int parser_ga_term_args_v0 (string &source, int ptr, NODE *node) {
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 40) /* ( */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      return -1; }
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_ga_term(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   ptr = getNext(source, ptr);
   if (ptr == -1) return -1;
   if (ptr >= source.length()) return -1;
   if (source.at(ptr) == 41) /* ) */ {
      ptr ++; }
   else {
      if (ptr > maxPtr) maxPtr = ptr;
      parserDeleteTree(false, node);
      return -1; }
   node -> id = G_GA_TERM_ARGS;
   return ptr;
}
int parser_ga_term_args_v1 (string &source, int ptr, NODE *node) {
   NODE* ptrNode = node;
   NODE* subNode = new NODE();
   subNode -> sub = NULL;
   subNode -> next = NULL;
   ptr = parser_si(source, ptr, subNode);
   if (ptr == -1) {
      delete subNode;
      return -1; }
   ptrNode -> sub = subNode;
   ptrNode = subNode;
   node -> id = G_GA_TERM_ARGS;
   return ptr;
}
int parser_ga_term_args (string &source, int ptr, NODE *node) {
   int newPtr = parser_ga_term_args_v0(source, ptr, node);
   if (newPtr > -1) return newPtr;
   return parser_ga_term_args_v1(source, ptr, node);
}
int parser_pdvl_grammar_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_grammar(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_description_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_description(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_cpp_grammar_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_cpp_grammar(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_tmp_transaction_case_item_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_tmp_transaction_case_item(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_preprocessing_or_declaration_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_preprocessing_or_declaration(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_cpp_expression_list_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_cpp_expression_list(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_cpp_select_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_cpp_select(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_cpp_declaration_statement_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_cpp_declaration_statement_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_cpp_statement_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_cpp_statement(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_parameter_declaration_clause_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_parameter_declaration_clause_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_file_path_spec_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_file_path_spec_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_non_port_module_item_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_non_port_module_item(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_ports_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_ports_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_port_declarations_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_port_declarations_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_port_expression_prev1_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_port_expression_prev1_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_variable_dimension_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_variable_dimension(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_struct_union_member_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_struct_union_member(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_net_decl_assignments_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_net_decl_assignments_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_unpacked_dimension_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_unpacked_dimension(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_port_identifiers_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_port_identifiers_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_tf_variable_identifiers_h2_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_tf_variable_identifiers_h2(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_variable_decl_assignments_h3_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_variable_decl_assignments_h3(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_tf_item_declaration_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_tf_item_declaration(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_function_body_declaration_port_implicit_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_function_body_declaration_port_implicit_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_function_body_declaration_port_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_function_body_declaration_port_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_task_body_declaration_port_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_task_body_declaration_port_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_module_instantiation_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_module_instantiation_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_module_param_instantiation_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_module_param_instantiation_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_port_connections_prev0_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_port_connections_prev0_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_port_connections_prev1_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_port_connections_prev1_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_generate_item_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_generate_item(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_case_generate_item_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_case_generate_item(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_variable_assignments_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_variable_assignments_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_statement_or_null_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_statement_or_null(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_event_expression_prev4_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_event_expression_prev4_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_case_item_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_case_item(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_of_variable_declarations_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_of_variable_declarations_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_loop_variables_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_loop_variables_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_expression_list_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_expression_list(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_constant_expression_list_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_constant_expression_list(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_select_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_select(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_constant_select_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_constant_select_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_variable_lvalue_list_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_variable_lvalue_list(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_us_digit_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_us_digit(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_list_attr_spec_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_list_attr_spec(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_attr_spec_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_attr_spec_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_sv_hierarchical_identifier_list_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_sv_hierarchical_identifier_list(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_hierarchical_name_h2_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_hierarchical_name_h2(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_declaration_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_declaration(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_cluster_declaration_body_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_cluster_declaration_body(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_list_of_si_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_list_of_si(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_data_declaration_body_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_data_declaration_body(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_cond_conditional_statement_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_cond_conditional_statement(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_tf_port_list_brackets_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_tf_port_list_brackets_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_list_of_cond_identifiers_by_name_extension_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_list_of_cond_identifiers_by_name_extension(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_list_of_event_identifiers_si_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_list_of_event_identifiers_si_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_list_of_event_identifiers_by_name_extension_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_list_of_event_identifiers_by_name_extension(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_transaction_statement_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_transaction_statement(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_transaction_priority_unique_list_entry_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_transaction_priority_unique_list_entry(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_else_if_declaration_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_else_if_declaration(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_case_declaration_item_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_case_declaration_item(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_transaction_finite_one_hot_keyword_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_transaction_finite_one_hot_keyword(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_transaction_finite_case_item_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_transaction_finite_case_item(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_build_command_body_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_build_command_body(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_join_cluster_body_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_join_cluster_body(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_route_signal_identifier_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_route_signal_identifier(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_else_if_command_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_else_if_command(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_case_command_item_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_case_command_item(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_pdvl_list_of_constant_expression_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_pdvl_list_of_constant_expression_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_list_of_usi_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_list_of_usi(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_declaration_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_declaration(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_inductive_declaration_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_inductive_declaration_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_inductive_term_prev0_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_inductive_term_prev0_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_definition_declaration_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_definition_declaration_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_fixpoint_declaration_h2_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_fixpoint_declaration_h2(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_theorem_statement_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_theorem_statement(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_term_prev0_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_term_prev0_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_term_prev0_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_term_prev0_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_term_prev2_h2_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_term_prev2_h2(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_term_prev3_h3_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_term_prev3_h3(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_match_option_prev0_h0_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_match_option_prev0_h0(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_match_option_prev1_h1_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_match_option_prev1_h1(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int parser_ga_match_option_prev2_h2_zom (string &source, int ptr, NODE *node) {
   bool found = false;
   while (true) {
      NODE* subNode = new NODE();
      int newPtr = parser_ga_match_option_prev2_h2(source, ptr, subNode);
      if (newPtr > -1) {
         if (!(found)) {
            node -> id = subNode -> id;
            node -> sub = subNode -> sub;
            node -> next = subNode -> next;
            delete subNode;
            found = true; }
         else {
            node -> next = subNode;
            node = subNode; } }
      else {
         delete subNode;
         return ptr; }
      ptr = newPtr; }
}
int getNext (string &source, int ptr) {
   if (ptr > 0) if (ptr >= source.length()) return -1;
   while (source.at(ptr) != -1) {
      if (source.at(ptr) == ' ') ptr ++;
      else return ptr;
      if (ptr >= source.length()) return -1; }
   maxPtr = ptr;
   return -1; }
void parserDeleteTree (bool del, NODE * node) {
   if (!(node -> sub == NULL)) parserDeleteTree(true, node -> sub);
   if (!(node -> next == NULL)) parserDeleteTree(true, node -> next);
   if (del) delete(node); }
