
#include <writer.h>

void writer_grammar (string &out, NODE *node) {
   while (node -> id == G_PDVL_GRAMMAR) {
      writer_pdvl_grammar(out, node -> sub);
      return; }
   while (node -> id == G_SV_DESCRIPTION) {
      writer_sv_description(out, node -> sub);
      return; }
   while (node -> id == G_CPP_GRAMMAR) {
      writer_cpp_grammar(out, node -> sub);
      return; }
}
void writer_tmp_transaction_case_statement (string &out, NODE *node) {
   if (node -> id == G_SV_UNIQUE_PRIORITY) {
      writer_sv_unique_priority(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_TMP_TRANSACTION_CASE_KEYWORD) {
      writer_tmp_transaction_case_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_TMP_TRANSACTION_CASE_ITEM) {
      writer_tmp_transaction_case_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" endcase");
}
void writer_tmp_transaction_case_keyword (string &out, NODE *node) {
   out.append(" case");
}
void writer_tmp_transaction_case_expression (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_tmp_transaction_case_item (string &out, NODE *node) {
   if (node -> id == G_TMP_TRANSACTION_DEFAULT_CASE) {
      writer_tmp_transaction_default_case(out, node -> sub);
      return; }
   if (node -> id == G_TMP_TRANSACTION_ITEM_CASE) {
      writer_tmp_transaction_item_case(out, node -> sub);
      return; }
}
void writer_tmp_transaction_item_case (string &out, NODE *node) {
   if (node -> id == G_TMP_TRANSACTION_CASE_ITEM_EXPRESSION) {
      writer_tmp_transaction_case_item_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_tmp_transaction_default_case (string &out, NODE *node) {
   out.append(" default");
   out.append(" :");
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_tmp_transaction_case_item_expression (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_grammar (string &out, NODE *node) {
   while (node -> id == G_PREPROCESSING_OR_DECLARATION) {
      writer_preprocessing_or_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_preprocessing_or_declaration (string &out, NODE *node) {
   if (node -> id == G_PREPROCESSING_FILE) {
      writer_preprocessing_file(out, node -> sub);
      return; }
   if (node -> id == G_CPP_DECLARATION) {
      writer_cpp_declaration(out, node -> sub);
      return; }
}
void writer_cpp_function_call (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_CPP_EXPRESSION) { writer_cpp_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_CPP_EXPRESSION_LIST) { writer_cpp_expression_list(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" )");
}
void writer_cpp_unary_expression (string &out, NODE *node) {
   if (node -> id == G_CPP_UNARY_OPERATOR) {
      writer_cpp_unary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_function_call_assignment (string &out, NODE *node) {
   if (node -> id == G_CPP_FUNCTION_CALL) {
      writer_cpp_function_call(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_cpp_unary_operator (string &out, NODE *node) {
   if (node -> id == G_OPERATOR_PLUS) {
      writer_operator_plus(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_MINUS) {
      writer_operator_minus(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_NAND) {
      writer_operator_nand(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_NOR) {
      writer_operator_nor(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_NXOR) {
      writer_operator_nxor(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_EXCLAMATION) {
      writer_operator_exclamation(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_TILDE) {
      writer_operator_tilde(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_AND) {
      writer_operator_and(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_OR) {
      writer_operator_or(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_XOR) {
      writer_operator_xor(out, node -> sub);
      return; }
}
void writer_cpp_assignment_expression (string &out, NODE *node) {
   if (node -> id == G_CPP_VARIABLE_LVALUE) {
      writer_cpp_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" =");
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_variable_lvalue (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_CPP_SELECT) {
      writer_cpp_select(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_cpp_expression (string &out, NODE *node) {
   if (node -> id == G_CPP_ASSIGNMENT_EXPRESSION) {
      writer_cpp_assignment_expression(out, node -> sub);
      return; }
   if (node -> id == G_CPP_CONDITIONAL_EXPRESSION) {
      writer_cpp_conditional_expression(out, node -> sub);
      return; }
   if (node -> id == G_CPP_BINARY_EXPRESSION) {
      writer_cpp_binary_expression(out, node -> sub);
      return; }
   if (node -> id == G_CPP_UNARY_EXPRESSION) {
      writer_cpp_unary_expression(out, node -> sub);
      return; }
   if (node -> id == G_SV_INC_OR_DEC_EXPRESSION) {
      writer_sv_inc_or_dec_expression(out, node -> sub);
      return; }
   if (node -> id == G_CPP_PRIMARY) {
      writer_cpp_primary(out, node -> sub);
      return; }
   if (node -> id == G_SV_PRIMARY) {
      writer_sv_primary(out, node -> sub);
      return; }
}
void writer_cpp_conditional_expression (string &out, NODE *node) {
   if (node -> id == G_CPP_COND_PREDICATE) {
      writer_cpp_cond_predicate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ?");
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_cond_predicate (string &out, NODE *node) {
   if (node -> id == G_CPP_BRACKET_EXPRESSION) {
      writer_cpp_bracket_expression(out, node -> sub);
      return; }
   if (node -> id == G_CPP_PRIMARY) {
      writer_cpp_primary(out, node -> sub);
      return; }
}
void writer_cpp_bracket_expression (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_CPP_EXPRESSION) { writer_cpp_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_cpp_binary_expression (string &out, NODE *node) {
   if (node -> id == G_CPP_BINARY_EXPRESSION_PRIMARY) {
      writer_cpp_binary_expression_primary(out, node -> sub);
      return; }
   if (node -> id == G_CPP_BINARY_EXPRESSION_UNARY) {
      writer_cpp_binary_expression_unary(out, node -> sub);
      return; }
}
void writer_cpp_binary_expression_primary (string &out, NODE *node) {
   if (node -> id == G_CPP_PRIMARY) {
      writer_cpp_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_OPERATOR) {
      writer_sv_binary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_binary_expression_unary (string &out, NODE *node) {
   if (node -> id == G_CPP_UNARY_EXPRESSION) {
      writer_cpp_unary_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_OPERATOR) {
      writer_sv_binary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_primary (string &out, NODE *node) {
   if (node -> id == G_CPP_FUNCTION_CALL) {
      writer_cpp_function_call(out, node -> sub);
      return; }
   if (node -> id == G_CPP_BRACKET_MINTYPMAX_EXPRESSION) {
      writer_cpp_bracket_mintypmax_expression(out, node -> sub);
      return; }
   if (node -> id == G_CPP_IDENTIFIER_SELECT) {
      writer_cpp_identifier_select(out, node -> sub);
      return; }
   if (node -> id == G_CPP_PRIMARY_LITERAL) {
      writer_cpp_primary_literal(out, node -> sub);
      return; }
}
void writer_cpp_primary_literal (string &out, NODE *node) {
   if (node -> id == G_CPP_UNSIGNED_NUMBER) {
      writer_cpp_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_bracket_mintypmax_expression (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_CPP_MINTYPMAX_EXPRESSION) { writer_cpp_mintypmax_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_cpp_mintypmax_expression (string &out, NODE *node) {
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_identifier_select (string &out, NODE *node) {
   if (node -> id == G_CPP_ASTERISK_IDENTIFIER) {
      writer_cpp_asterisk_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_CPP_AMPERSAND_IDENTIFIER) {
      writer_cpp_ampersand_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_CPP_SELECT) {
      writer_cpp_select(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_cpp_asterisk_identifier (string &out, NODE *node) {
   out.append(" *");
}
void writer_cpp_ampersand_identifier (string &out, NODE *node) {
   out.append(" &");
}
void writer_cpp_select (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_cpp_expression_list (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_unsigned_number (string &out, NODE *node) {
   out.append(" 0x");
   if (node -> id == G_CPP_HEX_VALUE) {
      writer_cpp_hex_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" U");
}
void writer_cpp_hex_value (string &out, NODE *node) {
   if (node -> id == G_CPP_HEX_VALUE_PREV0) {
      writer_cpp_hex_value_prev0(out, node -> sub);
      return; }
   if (node -> id == G_CPP_HEX_VALUE_PREV1) {
      writer_cpp_hex_value_prev1(out, node -> sub);
      return; }
}
void writer_cpp_hex_value_prev0 (string &out, NODE *node) {
   if (node -> id == G_HEX_DIGIT) {
      writer_hex_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_CPP_HEX_VALUE) {
      writer_cpp_hex_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_hex_value_prev1 (string &out, NODE *node) {
   if (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_CPP_HEX_VALUE) {
      writer_cpp_hex_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_statement (string &out, NODE *node) {
   if (node -> id == G_CPP_EXPRESSION_STATEMENT) {
      writer_cpp_expression_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_COMPOUND_STATEMENT) {
      writer_cpp_compound_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_EMPTY_COMPOUND_STATEMENT) {
      writer_cpp_empty_compound_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_SELECTION_STATEMENT) {
      writer_cpp_selection_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_LABELED_STATEMENT) {
      writer_cpp_labeled_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_FUNCTION_CALL_ASSIGNMENT) {
      writer_cpp_function_call_assignment(out, node -> sub);
      return; }
   if (node -> id == G_CPP_REF_EXPRESSION_STATEMENT) {
      writer_cpp_ref_expression_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_BREAK_STATEMENT) {
      writer_cpp_break_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_DECLARATION_STATEMENT) {
      writer_cpp_declaration_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_RETURN_STATEMENT) {
      writer_cpp_return_statement(out, node -> sub);
      return; }
}
void writer_condition (string &out, NODE *node) {
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_declaration_statement_h0 (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_DECIMAL_NUMBER) {
      writer_sv_decimal_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_cpp_declaration_statement (string &out, NODE *node) {
   out.append(" unsigned");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_CPP_DECLARATION_STATEMENT_H0) {
      writer_cpp_declaration_statement_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" ;");
}
void writer_cpp_return_statement (string &out, NODE *node) {
   out.append(" return");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_cpp_labeled_statement (string &out, NODE *node) {
   if (node -> id == G_CPP_LABELED_DEFAULT_STATEMENT) {
      writer_cpp_labeled_default_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_LABELED_CASE_STATEMENT) {
      writer_cpp_labeled_case_statement(out, node -> sub);
      return; }
}
void writer_cpp_labeled_case_statement (string &out, NODE *node) {
   out.append(" case");
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   while (node -> id == G_CPP_STATEMENT) {
      writer_cpp_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_cpp_labeled_default_statement (string &out, NODE *node) {
   out.append(" default");
   out.append(" :");
   while (node -> id == G_CPP_STATEMENT) {
      writer_cpp_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_cpp_break_statement (string &out, NODE *node) {
   out.append(" break;");
}
void writer_cpp_expression_statement (string &out, NODE *node) {
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_cpp_ref_expression_statement (string &out, NODE *node) {
   out.append(" *");
   if (node -> id == G_CPP_EXPRESSION) {
      writer_cpp_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_cpp_compound_statement (string &out, NODE *node) {
   out.append(" {");
   while (node -> id == G_CPP_STATEMENT) {
      writer_cpp_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_cpp_empty_compound_statement (string &out, NODE *node) {
   out.append(" {");
   out.append(" }");
}
void writer_cpp_selection_statement (string &out, NODE *node) {
   if (node -> id == G_CPP_IF_ELSE_SELECTION_STATEMENT) {
      writer_cpp_if_else_selection_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_IF_SELECTION_STATEMENT) {
      writer_cpp_if_selection_statement(out, node -> sub);
      return; }
   if (node -> id == G_CPP_CASE_SELECTION_STATEMENT) {
      writer_cpp_case_selection_statement(out, node -> sub);
      return; }
}
void writer_cpp_if_else_selection_statement (string &out, NODE *node) {
   out.append(" if");
   out.append(" (");if (node -> id == G_CONDITION) { writer_condition(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_CPP_STATEMENT) {
      writer_cpp_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" else");
   if (node -> id == G_CPP_STATEMENT) {
      writer_cpp_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_if_selection_statement (string &out, NODE *node) {
   out.append(" if");
   out.append(" (");if (node -> id == G_CONDITION) { writer_condition(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_CPP_STATEMENT) {
      writer_cpp_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_case_selection_statement (string &out, NODE *node) {
   out.append(" switch");
   out.append(" (");if (node -> id == G_CONDITION) { writer_condition(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_CPP_STATEMENT) {
      writer_cpp_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_declaration (string &out, NODE *node) {
   if (node -> id == G_TEMPLATE_DECLARATION) {
      writer_template_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_decl_specifier_seq (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_declarator (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PARAMETERS_AND_QUALIFIERS) {
      writer_parameters_and_qualifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_parameters_and_qualifiers (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_PARAMETER_DECLARATION_CLAUSE) { writer_parameter_declaration_clause(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_parameter_declaration_clause_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_CPP_PARAMETER_DECLARATION) {
      writer_cpp_parameter_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_parameter_declaration_clause (string &out, NODE *node) {
   if (node -> id == G_CPP_PARAMETER_DECLARATION) {
      writer_cpp_parameter_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_PARAMETER_DECLARATION_CLAUSE_H0) {
      writer_parameter_declaration_clause_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_cpp_parameter_declaration (string &out, NODE *node) {
   if (node -> id == G_CPP_PARAMETER_DECLARATION_PREV0) {
      writer_cpp_parameter_declaration_prev0(out, node -> sub);
      return; }
   if (node -> id == G_CPP_PARAMETER_DECLARATION_PREV1) {
      writer_cpp_parameter_declaration_prev1(out, node -> sub);
      return; }
   if (node -> id == G_CPP_PARAMETER_DECLARATION_PREV2) {
      writer_cpp_parameter_declaration_prev2(out, node -> sub);
      return; }
}
void writer_cpp_parameter_declaration_prev0 (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" *");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_parameter_declaration_prev1 (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" [");
   out.append(" ]");
}
void writer_cpp_parameter_declaration_prev2 (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_template_declaration_h0 (string &out, NODE *node) {
   out.append(" *");
}
void writer_template_declaration (string &out, NODE *node) {
   if (node -> id == G_DECL_SPECIFIER_SEQ) {
      writer_decl_specifier_seq(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_TEMPLATE_DECLARATION_H0) {
      writer_template_declaration_h0(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_DECLARATOR) {
      writer_declarator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_FUNCTION_BODY) {
      writer_function_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_function_body (string &out, NODE *node) {
   if (node -> id == G_CPP_COMPOUND_STATEMENT) {
      writer_cpp_compound_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_preprocessing_file (string &out, NODE *node) {
   if (node -> id == G_GROUP) {
      writer_group(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_group (string &out, NODE *node) {
   if (node -> id == G_GROUP_PART) {
      writer_group_part(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_group_part (string &out, NODE *node) {
   if (node -> id == G_CONTROL_LINE) {
      writer_control_line(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_control_line (string &out, NODE *node) {
   out.append(" #include");
   if (node -> id == G_H_PP_TOKENS) {
      writer_h_pp_tokens(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_h_pp_tokens (string &out, NODE *node) {
   if (node -> id == G_HEADER_NAME_TOKENS) {
      writer_header_name_tokens(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_header_name_tokens (string &out, NODE *node) {
   out.append(" <");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" .h>");
}
void writer_sv_library_text (string &out, NODE *node) {
   if (node -> id == G_SV_LIBRARY_DESCRIPTION) {
      writer_sv_library_description(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_library_description (string &out, NODE *node) {
   if (node -> id == G_SV_INCLUDE_STATEMENT) {
      writer_sv_include_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_include_statement (string &out, NODE *node) {
   out.append(" `");
   out.append(" include");
   if (node -> id == G_SV_FILE_PATH_SPEC) {
      writer_sv_file_path_spec(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_file_path_spec_h1 (string &out, NODE *node) {
   out.append(" .");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_file_path_spec (string &out, NODE *node) {
   out.append(" \"");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_FILE_PATH_SPEC_H1) {
      writer_sv_file_path_spec_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" \"");
}
void writer_sv_description (string &out, NODE *node) {
   if (node -> id == G_SV_MODULE_DECLARATION) {
      writer_sv_module_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_LIBRARY_TEXT) {
      writer_sv_library_text(out, node -> sub);
      return; }
}
void writer_sv_module_ansi_header (string &out, NODE *node) {
   if (node -> id == G_SV_MODULE_KEYWORD) {
      writer_sv_module_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_MODULE_IDENTIFIER) {
      writer_sv_module_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_LIST_OF_PORT_DECLARATIONS) { writer_sv_list_of_port_declarations(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   out.append(" ;");
}
void writer_sv_module_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_MODULE_ANSI_HEADER) {
      writer_sv_module_ansi_header(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_NON_PORT_MODULE_ITEM) {
      writer_sv_non_port_module_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" endmodule");
}
void writer_sv_module_keyword (string &out, NODE *node) {
   out.append(" module");
}
void writer_sv_list_of_ports_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_PORT) {
      writer_sv_port(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_ports (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SV_PORT) { writer_sv_port(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_SV_LIST_OF_PORTS_H0) { writer_sv_list_of_ports_h0(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" )");
}
void writer_sv_list_of_port_declarations_h1 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_ANSI_PORT_DECLARATION) {
      writer_sv_ansi_port_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_port_declarations (string &out, NODE *node) {
   if (node -> id == G_SV_ANSI_PORT_DECLARATION) {
      writer_sv_ansi_port_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LIST_OF_PORT_DECLARATIONS_H1) {
      writer_sv_list_of_port_declarations_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_port_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_INOUT_DECLARATION) {
      writer_sv_inout_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_INPUT_DECLARATION) {
      writer_sv_input_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_OUTPUT_DECLARATION) {
      writer_sv_output_declaration(out, node -> sub);
      return; }
}
void writer_sv_port (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_PREV0) {
      writer_sv_port_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_PORT_PREV1) {
      writer_sv_port_prev1(out, node -> sub);
      return; }
}
void writer_sv_port_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_EXPRESSION) {
      writer_sv_port_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_port_prev1 (string &out, NODE *node) {
   out.append(" .");
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_PORT_EXPRESSION) { writer_sv_port_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_port_expression (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_EXPRESSION_PREV0) {
      writer_sv_port_expression_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_PORT_EXPRESSION_PREV1) {
      writer_sv_port_expression_prev1(out, node -> sub);
      return; }
}
void writer_sv_port_expression_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_REFERENCE) {
      writer_sv_port_reference(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_port_expression_prev1_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_PORT_REFERENCE) {
      writer_sv_port_reference(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_port_expression_prev1 (string &out, NODE *node) {
   out.append(" {");
   if (node -> id == G_SV_PORT_REFERENCE) {
      writer_sv_port_reference(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_PORT_EXPRESSION_PREV1_H0) {
      writer_sv_port_expression_prev1_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_sv_port_reference (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_CONSTANT_SELECT) {
      writer_sv_constant_select(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_port_direction (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_INPUT_DIRECTION) {
      writer_sv_port_input_direction(out, node -> sub);
      return; }
   if (node -> id == G_SV_PORT_OUTPUT_DIRECTION) {
      writer_sv_port_output_direction(out, node -> sub);
      return; }
   if (node -> id == G_SV_PORT_INOUT_DIRECTION) {
      writer_sv_port_inout_direction(out, node -> sub);
      return; }
}
void writer_sv_port_input_direction (string &out, NODE *node) {
   out.append(" input");
}
void writer_sv_port_output_direction (string &out, NODE *node) {
   out.append(" output");
}
void writer_sv_port_inout_direction (string &out, NODE *node) {
   out.append(" inout");
}
void writer_sv_ansi_port_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_module_common_item (string &out, NODE *node) {
   if (node -> id == G_SV_MODULE_OR_GENERATE_ITEM_DECLARATION) {
      writer_sv_module_or_generate_item_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONTINUOUS_ASSIGN) {
      writer_sv_continuous_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ALWAYS_CONSTRUCT) {
      writer_sv_always_construct(out, node -> sub);
      return; }
   if (node -> id == G_SV_LOOP_GENERATE_CONSTRUCT) {
      writer_sv_loop_generate_construct(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONDITIONAL_GENERATE_CONSTRUCT) {
      writer_sv_conditional_generate_construct(out, node -> sub);
      return; }
}
void writer_sv_module_item (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_DECLARATION) {
      writer_sv_port_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_NON_PORT_MODULE_ITEM) {
      writer_sv_non_port_module_item(out, node -> sub);
      return; }
}
void writer_sv_module_or_generate_item (string &out, NODE *node) {
   if (node -> id == G_SV_PARAMETER_OVERRIDE) {
      writer_sv_parameter_override(out, node -> sub);
      return; }
   if (node -> id == G_SV_MODULE_PARAM_INSTANTIATION) {
      writer_sv_module_param_instantiation(out, node -> sub);
      return; }
   if (node -> id == G_SV_MODULE_INSTANTIATION) {
      writer_sv_module_instantiation(out, node -> sub);
      return; }
   if (node -> id == G_SV_MODULE_COMMON_ITEM) {
      writer_sv_module_common_item(out, node -> sub);
      return; }
}
void writer_sv_module_or_generate_item_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_PACKAGE_OR_GENERATE_ITEM_DECLARATION) {
      writer_sv_package_or_generate_item_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_non_port_module_item (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_DECLARATION) {
      writer_sv_port_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_GENERATE_REGION) {
      writer_sv_generate_region(out, node -> sub);
      return; }
   if (node -> id == G_SV_MODULE_OR_GENERATE_ITEM) {
      writer_sv_module_or_generate_item(out, node -> sub);
      return; }
   if (node -> id == G_SV_INCLUDE_STATEMENT) {
      writer_sv_include_statement(out, node -> sub);
      return; }
}
void writer_sv_parameter_override (string &out, NODE *node) {
   out.append(" defparam");
   if (node -> id == G_SV_LIST_OF_DEFPARAM_ASSIGNMENTS) {
      writer_sv_list_of_defparam_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_package_or_generate_item_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_TASK_DECLARATION) {
      writer_sv_task_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_FUNCTION_DECLARATION) {
      writer_sv_function_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_DATA_DECLARATION) {
      writer_sv_data_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_NET_DECLARATION) {
      writer_sv_net_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_PARAMETER_DECLARATION) {
      writer_sv_parameter_declaration(out, node -> sub);
      return; }
}
void writer_sv_parameter_declaration (string &out, NODE *node) {
   out.append(" parameter");
   if (node -> id == G_SV_LIST_OF_PARAM_ASSIGNMENTS) {
      writer_sv_list_of_param_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_inout_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_INOUT_TYPE_DECLARATION) {
      writer_sv_inout_type_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_INOUT_IMPLICIT_DECLARATION) {
      writer_sv_inout_implicit_declaration(out, node -> sub);
      return; }
}
void writer_sv_inout_type_declaration (string &out, NODE *node) {
   out.append(" inout");
   if (node -> id == G_SV_NET_PORT_TYPE) {
      writer_sv_net_port_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_LIST_OF_PORT_IDENTIFIERS) {
      writer_sv_list_of_port_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_inout_implicit_declaration (string &out, NODE *node) {
   out.append(" inout");
   if (node -> id == G_SV_LIST_OF_PORT_IDENTIFIERS) {
      writer_sv_list_of_port_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_input_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_INPUT_TYPE_DECLARATION) {
      writer_sv_input_type_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_INPUT_IMPLICIT_DECLARATION) {
      writer_sv_input_implicit_declaration(out, node -> sub);
      return; }
}
void writer_sv_input_type_declaration (string &out, NODE *node) {
   out.append(" input");
   if (node -> id == G_SV_NET_PORT_TYPE) {
      writer_sv_net_port_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_LIST_OF_PORT_IDENTIFIERS) {
      writer_sv_list_of_port_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_input_implicit_declaration (string &out, NODE *node) {
   out.append(" input");
   if (node -> id == G_SV_LIST_OF_PORT_IDENTIFIERS) {
      writer_sv_list_of_port_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_output_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_OUTPUT_TYPE_DECLARATION) {
      writer_sv_output_type_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_OUTPUT_IMPLICIT_DECLARATION) {
      writer_sv_output_implicit_declaration(out, node -> sub);
      return; }
}
void writer_sv_output_type_declaration (string &out, NODE *node) {
   out.append(" output");
   if (node -> id == G_SV_NET_PORT_TYPE) {
      writer_sv_net_port_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_LIST_OF_PORT_IDENTIFIERS) {
      writer_sv_list_of_port_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_output_implicit_declaration (string &out, NODE *node) {
   out.append(" output");
   if (node -> id == G_SV_LIST_OF_PORT_IDENTIFIERS) {
      writer_sv_list_of_port_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_data_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_LIST_OF_VARIABLE_DECL_ASSIGNMENTS) {
      writer_sv_list_of_variable_decl_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_net_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_NET_TYPE_DECLARATION_SPLIT_TYPE) {
      writer_sv_net_type_declaration_split_type(out, node -> sub);
      return; }
   if (node -> id == G_SV_NET_DECLARATION_SPLIT_IMPLICIT) {
      writer_sv_net_declaration_split_implicit(out, node -> sub);
      return; }
}
void writer_sv_net_type_declaration_split_type (string &out, NODE *node) {
   if (node -> id == G_SV_NET_TYPE) {
      writer_sv_net_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_LIST_OF_NET_DECL_ASSIGNMENTS) {
      writer_sv_list_of_net_decl_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_net_declaration_split_implicit (string &out, NODE *node) {
   if (node -> id == G_SV_NET_TYPE) {
      writer_sv_net_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_LIST_OF_NET_DECL_ASSIGNMENTS) {
      writer_sv_list_of_net_decl_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_type_declaration (string &out, NODE *node) {
   out.append(" typedef");
   if (node -> id == G_SV_DATA_TYPE) {
      writer_sv_data_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_TYPE_IDENTIFIER) {
      writer_sv_type_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_VARIABLE_DIMENSION) {
      writer_sv_variable_dimension(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" ;");
}
void writer_sv_data_type (string &out, NODE *node) {
   if (node -> id == G_SV_DATA_TYPE_PREV0) {
      writer_sv_data_type_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_DATA_TYPE_PREV1) {
      writer_sv_data_type_prev1(out, node -> sub);
      return; }
   if (node -> id == G_SV_DATA_TYPE_PREV2) {
      writer_sv_data_type_prev2(out, node -> sub);
      return; }
   if (node -> id == G_SV_DATA_TYPE_PREV3) {
      writer_sv_data_type_prev3(out, node -> sub);
      return; }
   if (node -> id == G_SV_DATA_TYPE_PREV4) {
      writer_sv_data_type_prev4(out, node -> sub);
      return; }
}
void writer_sv_data_type_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_INTEGER_VECTOR_TYPE) {
      writer_sv_integer_vector_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PACKED_DIMENSION_LIST) {
      writer_sv_packed_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_data_type_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_INTEGER_STRUCT_UNION_TYPE) {
      writer_sv_integer_struct_union_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_data_type_prev2 (string &out, NODE *node) {
   if (node -> id == G_SV_INTEGER_ENUM_TYPE) {
      writer_sv_integer_enum_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_data_type_prev3 (string &out, NODE *node) {
   if (node -> id == G_SV_INTEGER_ATOM_TYPE) {
      writer_sv_integer_atom_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_data_type_prev4 (string &out, NODE *node) {
   if (node -> id == G_SV_INTEGER_TYPE_IDENTIFIER_TYPE) {
      writer_sv_integer_type_identifier_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_integer_struct_union_type (string &out, NODE *node) {
   if (node -> id == G_SV_STRUCT_UNION) {
      writer_sv_struct_union(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PACKED_KEYWORD) {
      writer_sv_packed_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_SV_STRUCT_UNION_MEMBER) {
      writer_sv_struct_union_member(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_sv_packed_keyword (string &out, NODE *node) {
   out.append(" packed");
}
void writer_sv_integer_enum_type (string &out, NODE *node) {
   out.append(" enum");
   if (node -> id == G_SV_ENUM_BASE_TYPE) {
      writer_sv_enum_base_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   if (node -> id == G_SV_ENUM_NAME_DECLARATION_LIST) {
      writer_sv_enum_name_declaration_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" }");
}
void writer_sv_integer_type_identifier_type (string &out, NODE *node) {
   if (node -> id == G_SV_CLASS_SCOPE) {
      writer_sv_class_scope(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_TYPE_IDENTIFIER) {
      writer_sv_type_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_data_type_or_implicit (string &out, NODE *node) {
   if (node -> id == G_SV_DATA_TYPE) {
      writer_sv_data_type(out, node -> sub);
      return; }
   if (node -> id == G_SV_IMPLICIT_DATA_TYPE) {
      writer_sv_implicit_data_type(out, node -> sub);
      return; }
}
void writer_sv_implicit_data_type (string &out, NODE *node) {
   if (node -> id == G_SV_PACKED_DIMENSION_LIST) {
      writer_sv_packed_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_enum_base_type (string &out, NODE *node) {
   if (node -> id == G_SV_INTEGER_VECTOR_TYPE) {
      writer_sv_integer_vector_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PACKED_DIMENSION_LIST) {
      writer_sv_packed_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_enum_name_declaration_list_h0 (string &out, NODE *node) {
   out.append(" =");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_enum_name_declaration_list_h1 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_ENUM_NAME_DECLARATION_LIST) {
      writer_sv_enum_name_declaration_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_enum_name_declaration_list (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_ENUM_NAME_DECLARATION_LIST_H0) {
      writer_sv_enum_name_declaration_list_h0(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_ENUM_NAME_DECLARATION_LIST_H1) {
      writer_sv_enum_name_declaration_list_h1(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_class_scope (string &out, NODE *node) {
   if (node -> id == G_SV_CLASS_TYPE) {
      writer_sv_class_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ::");
}
void writer_sv_class_type (string &out, NODE *node) {
   if (node -> id == G_SV_CLASS_IDENTIFIER) {
      writer_sv_class_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_integer_atom_type (string &out, NODE *node) {
   out.append(" integer");
}
void writer_sv_integer_vector_type (string &out, NODE *node) {
   if (node -> id == G_SV_INTEGER_VECTOR_TYPE_BIT) {
      writer_sv_integer_vector_type_bit(out, node -> sub);
      return; }
   if (node -> id == G_SV_INTEGER_VECTOR_TYPE_LOGIC) {
      writer_sv_integer_vector_type_logic(out, node -> sub);
      return; }
   if (node -> id == G_SV_INTEGER_VECTOR_TYPE_REG) {
      writer_sv_integer_vector_type_reg(out, node -> sub);
      return; }
}
void writer_sv_integer_vector_type_bit (string &out, NODE *node) {
   out.append(" bit");
}
void writer_sv_integer_vector_type_logic (string &out, NODE *node) {
   out.append(" logic");
}
void writer_sv_integer_vector_type_reg (string &out, NODE *node) {
   out.append(" reg");
}
void writer_sv_net_type (string &out, NODE *node) {
   if (node -> id == G_SV_NET_TYPE_SPLIT_WIRE) {
      writer_sv_net_type_split_wire(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_net_type_split_wire (string &out, NODE *node) {
   out.append(" wire");
}
void writer_sv_net_port_type (string &out, NODE *node) {
   if (node -> id == G_SV_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_struct_union_member (string &out, NODE *node) {
   if (node -> id == G_SV_DATA_TYPE) {
      writer_sv_data_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_VARIABLE_DIMENSION) {
      writer_sv_variable_dimension(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" ;");
}
void writer_sv_data_type_or_void (string &out, NODE *node) {
   if (node -> id == G_SV_DATA_TYPE) {
      writer_sv_data_type(out, node -> sub);
      return; }
}
void writer_sv_struct_union (string &out, NODE *node) {
   if (node -> id == G_SV_STRUCT) {
      writer_sv_struct(out, node -> sub);
      return; }
   if (node -> id == G_SV_UNION) {
      writer_sv_union(out, node -> sub);
      return; }
}
void writer_sv_struct (string &out, NODE *node) {
   out.append(" struct");
}
void writer_sv_union (string &out, NODE *node) {
   out.append(" union");
}
void writer_sv_delay_value (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_defparam_assignments (string &out, NODE *node) {
   if (node -> id == G_SV_DEFPARAM_ASSIGNMENT) {
      writer_sv_defparam_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_net_decl_assignments_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_NET_DECL_ASSIGNMENT) {
      writer_sv_net_decl_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_net_decl_assignments (string &out, NODE *node) {
   if (node -> id == G_SV_NET_DECL_ASSIGNMENT) {
      writer_sv_net_decl_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LIST_OF_NET_DECL_ASSIGNMENTS_H0) {
      writer_sv_list_of_net_decl_assignments_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_list_of_param_assignments (string &out, NODE *node) {
   if (node -> id == G_SV_PARAM_ASSIGNMENT) {
      writer_sv_param_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_port_identifiers_h1 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_LIST_OF_PORT_IDENTIFIERS) {
      writer_sv_list_of_port_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_port_identifiers (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_UNPACKED_DIMENSION) {
      writer_sv_unpacked_dimension(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   while (node -> id == G_SV_LIST_OF_PORT_IDENTIFIERS_H1) {
      writer_sv_list_of_port_identifiers_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_list_of_tf_variable_identifiers_h2 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_tf_variable_identifiers (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LIST_OF_TF_VARIABLE_IDENTIFIERS_H2) {
      writer_sv_list_of_tf_variable_identifiers_h2(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_list_of_variable_decl_assignments_h3 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_VARIABLE_DECL_ASSIGNMENT) {
      writer_sv_variable_decl_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_variable_decl_assignments (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_DECL_ASSIGNMENT) {
      writer_sv_variable_decl_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LIST_OF_VARIABLE_DECL_ASSIGNMENTS_H3) {
      writer_sv_list_of_variable_decl_assignments_h3(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_defparam_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_HIERARCHICAL_PARAMETER_IDENTIFIER) {
      writer_sv_hierarchical_parameter_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" =");
   if (node -> id == G_SV_CONSTANT_PARAM_EXPRESSION) {
      writer_sv_constant_param_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_net_decl_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_NET_IDENTIFIER) {
      writer_sv_net_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_UNPACKED_DIMENSION) {
      writer_sv_unpacked_dimension(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_SV_BLOCKING_ASSIGN_EXPRESSION) {
      writer_sv_blocking_assign_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_param_assignment (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" =");
   if (node -> id == G_SV_CONSTANT_PARAM_EXPRESSION) {
      writer_sv_constant_param_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_variable_decl_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_IDENTIFIER) {
      writer_sv_variable_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_VARIABLE_DIMENSION) {
      writer_sv_variable_dimension(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_unpacked_dimension (string &out, NODE *node) {
   if (node -> id == G_SV_UNPACKED_DIMENSION_CONSTANT_RANGE) {
      writer_sv_unpacked_dimension_constant_range(out, node -> sub);
      return; }
   if (node -> id == G_SV_UNPACKED_DIMENSION_CONSTANT_EXPRESSION) {
      writer_sv_unpacked_dimension_constant_expression(out, node -> sub);
      return; }
}
void writer_sv_unpacked_dimension_constant_range (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_CONSTANT_RANGE) {
      writer_sv_constant_range(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_sv_unpacked_dimension_constant_expression (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_sv_packed_dimension_list (string &out, NODE *node) {
   if (node -> id == G_SV_PACKED_DIMENSION) {
      writer_sv_packed_dimension(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PACKED_DIMENSION_LIST) {
      writer_sv_packed_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_packed_dimension (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_CONSTANT_RANGE) {
      writer_sv_constant_range(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_sv_variable_dimension (string &out, NODE *node) {
   if (node -> id == G_SV_UNPACKED_DIMENSION) {
      writer_sv_unpacked_dimension(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_function_data_type_or_implicit (string &out, NODE *node) {
   if (node -> id == G_SV_DATA_TYPE_OR_VOID) {
      writer_sv_data_type_or_void(out, node -> sub);
      return; }
   if (node -> id == G_SV_IMPLICIT_DATA_TYPE) {
      writer_sv_implicit_data_type(out, node -> sub);
      return; }
}
void writer_sv_function_declaration (string &out, NODE *node) {
   out.append(" function");
   if (node -> id == G_SV_FUNCTION_BODY_DECLARATION) {
      writer_sv_function_body_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_function_body_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_FUNCTION_BODY_DECLARATION_ITEM_IMPLICIT) {
      writer_sv_function_body_declaration_item_implicit(out, node -> sub);
      return; }
   if (node -> id == G_SV_FUNCTION_BODY_DECLARATION_ITEM) {
      writer_sv_function_body_declaration_item(out, node -> sub);
      return; }
   if (node -> id == G_SV_FUNCTION_BODY_DECLARATION_PORT_IMPLICIT) {
      writer_sv_function_body_declaration_port_implicit(out, node -> sub);
      return; }
   if (node -> id == G_SV_FUNCTION_BODY_DECLARATION_PORT) {
      writer_sv_function_body_declaration_port(out, node -> sub);
      return; }
}
void writer_sv_function_body_declaration_item_implicit (string &out, NODE *node) {
   if (node -> id == G_SV_TF_IDENTIFIER) {
      writer_sv_tf_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
   while (node -> id == G_SV_TF_ITEM_DECLARATION) {
      writer_sv_tf_item_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" endfunction");
}
void writer_sv_function_body_declaration_item (string &out, NODE *node) {
   if (node -> id == G_SV_FUNCTION_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_function_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_TF_IDENTIFIER) {
      writer_sv_tf_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
   while (node -> id == G_SV_TF_ITEM_DECLARATION) {
      writer_sv_tf_item_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" endfunction");
}
void writer_sv_function_body_declaration_port_implicit_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_FUNCTION_PORT_LIST) {
      writer_sv_function_port_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_function_body_declaration_port_implicit (string &out, NODE *node) {
   if (node -> id == G_SV_TF_IDENTIFIER) {
      writer_sv_tf_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_FUNCTION_PORT_ITEM) { writer_sv_function_port_item(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_SV_FUNCTION_BODY_DECLARATION_PORT_IMPLICIT_H0) { writer_sv_function_body_declaration_port_implicit_h0(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" )");
   out.append(" ;");
   while (node -> id == G_SV_TF_ITEM_DECLARATION) {
      writer_sv_tf_item_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" endfunction");
}
void writer_sv_function_body_declaration_port_h1 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_FUNCTION_PORT_LIST) {
      writer_sv_function_port_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_function_body_declaration_port (string &out, NODE *node) {
   if (node -> id == G_SV_FUNCTION_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_function_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_TF_IDENTIFIER) {
      writer_sv_tf_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_FUNCTION_PORT_ITEM) { writer_sv_function_port_item(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_SV_FUNCTION_BODY_DECLARATION_PORT_H1) { writer_sv_function_body_declaration_port_h1(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" )");
   out.append(" ;");
   while (node -> id == G_SV_TF_ITEM_DECLARATION) {
      writer_sv_tf_item_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" endfunction");
}
void writer_sv_task_declaration (string &out, NODE *node) {
   out.append(" task");
   if (node -> id == G_SV_TASK_BODY_DECLARATION) {
      writer_sv_task_body_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_task_body_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_TASK_BODY_DECLARATION_ITEM) {
      writer_sv_task_body_declaration_item(out, node -> sub);
      return; }
   if (node -> id == G_SV_TASK_BODY_DECLARATION_PORT) {
      writer_sv_task_body_declaration_port(out, node -> sub);
      return; }
}
void writer_sv_task_body_declaration_item (string &out, NODE *node) {
   if (node -> id == G_SV_TF_IDENTIFIER) {
      writer_sv_tf_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
   while (node -> id == G_SV_TF_ITEM_DECLARATION) {
      writer_sv_tf_item_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" endtask");
}
void writer_sv_task_body_declaration_port_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_TASK_PORT_LIST) {
      writer_sv_task_port_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_task_body_declaration_port (string &out, NODE *node) {
   if (node -> id == G_SV_TF_IDENTIFIER) {
      writer_sv_tf_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_TASK_PORT_ITEM) { writer_sv_task_port_item(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_SV_TASK_BODY_DECLARATION_PORT_H0) { writer_sv_task_body_declaration_port_h0(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" )");
   out.append(" ;");
   while (node -> id == G_SV_TF_ITEM_DECLARATION) {
      writer_sv_tf_item_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" endtask");
}
void writer_sv_tf_item_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_TF_PORT_DECLARATION) {
      writer_sv_tf_port_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_PARAMETER_DECLARATION) {
      writer_sv_parameter_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_DATA_DECLARATION) {
      writer_sv_data_declaration(out, node -> sub);
      return; }
}
void writer_sv_function_port_list (string &out, NODE *node) {
   if (node -> id == G_SV_FUNCTION_PORT_ITEM) {
      writer_sv_function_port_item(out, node -> sub);
      return; }
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      return; }
}
void writer_sv_task_port_list (string &out, NODE *node) {
   if (node -> id == G_SV_TASK_PORT_ITEM) {
      writer_sv_task_port_item(out, node -> sub);
      return; }
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      return; }
}
void writer_sv_function_port_item (string &out, NODE *node) {
   if (node -> id == G_SV_FUNCTION_PORT_ITEM_PREV0) {
      writer_sv_function_port_item_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_FUNCTION_PORT_ITEM_PREV1) {
      writer_sv_function_port_item_prev1(out, node -> sub);
      return; }
   if (node -> id == G_SV_FUNCTION_PORT_ITEM_PREV2) {
      writer_sv_function_port_item_prev2(out, node -> sub);
      return; }
}
void writer_sv_function_port_item_prev0 (string &out, NODE *node) {
   out.append(" input");
   if (node -> id == G_SV_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_function_port_item_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_function_port_item_prev2 (string &out, NODE *node) {
   out.append(" input");
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_task_port_item (string &out, NODE *node) {
   if (node -> id == G_SV_TASK_PORT_ITEM_PREV0) {
      writer_sv_task_port_item_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_TASK_PORT_ITEM_PREV1) {
      writer_sv_task_port_item_prev1(out, node -> sub);
      return; }
}
void writer_sv_task_port_item_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_DIRECTION) {
      writer_sv_port_direction(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_task_port_item_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_DIRECTION) {
      writer_sv_port_direction(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_tf_port_direction (string &out, NODE *node) {
   if (node -> id == G_SV_PORT_DIRECTION) {
      writer_sv_port_direction(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_tf_port_declaration (string &out, NODE *node) {
   if (node -> id == G_SV_TF_PORT_DECLARATION_PREV0) {
      writer_sv_tf_port_declaration_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_TF_PORT_DECLARATION_PREV1) {
      writer_sv_tf_port_declaration_prev1(out, node -> sub);
      return; }
}
void writer_sv_tf_port_declaration_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_TF_PORT_DIRECTION) {
      writer_sv_tf_port_direction(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_DATA_TYPE_OR_IMPLICIT) {
      writer_sv_data_type_or_implicit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_LIST_OF_TF_VARIABLE_IDENTIFIERS) {
      writer_sv_list_of_tf_variable_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_tf_port_declaration_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_TF_PORT_DIRECTION) {
      writer_sv_tf_port_direction(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_LIST_OF_TF_VARIABLE_IDENTIFIERS) {
      writer_sv_list_of_tf_variable_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_module_instantiation_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_HIERARCHICAL_INSTANCE) {
      writer_sv_hierarchical_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_module_instantiation (string &out, NODE *node) {
   if (node -> id == G_SV_MODULE_IDENTIFIER) {
      writer_sv_module_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_HIERARCHICAL_INSTANCE) {
      writer_sv_hierarchical_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_MODULE_INSTANTIATION_H0) {
      writer_sv_module_instantiation_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" ;");
}
void writer_sv_module_param_instantiation_h1 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_HIERARCHICAL_INSTANCE) {
      writer_sv_hierarchical_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_module_param_instantiation (string &out, NODE *node) {
   if (node -> id == G_SV_MODULE_IDENTIFIER) {
      writer_sv_module_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PARAMETER_VALUE_ASSIGNMENT) {
      writer_sv_parameter_value_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_HIERARCHICAL_INSTANCE) {
      writer_sv_hierarchical_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_MODULE_PARAM_INSTANTIATION_H1) {
      writer_sv_module_param_instantiation_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" ;");
}
void writer_sv_parameter_value_assignment (string &out, NODE *node) {
   out.append(" #");
   out.append(" (");if (node -> id == G_SV_LIST_OF_PARAMETER_ASSIGNMENTS) { writer_sv_list_of_parameter_assignments(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_list_of_parameter_assignments (string &out, NODE *node) {
   if (node -> id == G_SV_NAMED_LIST_OF_PARAMETER_ASSIGNMENTS) {
      writer_sv_named_list_of_parameter_assignments(out, node -> sub);
      return; }
   if (node -> id == G_SV_ORDERED_LIST_OF_PARAMETER_ASSIGNMENTS) {
      writer_sv_ordered_list_of_parameter_assignments(out, node -> sub);
      return; }
}
void writer_sv_named_list_of_parameter_assignments_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_NAMED_LIST_OF_PARAMETER_ASSIGNMENTS) {
      writer_sv_named_list_of_parameter_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_named_list_of_parameter_assignments (string &out, NODE *node) {
   if (node -> id == G_SV_NAMED_PARAMETER_ASSIGNMENT) {
      writer_sv_named_parameter_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_NAMED_LIST_OF_PARAMETER_ASSIGNMENTS_H0) {
      writer_sv_named_list_of_parameter_assignments_h0(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_ordered_list_of_parameter_assignments_h1 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_ORDERED_LIST_OF_PARAMETER_ASSIGNMENTS) {
      writer_sv_ordered_list_of_parameter_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_ordered_list_of_parameter_assignments (string &out, NODE *node) {
   if (node -> id == G_SV_ORDERED_PARAMETER_ASSIGNMENT) {
      writer_sv_ordered_parameter_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_ORDERED_LIST_OF_PARAMETER_ASSIGNMENTS_H1) {
      writer_sv_ordered_list_of_parameter_assignments_h1(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_named_parameter_assignment (string &out, NODE *node) {
   out.append(" .");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_ordered_parameter_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hierarchical_instance (string &out, NODE *node) {
   if (node -> id == G_SV_NAME_OF_INSTANCE) {
      writer_sv_name_of_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_LIST_OF_PORT_CONNECTIONS) { writer_sv_list_of_port_connections(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_name_of_instance (string &out, NODE *node) {
   if (node -> id == G_SV_INSTANCE_IDENTIFIER) {
      writer_sv_instance_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_port_connections (string &out, NODE *node) {
   if (node -> id == G_SV_LIST_OF_PORT_CONNECTIONS_PREV0) {
      writer_sv_list_of_port_connections_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_LIST_OF_PORT_CONNECTIONS_PREV1) {
      writer_sv_list_of_port_connections_prev1(out, node -> sub);
      return; }
}
void writer_sv_list_of_port_connections_prev0_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_ORDERED_PORT_CONNECTION) {
      writer_sv_ordered_port_connection(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_port_connections_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_ORDERED_PORT_CONNECTION) {
      writer_sv_ordered_port_connection(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LIST_OF_PORT_CONNECTIONS_PREV0_H0) {
      writer_sv_list_of_port_connections_prev0_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_list_of_port_connections_prev1_h1 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_NAMED_PORT_CONNECTION) {
      writer_sv_named_port_connection(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_port_connections_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_NAMED_PORT_CONNECTION) {
      writer_sv_named_port_connection(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LIST_OF_PORT_CONNECTIONS_PREV1_H1) {
      writer_sv_list_of_port_connections_prev1_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_ordered_port_connection (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_named_port_connection (string &out, NODE *node) {
   out.append(" .");
   if (node -> id == G_SV_PORT_IDENTIFIER) {
      writer_sv_port_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_generate_region (string &out, NODE *node) {
   out.append(" generate");
   while (node -> id == G_SV_GENERATE_ITEM) {
      writer_sv_generate_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" endgenerate");
}
void writer_sv_loop_generate_construct (string &out, NODE *node) {
   out.append(" for");
   out.append(" (");if (node -> id == G_SV_GENVAR_INITIALIZATION) { writer_sv_genvar_initialization(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ;");if (node -> id == G_SV_GENVAR_EXPRESSION) { writer_sv_genvar_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ;");if (node -> id == G_SV_GENVAR_ITERATION) { writer_sv_genvar_iteration(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_SV_GENERATE_BLOCK) {
      writer_sv_generate_block(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_genvar_initialization (string &out, NODE *node) {
   if (node -> id == G_SV_GENVAR_IDENTIFIER) {
      writer_sv_genvar_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" =");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_genvar_iteration (string &out, NODE *node) {
   if (node -> id == G_SV_GENVAR_ITERATION_ASSIGNMENT) {
      writer_sv_genvar_iteration_assignment(out, node -> sub);
      return; }
   if (node -> id == G_SV_GENVAR_ITERATION_INC_OR_DEC) {
      writer_sv_genvar_iteration_inc_or_dec(out, node -> sub);
      return; }
}
void writer_sv_genvar_iteration_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_GENVAR_IDENTIFIER) {
      writer_sv_genvar_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR) {
      writer_sv_assignment_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_GENVAR_EXPRESSION) {
      writer_sv_genvar_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_genvar_iteration_inc_or_dec (string &out, NODE *node) {
   if (node -> id == G_SV_GENVAR_IDENTIFIER) {
      writer_sv_genvar_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_INC_OR_DEC_OPERATOR) {
      writer_inc_or_dec_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_conditional_generate_construct (string &out, NODE *node) {
   if (node -> id == G_SV_IF_GENERATE_CONSTRUCT) {
      writer_sv_if_generate_construct(out, node -> sub);
      return; }
   if (node -> id == G_SV_CASE_GENERATE_CONSTRUCT) {
      writer_sv_case_generate_construct(out, node -> sub);
      return; }
}
void writer_sv_if_generate_construct (string &out, NODE *node) {
   if (node -> id == G_SV_IF_GENERATE_CONSTRUCT_PREV0) {
      writer_sv_if_generate_construct_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_IF_GENERATE_CONSTRUCT_PREV1) {
      writer_sv_if_generate_construct_prev1(out, node -> sub);
      return; }
   if (node -> id == G_SV_IF_GENERATE_CONSTRUCT_PREV2) {
      writer_sv_if_generate_construct_prev2(out, node -> sub);
      return; }
}
void writer_sv_if_generate_construct_prev0 (string &out, NODE *node) {
   out.append(" if");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_SV_GENERATE_BLOCK) {
      writer_sv_generate_block(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" else");
   if (node -> id == G_SV_IF_GENERATE_CONSTRUCT) {
      writer_sv_if_generate_construct(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_if_generate_construct_prev1 (string &out, NODE *node) {
   out.append(" if");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_SV_GENERATE_BLOCK) {
      writer_sv_generate_block(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" else");
   if (node -> id == G_SV_GENERATE_BLOCK) {
      writer_sv_generate_block(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_if_generate_construct_prev2 (string &out, NODE *node) {
   out.append(" if");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_SV_GENERATE_BLOCK) {
      writer_sv_generate_block(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_case_generate_construct (string &out, NODE *node) {
   out.append(" case");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   while (node -> id == G_SV_CASE_GENERATE_ITEM) {
      writer_sv_case_generate_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" endcase");
}
void writer_sv_case_generate_item (string &out, NODE *node) {
   if (node -> id == G_SV_CASE_GENERATE_ITEM_DEFAULT_NULL) {
      writer_sv_case_generate_item_default_null(out, node -> sub);
      return; }
   if (node -> id == G_SV_CASE_GENERATE_ITEM_DEFAULT) {
      writer_sv_case_generate_item_default(out, node -> sub);
      return; }
   if (node -> id == G_SV_CASE_GENERATE_ITEM_SPECIFIC) {
      writer_sv_case_generate_item_specific(out, node -> sub);
      return; }
}
void writer_sv_case_generate_item_specific (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_SV_GENERATE_BLOCK) {
      writer_sv_generate_block(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_case_generate_item_default_null (string &out, NODE *node) {
   out.append(" default");
   out.append(" :");
   out.append(" ;");
}
void writer_sv_case_generate_item_default (string &out, NODE *node) {
   out.append(" default");
   out.append(" :");
   if (node -> id == G_SV_GENERATE_BLOCK) {
      writer_sv_generate_block(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_generate_block (string &out, NODE *node) {
   if (node -> id == G_SV_GENERATE_BLOCK_SEQ) {
      writer_sv_generate_block_seq(out, node -> sub);
      return; }
   if (node -> id == G_SV_GENERATE_BLOCK_SINGLE) {
      writer_sv_generate_block_single(out, node -> sub);
      return; }
}
void writer_sv_generate_block_seq (string &out, NODE *node) {
   out.append(" begin");
   while (node -> id == G_SV_GENERATE_ITEM) {
      writer_sv_generate_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" end");
}
void writer_sv_generate_block_single (string &out, NODE *node) {
   if (node -> id == G_SV_GENERATE_ITEM) {
      writer_sv_generate_item(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_generate_item (string &out, NODE *node) {
   if (node -> id == G_SV_MODULE_OR_GENERATE_ITEM) {
      writer_sv_module_or_generate_item(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_continuous_assign (string &out, NODE *node) {
   if (node -> id == G_SV_ASSIGN_LIST_OF_VARIABLE_ASSIGNMENTS) {
      writer_sv_assign_list_of_variable_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_assign_list_of_variable_assignments (string &out, NODE *node) {
   out.append(" assign");
   if (node -> id == G_SV_LIST_OF_VARIABLE_ASSIGNMENTS) {
      writer_sv_list_of_variable_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_list_of_variable_assignments_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_VARIABLE_ASSIGNMENT) {
      writer_sv_variable_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_variable_assignments (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_ASSIGNMENT) {
      writer_sv_variable_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LIST_OF_VARIABLE_ASSIGNMENTS_H0) {
      writer_sv_list_of_variable_assignments_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_always_construct (string &out, NODE *node) {
   if (node -> id == G_SV_ALWAYS_KEYWORD) {
      writer_sv_always_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_STATEMENT) {
      writer_sv_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_always_keyword (string &out, NODE *node) {
   if (node -> id == G_SV_ALWAYS_COMB_IDENTIFIER) {
      writer_sv_always_comb_identifier(out, node -> sub);
      return; }
   if (node -> id == G_SV_ALWAYS_LATCH_IDENTIFIER) {
      writer_sv_always_latch_identifier(out, node -> sub);
      return; }
   if (node -> id == G_SV_ALWAYS_FF_IDENTIFIER) {
      writer_sv_always_ff_identifier(out, node -> sub);
      return; }
   if (node -> id == G_SV_ALWAYS_IDENTIFIER) {
      writer_sv_always_identifier(out, node -> sub);
      return; }
}
void writer_sv_always_identifier (string &out, NODE *node) {
   out.append(" always");
}
void writer_sv_always_comb_identifier (string &out, NODE *node) {
   out.append(" always_comb");
}
void writer_sv_always_latch_identifier (string &out, NODE *node) {
   out.append(" always_latch");
}
void writer_sv_always_ff_identifier (string &out, NODE *node) {
   out.append(" always_ff");
}
void writer_sv_blocking_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_LVALUE) {
      writer_sv_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BLOCKING_ASSIGN_EXPRESSION) {
      writer_sv_blocking_assign_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_blocking_assign_expression_h0 (string &out, NODE *node) {
   out.append(" ((");if (node -> id == G_SI) { writer_si(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ))");
}
void writer_sv_blocking_assign_expression (string &out, NODE *node) {
   out.append(" =");
   if (node -> id == G_SV_BLOCKING_ASSIGN_EXPRESSION_H0) {
      writer_sv_blocking_assign_expression_h0(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_operator_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_LVALUE) {
      writer_sv_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR) {
      writer_sv_assignment_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_assignment_operator (string &out, NODE *node) {
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_ASSIGN) {
      writer_sv_assignment_operator_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_PLUS_ASSIGN) {
      writer_sv_assignment_operator_plus_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_MINUS_ASSIGN) {
      writer_sv_assignment_operator_minus_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_MUL_ASSIGN) {
      writer_sv_assignment_operator_mul_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_NOT_ASSIGN) {
      writer_sv_assignment_operator_not_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_MOD_ASSIGN) {
      writer_sv_assignment_operator_mod_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_AND_ASSIGN) {
      writer_sv_assignment_operator_and_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_OR_ASSIGN) {
      writer_sv_assignment_operator_or_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_XOR_ASSIGN) {
      writer_sv_assignment_operator_xor_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_SHR2_ASSIGN) {
      writer_sv_assignment_operator_shr2_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_SHR3_ASSIGN) {
      writer_sv_assignment_operator_shr3_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_SHL2_ASSIGN) {
      writer_sv_assignment_operator_shl2_assign(out, node -> sub);
      return; }
   if (node -> id == G_SV_ASSIGNMENT_OPERATOR_SHL3_ASSIGN) {
      writer_sv_assignment_operator_shl3_assign(out, node -> sub);
      return; }
}
void writer_sv_assignment_operator_assign (string &out, NODE *node) {
   out.append(" =");
}
void writer_sv_assignment_operator_plus_assign (string &out, NODE *node) {
   out.append(" +=");
}
void writer_sv_assignment_operator_minus_assign (string &out, NODE *node) {
   out.append(" -=");
}
void writer_sv_assignment_operator_mul_assign (string &out, NODE *node) {
   out.append(" *=");
}
void writer_sv_assignment_operator_not_assign (string &out, NODE *node) {
   out.append(" /=");
}
void writer_sv_assignment_operator_mod_assign (string &out, NODE *node) {
   out.append(" %=");
}
void writer_sv_assignment_operator_and_assign (string &out, NODE *node) {
   out.append(" &=");
}
void writer_sv_assignment_operator_or_assign (string &out, NODE *node) {
   out.append(" |=");
}
void writer_sv_assignment_operator_xor_assign (string &out, NODE *node) {
   out.append(" ^");
   out.append(" =");
}
void writer_sv_assignment_operator_shr2_assign (string &out, NODE *node) {
   out.append(" <<=");
}
void writer_sv_assignment_operator_shr3_assign (string &out, NODE *node) {
   out.append(" <<<=");
}
void writer_sv_assignment_operator_shl2_assign (string &out, NODE *node) {
   out.append(" >>=");
}
void writer_sv_assignment_operator_shl3_assign (string &out, NODE *node) {
   out.append(" >>>=");
}
void writer_sv_nonblocking_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_LVALUE) {
      writer_sv_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_NONBLOCKING_ASSIGN_EXPRESSION) {
      writer_sv_nonblocking_assign_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_nonblocking_assign_expression (string &out, NODE *node) {
   out.append(" <=");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_variable_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_LVALUE) {
      writer_sv_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BLOCKING_ASSIGN_EXPRESSION) {
      writer_sv_blocking_assign_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_seq_block_h0 (string &out, NODE *node) {
   out.append(" :");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_seq_block_h1 (string &out, NODE *node) {
   out.append(" :");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_seq_block (string &out, NODE *node) {
   out.append(" begin");
   if (node -> id == G_SV_SEQ_BLOCK_H0) {
      writer_sv_seq_block_h0(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" end");
   if (node -> id == G_SV_SEQ_BLOCK_H1) {
      writer_sv_seq_block_h1(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_statement_or_null (string &out, NODE *node) {
   if (node -> id == G_SV_STATEMENT) {
      writer_sv_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_NULL_STATEMENT) {
      writer_sv_null_statement(out, node -> sub);
      return; }
}
void writer_sv_null_statement (string &out, NODE *node) {
   out.append(" ;");
}
void writer_sv_statement (string &out, NODE *node) {
   if (node -> id == G_SV_STATEMENT_ITEM) {
      writer_sv_statement_item(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_statement_item (string &out, NODE *node) {
   if (node -> id == G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT) {
      writer_sv_statement_item_blocking_assignment(out, node -> sub);
      return; }
   if (node -> id == G_SV_STATEMENT_ITEM_NONBLOCKING_ASSIGNMENT) {
      writer_sv_statement_item_nonblocking_assignment(out, node -> sub);
      return; }
   if (node -> id == G_SV_CASE_STATEMENT) {
      writer_sv_case_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONDITIONAL_STATEMENT) {
      writer_sv_conditional_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_SUBROUTINE_CALL_STATEMENT) {
      writer_sv_subroutine_call_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_LOOP_STATEMENT) {
      writer_sv_loop_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_PROCEDURAL_TIMING_CONTROL_STATEMENT) {
      writer_sv_procedural_timing_control_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_SEQ_BLOCK) {
      writer_sv_seq_block(out, node -> sub);
      return; }
}
void writer_sv_statement_item_blocking_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_BLOCKING_ASSIGNMENT) {
      writer_sv_blocking_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_statement_item_nonblocking_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_NONBLOCKING_ASSIGNMENT) {
      writer_sv_nonblocking_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_procedural_timing_control_statement (string &out, NODE *node) {
   if (node -> id == G_SV_PROCEDURAL_TIMING_CONTROL) {
      writer_sv_procedural_timing_control(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_delay_control (string &out, NODE *node) {
   size_t pos = out.length() + 1;

   if (node -> id == G_SV_SI_DELAY_CONTROL) {
      writer_sv_si_delay_control(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   writer_clear_space(out, pos);
}
void writer_sv_si_delay_control (string &out, NODE *node) {
   out.append(" #");
   if (node -> id == G_SV_DELAY_VALUE) {
      writer_sv_delay_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_event_control (string &out, NODE *node) {
   if (node -> id == G_SV_EVENT_CONTROL_EVENT_EXPRESSION) {
      writer_sv_event_control_event_expression(out, node -> sub);
      return; }
   if (node -> id == G_SV_EVENT_CONTROL_ASTERISK) {
      writer_sv_event_control_asterisk(out, node -> sub);
      return; }
}
void writer_sv_event_control_event_expression (string &out, NODE *node) {
   out.append(" @");
   out.append(" (");if (node -> id == G_SV_EVENT_EXPRESSION) { writer_sv_event_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_event_control_asterisk (string &out, NODE *node) {
   out.append(" @");
   out.append(" (");out.append(" *");out.append(" )");
}
void writer_sv_event_expression (string &out, NODE *node) {
   if (node -> id == G_SV_EVENT_EXPRESSION_PREV0) {
      writer_sv_event_expression_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_EVENT_EXPRESSION_PREV1) {
      writer_sv_event_expression_prev1(out, node -> sub);
      return; }
   if (node -> id == G_SV_EVENT_EXPRESSION_PREV2) {
      writer_sv_event_expression_prev2(out, node -> sub);
      return; }
   if (node -> id == G_SV_EVENT_EXPRESSION_PREV3) {
      writer_sv_event_expression_prev3(out, node -> sub);
      return; }
   if (node -> id == G_SV_EVENT_EXPRESSION_PREV4) {
      writer_sv_event_expression_prev4(out, node -> sub);
      return; }
}
void writer_sv_event_expression_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_EDGE_IDENTIFIER) {
      writer_sv_edge_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" or");
   if (node -> id == G_SV_EVENT_EXPRESSION) {
      writer_sv_event_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_event_expression_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_EDGE_IDENTIFIER) {
      writer_sv_edge_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_event_expression_prev2 (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SV_EVENT_EXPRESSION) { writer_sv_event_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_event_expression_prev3 (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" or");
   if (node -> id == G_SV_EVENT_EXPRESSION) {
      writer_sv_event_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_event_expression_prev4_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_event_expression_prev4 (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_EVENT_EXPRESSION_PREV4_H0) {
      writer_sv_event_expression_prev4_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_edge_identifier (string &out, NODE *node) {
   if (node -> id == G_SV_POSEDGE_IDENTIFIER) {
      writer_sv_posedge_identifier(out, node -> sub);
      return; }
   if (node -> id == G_SV_NEGEDGE_IDENTIFIER) {
      writer_sv_negedge_identifier(out, node -> sub);
      return; }
}
void writer_sv_posedge_identifier (string &out, NODE *node) {
   out.append(" posedge");
}
void writer_sv_negedge_identifier (string &out, NODE *node) {
   out.append(" negedge");
}
void writer_sv_procedural_timing_control (string &out, NODE *node) {
   if (node -> id == G_SV_DELAY_CONTROL) {
      writer_sv_delay_control(out, node -> sub);
      return; }
   if (node -> id == G_SV_EVENT_CONTROL) {
      writer_sv_event_control(out, node -> sub);
      return; }
}
void writer_sv_conditional_statement (string &out, NODE *node) {
   if (node -> id == G_SV_IF_ELSE_CONDITIONAL_STATEMENT) {
      writer_sv_if_else_conditional_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_IF_CONDITIONAL_STATEMENT) {
      writer_sv_if_conditional_statement(out, node -> sub);
      return; }
}
void writer_sv_if_else_conditional_statement (string &out, NODE *node) {
   if (node -> id == G_SV_UNIQUE_PRIORITY) {
      writer_sv_unique_priority(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" if");
   if (node -> id == G_SV_COND_PREDICATE) {
      writer_sv_cond_predicate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" else");
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_if_conditional_statement (string &out, NODE *node) {
   if (node -> id == G_SV_UNIQUE_PRIORITY) {
      writer_sv_unique_priority(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" if");
   if (node -> id == G_SV_COND_PREDICATE) {
      writer_sv_cond_predicate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_unique_priority (string &out, NODE *node) {
   if (node -> id == G_SV_UNIQUE_PRIORITY_UNIQUE) {
      writer_sv_unique_priority_unique(out, node -> sub);
      return; }
   if (node -> id == G_SV_UNIQUE_PRIORITY_UNIQUE0) {
      writer_sv_unique_priority_unique0(out, node -> sub);
      return; }
   if (node -> id == G_SV_UNIQUE_PRIORITY_PRIORITY) {
      writer_sv_unique_priority_priority(out, node -> sub);
      return; }
}
void writer_sv_unique_priority_unique (string &out, NODE *node) {
   out.append(" unique");
}
void writer_sv_unique_priority_unique0 (string &out, NODE *node) {
   out.append(" unique0");
}
void writer_sv_unique_priority_priority (string &out, NODE *node) {
   out.append(" priority");
}
void writer_sv_cond_predicate (string &out, NODE *node) {
   if (node -> id == G_SV_BRACKET_EXPRESSION) {
      writer_sv_bracket_expression(out, node -> sub);
      return; }
   if (node -> id == G_SV_UNARY_PRIMARY) {
      writer_sv_unary_primary(out, node -> sub);
      return; }
   if (node -> id == G_SV_PRIMARY) {
      writer_sv_primary(out, node -> sub);
      return; }
}
void writer_sv_case_statement (string &out, NODE *node) {
   if (node -> id == G_SV_UNIQUE_PRIORITY) {
      writer_sv_unique_priority(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_CASE_KEYWORD) {
      writer_sv_case_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_CASE_EXPRESSION) { writer_sv_case_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   while (node -> id == G_SV_CASE_ITEM) {
      writer_sv_case_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" endcase");
}
void writer_sv_case_keyword (string &out, NODE *node) {
   if (node -> id == G_SV_CASE_KEYWORD_CASEZ) {
      writer_sv_case_keyword_casez(out, node -> sub);
      return; }
   if (node -> id == G_SV_CASE_KEYWORD_CASEX) {
      writer_sv_case_keyword_casex(out, node -> sub);
      return; }
   if (node -> id == G_SV_CASE_KEYWORD_CASE) {
      writer_sv_case_keyword_case(out, node -> sub);
      return; }
}
void writer_sv_case_keyword_case (string &out, NODE *node) {
   out.append(" case");
}
void writer_sv_case_keyword_casez (string &out, NODE *node) {
   out.append(" casez");
}
void writer_sv_case_keyword_casex (string &out, NODE *node) {
   out.append(" casex");
}
void writer_sv_case_expression (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_case_item (string &out, NODE *node) {
   if (node -> id == G_SV_CASE_DEFAULT_ITEM) {
      writer_sv_case_default_item(out, node -> sub);
      return; }
   if (node -> id == G_SV_CASE_EXPRESSION_ITEM) {
      writer_sv_case_expression_item(out, node -> sub);
      return; }
}
void writer_sv_case_default_item (string &out, NODE *node) {
   out.append(" default");
   out.append(" :");
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_case_expression_item (string &out, NODE *node) {
   if (node -> id == G_SV_CASE_ITEM_EXPRESSION) {
      writer_sv_case_item_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_case_item_expression (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_loop_statement (string &out, NODE *node) {
   if (node -> id == G_SV_LOOP_REPEAT_STATEMENT) {
      writer_sv_loop_repeat_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_LOOP_WHILE_STATEMENT) {
      writer_sv_loop_while_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_LOOP_DO_STATEMENT) {
      writer_sv_loop_do_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_LOOP_FOREACH_STATEMENT) {
      writer_sv_loop_foreach_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_LOOP_FOR_STATEMENT) {
      writer_sv_loop_for_statement(out, node -> sub);
      return; }
}
void writer_sv_loop_repeat_statement (string &out, NODE *node) {
   out.append(" repeat");
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_loop_while_statement (string &out, NODE *node) {
   out.append(" while");
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_loop_do_statement (string &out, NODE *node) {
   out.append(" do");
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" while");
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   out.append(" ;");
}
void writer_sv_loop_foreach_statement (string &out, NODE *node) {
   out.append(" foreach");
   out.append(" (");if (node -> id == G_SV_PS_OR_HIERARCHICAL_ARRAY_IDENTIFIER) { writer_sv_ps_or_hierarchical_array_identifier(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" [");if (node -> id == G_SV_LOOP_VARIABLES) { writer_sv_loop_variables(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ]");out.append(" )");
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_loop_for_statement (string &out, NODE *node) {
   out.append(" for");
   out.append(" (");if (node -> id == G_SV_FOR_INITIALIZATION) { writer_sv_for_initialization(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ;");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ;");if (node -> id == G_SV_FOR_STEP) { writer_sv_for_step(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_SV_STATEMENT_OR_NULL) {
      writer_sv_statement_or_null(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_for_initialization (string &out, NODE *node) {
   if (node -> id == G_SV_LIST_OF_VARIABLE_ASSIGNMENTS) {
      writer_sv_list_of_variable_assignments(out, node -> sub);
      return; }
   if (node -> id == G_SV_INTEGER_VARIABLE_ASSIGNMENT) {
      writer_sv_integer_variable_assignment(out, node -> sub);
      return; }
   if (node -> id == G_SV_LIST_OF_VARIABLE_DECLARATIONS) {
      writer_sv_list_of_variable_declarations(out, node -> sub);
      return; }
}
void writer_sv_integer_variable_assignment (string &out, NODE *node) {
   out.append(" integer");
   if (node -> id == G_SV_VARIABLE_ASSIGNMENT) {
      writer_sv_variable_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_variable_declarations_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_FOR_VARIABLE_DECLARATION) {
      writer_sv_for_variable_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_variable_declarations (string &out, NODE *node) {
   if (node -> id == G_SV_FOR_VARIABLE_DECLARATION) {
      writer_sv_for_variable_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LIST_OF_VARIABLE_DECLARATIONS_H0) {
      writer_sv_list_of_variable_declarations_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_for_variable_declaration (string &out, NODE *node) {
   out.append(" int");
   if (node -> id == G_SV_VARIABLE_IDENTIFIER) {
      writer_sv_variable_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" =");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_for_step (string &out, NODE *node) {
   if (node -> id == G_SV_FOR_STEP_ASSIGNMENT) {
      writer_sv_for_step_assignment(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_for_step_assignment (string &out, NODE *node) {
   if (node -> id == G_SV_LIST_OF_VARIABLE_ASSIGNMENTS) {
      writer_sv_list_of_variable_assignments(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_loop_variables_h1 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_INDEX_VARIABLE_IDENTIFIER) {
      writer_sv_index_variable_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_loop_variables (string &out, NODE *node) {
   if (node -> id == G_SV_INDEX_VARIABLE_IDENTIFIER) {
      writer_sv_index_variable_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_LOOP_VARIABLES_H1) {
      writer_sv_loop_variables_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_subroutine_call_statement (string &out, NODE *node) {
   if (node -> id == G_SV_TF_CALL) {
      writer_sv_tf_call(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_sv_concatenation (string &out, NODE *node) {
   out.append(" {");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_EXPRESSION_LIST) {
      writer_sv_expression_list(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_sv_expression_list (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_concatenation (string &out, NODE *node) {
   out.append(" {");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_CONSTANT_EXPRESSION_LIST) {
      writer_sv_constant_expression_list(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_sv_constant_expression_list (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_multiple_concatenation (string &out, NODE *node) {
   out.append(" {");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_CONCATENATION) {
      writer_sv_concatenation(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" }");
}
void writer_sv_constant_function_call (string &out, NODE *node) {
   if (node -> id == G_SV_FUNCTION_SUBROUTINE_CALL) {
      writer_sv_function_subroutine_call(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_tf_call (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_LIST_OF_ARGUMENTS) { writer_sv_list_of_arguments(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_system_tf_call (string &out, NODE *node) {
   if (node -> id == G_SYSTEM_SI) {
      writer_system_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SV_LIST_OF_ARGUMENTS) { writer_sv_list_of_arguments(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_subroutine_call (string &out, NODE *node) {
   if (node -> id == G_SV_TF_CALL) {
      writer_sv_tf_call(out, node -> sub);
      return; }
   if (node -> id == G_SV_SYSTEM_TF_CALL) {
      writer_sv_system_tf_call(out, node -> sub);
      return; }
}
void writer_sv_function_subroutine_call (string &out, NODE *node) {
   if (node -> id == G_SV_SUBROUTINE_CALL) {
      writer_sv_subroutine_call(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_list_of_arguments (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_EXPRESSION_LIST) {
      writer_sv_expression_list(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_inc_or_dec_expression (string &out, NODE *node) {
   if (node -> id == G_SV_INC_OR_DEC_EXPRESSION_PREV0) {
      writer_sv_inc_or_dec_expression_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_INC_OR_DEC_EXPRESSION_PREV1) {
      writer_sv_inc_or_dec_expression_prev1(out, node -> sub);
      return; }
}
void writer_sv_inc_or_dec_expression_prev0 (string &out, NODE *node) {
   if (node -> id == G_INC_OR_DEC_OPERATOR) {
      writer_inc_or_dec_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_VARIABLE_LVALUE) {
      writer_sv_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_inc_or_dec_expression_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_LVALUE) {
      writer_sv_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_INC_OR_DEC_OPERATOR) {
      writer_inc_or_dec_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_conditional_expression (string &out, NODE *node) {
   if (node -> id == G_SV_COND_PREDICATE) {
      writer_sv_cond_predicate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ?");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_expression (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION_BINARY) {
      writer_sv_constant_expression_binary(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONSTANT_TRINARY_EXPRESSION) {
      writer_sv_constant_trinary_expression(out, node -> sub);
      return; }
   if (node -> id == G_SV_UNARY_CONSTANT_PRIMARY) {
      writer_sv_unary_constant_primary(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONSTANT_PRIMARY) {
      writer_sv_constant_primary(out, node -> sub);
      return; }
}
void writer_sv_constant_expression_binary (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION_BINARY_PRIMARY) {
      writer_sv_constant_expression_binary_primary(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONSTANT_EXPRESSION_BINARY_UNARY) {
      writer_sv_constant_expression_binary_unary(out, node -> sub);
      return; }
}
void writer_sv_constant_expression_binary_primary (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_PRIMARY) {
      writer_sv_constant_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_OPERATOR) {
      writer_sv_binary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_expression_binary_unary (string &out, NODE *node) {
   if (node -> id == G_SV_UNARY_CONSTANT_PRIMARY) {
      writer_sv_unary_constant_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_OPERATOR) {
      writer_sv_binary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_unary_constant_primary (string &out, NODE *node) {
   if (node -> id == G_SV_UNARY_OPERATOR) {
      writer_sv_unary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_CONSTANT_PRIMARY) {
      writer_sv_constant_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_trinary_expression (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_PRIMARY) {
      writer_sv_constant_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_TRINARY_OPERATOR) {
      writer_sv_trinary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_trinary_operator (string &out, NODE *node) {
   if (node -> id == G_SV_OPERATOR_CONDITIONAL) {
      writer_sv_operator_conditional(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_operator_conditional (string &out, NODE *node) {
   out.append(" ?");
}
void writer_sv_constant_bracket_mintypmax_expression (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SV_CONSTANT_MINTYPMAX_EXPRESSION) { writer_sv_constant_mintypmax_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_constant_mintypmax_expression (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_param_expression (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_part_select_range (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_RANGE) {
      writer_sv_constant_range(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_range (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_expression (string &out, NODE *node) {
   if (node -> id == G_SV_CONDITIONAL_EXPRESSION) {
      writer_sv_conditional_expression(out, node -> sub);
      return; }
   if (node -> id == G_SV_EXPRESSION_BINARY) {
      writer_sv_expression_binary(out, node -> sub);
      return; }
   if (node -> id == G_SV_UNARY_PRIMARY) {
      writer_sv_unary_primary(out, node -> sub);
      return; }
   if (node -> id == G_SV_INC_OR_DEC_EXPRESSION) {
      writer_sv_inc_or_dec_expression(out, node -> sub);
      return; }
   if (node -> id == G_SV_PRIMARY) {
      writer_sv_primary(out, node -> sub);
      return; }
}
void writer_sv_bracket_expression (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_expression_binary (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION_BINARY_PRIMARY) {
      writer_sv_expression_binary_primary(out, node -> sub);
      return; }
   if (node -> id == G_SV_EXPRESSION_BINARY_UNARY) {
      writer_sv_expression_binary_unary(out, node -> sub);
      return; }
}
void writer_sv_expression_binary_primary (string &out, NODE *node) {
   if (node -> id == G_SV_PRIMARY) {
      writer_sv_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_OPERATOR) {
      writer_sv_binary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_expression_binary_unary (string &out, NODE *node) {
   if (node -> id == G_SV_UNARY_PRIMARY) {
      writer_sv_unary_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_OPERATOR) {
      writer_sv_binary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_unary_primary (string &out, NODE *node) {
   if (node -> id == G_SV_UNARY_OPERATOR) {
      writer_sv_unary_operator(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PRIMARY) {
      writer_sv_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_mintypmax_expression (string &out, NODE *node) {
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_part_select_range (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_RANGE) {
      writer_sv_constant_range(out, node -> sub);
      return; }
   if (node -> id == G_SV_INDEXED_RANGE) {
      writer_sv_indexed_range(out, node -> sub);
      return; }
}
void writer_sv_indexed_range (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_PRIMARY) {
      writer_sv_constant_primary(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_genvar_expression (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_primary (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_CONCATENATION) {
      writer_sv_constant_concatenation(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONSTANT_FUNCTION_CALL) {
      writer_sv_constant_function_call(out, node -> sub);
      return; }
   if (node -> id == G_SV_PRIMARY_LITERAL) {
      writer_sv_primary_literal(out, node -> sub);
      return; }
   if (node -> id == G_SV_GENVAR_IDENTIFIER) {
      writer_sv_genvar_identifier(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONSTANT_BRACKET_MINTYPMAX_EXPRESSION) {
      writer_sv_constant_bracket_mintypmax_expression(out, node -> sub);
      return; }
}
void writer_sv_primary (string &out, NODE *node) {
   if (node -> id == G_SV_CONCATENATION) {
      writer_sv_concatenation(out, node -> sub);
      return; }
   if (node -> id == G_SV_MULTIPLE_CONCATENATION) {
      writer_sv_multiple_concatenation(out, node -> sub);
      return; }
   if (node -> id == G_SV_FUNCTION_SUBROUTINE_CALL) {
      writer_sv_function_subroutine_call(out, node -> sub);
      return; }
   if (node -> id == G_SV_BRACKET_MINTYPMAX_EXPRESSION) {
      writer_sv_bracket_mintypmax_expression(out, node -> sub);
      return; }
   if (node -> id == G_SV_HIERARCHICAL_IDENTIFIER_SELECT) {
      writer_sv_hierarchical_identifier_select(out, node -> sub);
      return; }
   if (node -> id == G_SV_PRIMARY_LITERAL) {
      writer_sv_primary_literal(out, node -> sub);
      return; }
}
void writer_sv_bracket_mintypmax_expression (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SV_MINTYPMAX_EXPRESSION) { writer_sv_mintypmax_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_sv_hierarchical_identifier_select (string &out, NODE *node) {
   if (node -> id == G_SV_HIERARCHICAL_IDENTIFIER) {
      writer_sv_hierarchical_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_SELECT) {
      writer_sv_select(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_primary_literal (string &out, NODE *node) {
   if (node -> id == G_SV_NUMBER) {
      writer_sv_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_bit_select (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_sv_select (string &out, NODE *node) {
   if (node -> id == G_SV_SELECT_RANGE) {
      writer_sv_select_range(out, node -> sub);
      return; }
   if (node -> id == G_SV_BIT_SELECT) {
      writer_sv_bit_select(out, node -> sub);
      return; }
}
void writer_sv_select_range (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_PART_SELECT_RANGE) {
      writer_sv_part_select_range(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_sv_constant_bit_select_list (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_BIT_SELECT) {
      writer_sv_constant_bit_select(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_CONSTANT_BIT_SELECT_LIST) {
      writer_sv_constant_bit_select_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_constant_bit_select (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_sv_constant_select_h0 (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_CONSTANT_PART_SELECT_RANGE) {
      writer_sv_constant_part_select_range(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_sv_constant_select (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_BIT_SELECT) {
      writer_sv_constant_bit_select(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_CONSTANT_SELECT_H0) {
      writer_sv_constant_select_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_variable_lvalue (string &out, NODE *node) {
   if (node -> id == G_SV_VARIABLE_SINGLE_LVALUE) {
      writer_sv_variable_single_lvalue(out, node -> sub);
      return; }
   if (node -> id == G_SV_VARIABLE_CONCAT_LVALUE) {
      writer_sv_variable_concat_lvalue(out, node -> sub);
      return; }
}
void writer_sv_variable_single_lvalue (string &out, NODE *node) {
   if (node -> id == G_SV_HIERARCHICAL_VARIABLE_IDENTIFIER) {
      writer_sv_hierarchical_variable_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_SELECT) {
      writer_sv_select(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_variable_concat_lvalue (string &out, NODE *node) {
   out.append(" {");
   if (node -> id == G_SV_VARIABLE_LVALUE) {
      writer_sv_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_VARIABLE_LVALUE_LIST) {
      writer_sv_variable_lvalue_list(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_sv_variable_lvalue_list (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_VARIABLE_LVALUE) {
      writer_sv_variable_lvalue(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_unary_operator (string &out, NODE *node) {
   if (node -> id == G_OPERATOR_PLUS) {
      writer_operator_plus(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_MINUS) {
      writer_operator_minus(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_NAND) {
      writer_operator_nand(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_NOR) {
      writer_operator_nor(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_NXOR) {
      writer_operator_nxor(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_EXCLAMATION) {
      writer_operator_exclamation(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_TILDE) {
      writer_operator_tilde(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_AND) {
      writer_operator_and(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_OR) {
      writer_operator_or(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_XOR) {
      writer_operator_xor(out, node -> sub);
      return; }
}
void writer_operator_exclamation (string &out, NODE *node) {
   out.append(" !");
}
void writer_operator_tilde (string &out, NODE *node) {
   out.append(" ~");
}
void writer_sv_binary_operator (string &out, NODE *node) {
   if (node -> id == G_OPERATOR_PLUS) {
      writer_operator_plus(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_MINUS) {
      writer_operator_minus(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_POW) {
      writer_operator_pow(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_MUL) {
      writer_operator_mul(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_ASR) {
      writer_operator_asr(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_ASL) {
      writer_operator_asl(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_LSR) {
      writer_operator_lsr(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_LSL) {
      writer_operator_lsl(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_DIV) {
      writer_operator_div(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_MOD) {
      writer_operator_mod(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_CASE_EQUAL) {
      writer_operator_case_equal(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_CASE_INEQUAL) {
      writer_operator_case_inequal(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_WILDCARD_EQUAL) {
      writer_operator_wildcard_equal(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_WILDCARD_INEQUAL) {
      writer_operator_wildcard_inequal(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_LOGICAL_EQUAL) {
      writer_operator_logical_equal(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_LOGICAL_INEQUAL) {
      writer_operator_logical_inequal(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_LESSER_EQUAL) {
      writer_operator_lesser_equal(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_GREATER_EQUAL) {
      writer_operator_greater_equal(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_LAND) {
      writer_operator_land(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_AND) {
      writer_operator_and(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_LOR) {
      writer_operator_lor(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_OR) {
      writer_operator_or(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_NXOR) {
      writer_operator_nxor(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_XOR) {
      writer_operator_xor(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_LESSER) {
      writer_operator_lesser(out, node -> sub);
      return; }
   if (node -> id == G_OPERATOR_GREATER) {
      writer_operator_greater(out, node -> sub);
      return; }
}
void writer_operator_plus (string &out, NODE *node) {
   out.append(" +");
}
void writer_operator_minus (string &out, NODE *node) {
   out.append(" -");
}
void writer_operator_pow (string &out, NODE *node) {
   out.append(" **");
}
void writer_operator_mul (string &out, NODE *node) {
   out.append(" *");
}
void writer_operator_div (string &out, NODE *node) {
   out.append(" /");
}
void writer_operator_mod (string &out, NODE *node) {
   out.append(" %");
}
void writer_operator_logical_equal (string &out, NODE *node) {
   out.append(" ==");
}
void writer_operator_logical_inequal (string &out, NODE *node) {
   out.append(" !=");
}
void writer_operator_case_equal (string &out, NODE *node) {
   out.append(" ===");
}
void writer_operator_case_inequal (string &out, NODE *node) {
   out.append(" !==");
}
void writer_operator_wildcard_equal (string &out, NODE *node) {
   out.append(" ==?");
}
void writer_operator_wildcard_inequal (string &out, NODE *node) {
   out.append(" !=?");
}
void writer_operator_lesser_equal (string &out, NODE *node) {
   out.append(" <=");
}
void writer_operator_greater_equal (string &out, NODE *node) {
   out.append(" >=");
}
void writer_operator_land (string &out, NODE *node) {
   out.append(" &&");
}
void writer_operator_and (string &out, NODE *node) {
   out.append(" &");
}
void writer_operator_nand (string &out, NODE *node) {
   out.append(" ~&");
}
void writer_operator_lor (string &out, NODE *node) {
   out.append(" ||");
}
void writer_operator_or (string &out, NODE *node) {
   out.append(" |");
}
void writer_operator_nor (string &out, NODE *node) {
   out.append(" ~|");
}
void writer_operator_xor (string &out, NODE *node) {
   out.append(" ^");
}
void writer_operator_nxor (string &out, NODE *node) {
   out.append(" ~^");
}
void writer_operator_lsr (string &out, NODE *node) {
   out.append(" >>");
}
void writer_operator_lsl (string &out, NODE *node) {
   out.append(" <<");
}
void writer_operator_asr (string &out, NODE *node) {
   out.append(" >>>");
}
void writer_operator_asl (string &out, NODE *node) {
   out.append(" <<<");
}
void writer_operator_lesser (string &out, NODE *node) {
   out.append(" <");
}
void writer_operator_greater (string &out, NODE *node) {
   out.append(" >");
}
void writer_inc_or_dec_operator (string &out, NODE *node) {
   if (node -> id == G_INC_OPERATOR) {
      writer_inc_operator(out, node -> sub);
      return; }
   if (node -> id == G_DEC_OPERATOR) {
      writer_dec_operator(out, node -> sub);
      return; }
}
void writer_inc_operator (string &out, NODE *node) {
   out.append(" ++");
}
void writer_dec_operator (string &out, NODE *node) {
   out.append(" --");
}
void writer_sv_number (string &out, NODE *node) {
   size_t pos = out.length() + 1;

   if (node -> id == G_SV_INTEGRAL_NUMBER) {
      writer_sv_integral_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   writer_clear_space(out, pos);
}
void writer_sv_integral_number (string &out, NODE *node) {
   if (node -> id == G_SV_BINARY_NUMBER) {
      writer_sv_binary_number(out, node -> sub);
      return; }
   if (node -> id == G_SV_OCTAL_NUMBER) {
      writer_sv_octal_number(out, node -> sub);
      return; }
   if (node -> id == G_SV_HEX_NUMBER) {
      writer_sv_hex_number(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER) {
      writer_sv_decimal_number(out, node -> sub);
      return; }
}
void writer_sv_decimal_number (string &out, NODE *node) {
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV0) {
      writer_sv_decimal_number_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV1) {
      writer_sv_decimal_number_prev1(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV2) {
      writer_sv_decimal_number_prev2(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV3) {
      writer_sv_decimal_number_prev3(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV4) {
      writer_sv_decimal_number_prev4(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV5) {
      writer_sv_decimal_number_prev5(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV6) {
      writer_sv_decimal_number_prev6(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV7) {
      writer_sv_decimal_number_prev7(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_NUMBER_PREV8) {
      writer_sv_decimal_number_prev8(out, node -> sub);
      return; }
}
void writer_sv_decimal_number_prev0 (string &out, NODE *node) {
   if (node -> id == G_CPP_UNSIGNED_NUMBER) {
      writer_cpp_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_decimal_number_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_DECIMAL_BASE) {
      writer_sv_decimal_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_decimal_number_prev2 (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_DECIMAL_BASE) {
      writer_sv_decimal_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_X_DIGIT) {
      writer_x_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_decimal_number_prev3 (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_DECIMAL_BASE) {
      writer_sv_decimal_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_Z_DIGIT) {
      writer_z_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_decimal_number_prev4 (string &out, NODE *node) {
   if (node -> id == G_SV_DECIMAL_BASE) {
      writer_sv_decimal_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_decimal_number_prev5 (string &out, NODE *node) {
   if (node -> id == G_SV_DECIMAL_BASE) {
      writer_sv_decimal_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_X_DIGIT) {
      writer_x_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_decimal_number_prev6 (string &out, NODE *node) {
   if (node -> id == G_SV_DECIMAL_BASE) {
      writer_sv_decimal_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_Z_DIGIT) {
      writer_z_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_decimal_number_prev7 (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_decimal_number_prev8 (string &out, NODE *node) {
   if (node -> id == G_SV_ZERO_NUMBER) {
      writer_sv_zero_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_binary_number (string &out, NODE *node) {
   if (node -> id == G_SV_BINARY_NUMBER_PREV0) {
      writer_sv_binary_number_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_BINARY_NUMBER_PREV1) {
      writer_sv_binary_number_prev1(out, node -> sub);
      return; }
}
void writer_sv_binary_number_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_BASE) {
      writer_sv_binary_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_VALUE) {
      writer_sv_binary_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_binary_number_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_BINARY_BASE) {
      writer_sv_binary_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_VALUE) {
      writer_sv_binary_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_octal_number (string &out, NODE *node) {
   if (node -> id == G_SV_OCTAL_NUMBER_PREV0) {
      writer_sv_octal_number_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_OCTAL_NUMBER_PREV1) {
      writer_sv_octal_number_prev1(out, node -> sub);
      return; }
}
void writer_sv_octal_number_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_OCTAL_BASE) {
      writer_sv_octal_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_OCTAL_VALUE) {
      writer_sv_octal_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_octal_number_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_OCTAL_BASE) {
      writer_sv_octal_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_OCTAL_VALUE) {
      writer_sv_octal_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hex_number (string &out, NODE *node) {
   if (node -> id == G_SV_HEX_NUMBER_PREV0) {
      writer_sv_hex_number_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_HEX_NUMBER_PREV1) {
      writer_sv_hex_number_prev1(out, node -> sub);
      return; }
}
void writer_sv_hex_number_prev0 (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_HEX_BASE) {
      writer_sv_hex_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_HEX_VALUE) {
      writer_sv_hex_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hex_number_prev1 (string &out, NODE *node) {
   if (node -> id == G_SV_HEX_BASE) {
      writer_sv_hex_base(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_HEX_VALUE) {
      writer_sv_hex_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_cpp_unsigned_number_old (string &out, NODE *node) {
   out.append(" 0x");
   if (node -> id == G_SV_HEX_VALUE) {
      writer_sv_hex_value(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" U");
}
void writer_sv_unsigned_number (string &out, NODE *node) {
   if (node -> id == G_SV_UNSIGNED_NUMBER_PREV0) {
      writer_sv_unsigned_number_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_UNSIGNED_NUMBER_PREV1) {
      writer_sv_unsigned_number_prev1(out, node -> sub);
      return; }
}
void writer_sv_unsigned_number_prev0 (string &out, NODE *node) {
   if (node -> id == G_DECIMAL_DIGIT) {
      writer_decimal_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_unsigned_number_prev1 (string &out, NODE *node) {
   if (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_UNSIGNED_NUMBER) {
      writer_sv_unsigned_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_zero_number (string &out, NODE *node) {
   out.append(" '");
   if (node -> id == G_0_DIGIT) {
      writer_0_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_binary_value_digit (string &out, NODE *node) {
   if (node -> id == G_SV_BINARY_VALUE_DIGIT_PREV0) {
      writer_sv_binary_value_digit_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_BINARY_VALUE_DIGIT_PREV1) {
      writer_sv_binary_value_digit_prev1(out, node -> sub);
      return; }
}
void writer_sv_binary_value_digit_prev0 (string &out, NODE *node) {
   if (node -> id == G_BINARY_DIGIT) {
      writer_binary_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_VALUE_DIGIT) {
      writer_sv_binary_value_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_binary_value_digit_prev1 (string &out, NODE *node) {
   if (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BINARY_VALUE_DIGIT) {
      writer_sv_binary_value_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_binary_value (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_sv_octal_value_digit (string &out, NODE *node) {
   if (node -> id == G_SV_OCTAL_VALUE_DIGIT_PREV0) {
      writer_sv_octal_value_digit_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_OCTAL_VALUE_DIGIT_PREV1) {
      writer_sv_octal_value_digit_prev1(out, node -> sub);
      return; }
}
void writer_sv_octal_value_digit_prev0 (string &out, NODE *node) {
   if (node -> id == G_OCTAL_DIGIT) {
      writer_octal_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_OCTAL_VALUE_DIGIT) {
      writer_sv_octal_value_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_octal_value_digit_prev1 (string &out, NODE *node) {
   if (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_OCTAL_VALUE_DIGIT) {
      writer_sv_octal_value_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_octal_value (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_sv_hex_value_digit (string &out, NODE *node) {
   if (node -> id == G_SV_HEX_VALUE_DIGIT_PREV0) {
      writer_sv_hex_value_digit_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SV_HEX_VALUE_DIGIT_PREV1) {
      writer_sv_hex_value_digit_prev1(out, node -> sub);
      return; }
}
void writer_sv_hex_value_digit_prev0 (string &out, NODE *node) {
   if (node -> id == G_HEX_DIGIT) {
      writer_hex_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_HEX_VALUE_DIGIT) {
      writer_sv_hex_value_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hex_value_digit_prev1 (string &out, NODE *node) {
   if (node -> id == G_US_DIGIT) {
      writer_us_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_HEX_VALUE_DIGIT) {
      writer_sv_hex_value_digit(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hex_value (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_sv_decimal_base (string &out, NODE *node) {
   if (node -> id == G_SV_DECIMAL_UNSIGNED_BASE) {
      writer_sv_decimal_unsigned_base(out, node -> sub);
      return; }
   if (node -> id == G_SV_DECIMAL_SIGNED_BASE) {
      writer_sv_decimal_signed_base(out, node -> sub);
      return; }
}
void writer_sv_decimal_unsigned_base (string &out, NODE *node) {
   out.append(" '");
   out.append(" d");
}
void writer_sv_decimal_signed_base (string &out, NODE *node) {
   out.append(" '");
   out.append(" s");
   out.append(" d");
}
void writer_sv_binary_base (string &out, NODE *node) {
   if (node -> id == G_SV_BINARY_UNSIGNED_BASE) {
      writer_sv_binary_unsigned_base(out, node -> sub);
      return; }
   if (node -> id == G_SV_BINARY_SIGNED_BASE) {
      writer_sv_binary_signed_base(out, node -> sub);
      return; }
}
void writer_sv_binary_unsigned_base (string &out, NODE *node) {
   out.append(" '");
   out.append(" b");
}
void writer_sv_binary_signed_base (string &out, NODE *node) {
   out.append(" '");
   out.append(" s");
   out.append(" b");
}
void writer_sv_octal_base (string &out, NODE *node) {
   if (node -> id == G_SV_OCTAL_UNSIGNED_BASE) {
      writer_sv_octal_unsigned_base(out, node -> sub);
      return; }
   if (node -> id == G_SV_OCTAL_SIGNED_BASE) {
      writer_sv_octal_signed_base(out, node -> sub);
      return; }
}
void writer_sv_octal_unsigned_base (string &out, NODE *node) {
   out.append(" '");
   out.append(" o");
}
void writer_sv_octal_signed_base (string &out, NODE *node) {
   out.append(" '");
   out.append(" s");
   out.append(" o");
}
void writer_sv_hex_base (string &out, NODE *node) {
   if (node -> id == G_SV_HEX_UNSIGNED_BASE) {
      writer_sv_hex_unsigned_base(out, node -> sub);
      return; }
   if (node -> id == G_SV_HEX_SIGNED_BASE) {
      writer_sv_hex_signed_base(out, node -> sub);
      return; }
}
void writer_sv_hex_unsigned_base (string &out, NODE *node) {
   out.append(" '");
   out.append(" h");
}
void writer_sv_hex_signed_base (string &out, NODE *node) {
   out.append(" '");
   out.append(" s");
   out.append(" h");
}
void writer_decimal_digit (string &out, NODE *node) {
   if (node -> id == G_0_DIGIT) {
      writer_0_digit(out, node -> sub);
      return; }
   if (node -> id == G_1_DIGIT) {
      writer_1_digit(out, node -> sub);
      return; }
   if (node -> id == G_2_DIGIT) {
      writer_2_digit(out, node -> sub);
      return; }
   if (node -> id == G_3_DIGIT) {
      writer_3_digit(out, node -> sub);
      return; }
   if (node -> id == G_4_DIGIT) {
      writer_4_digit(out, node -> sub);
      return; }
   if (node -> id == G_5_DIGIT) {
      writer_5_digit(out, node -> sub);
      return; }
   if (node -> id == G_6_DIGIT) {
      writer_6_digit(out, node -> sub);
      return; }
   if (node -> id == G_7_DIGIT) {
      writer_7_digit(out, node -> sub);
      return; }
   if (node -> id == G_8_DIGIT) {
      writer_8_digit(out, node -> sub);
      return; }
   if (node -> id == G_9_DIGIT) {
      writer_9_digit(out, node -> sub);
      return; }
}
void writer_binary_digit (string &out, NODE *node) {
   if (node -> id == G_X_DIGIT) {
      writer_x_digit(out, node -> sub);
      return; }
   if (node -> id == G_Z_DIGIT) {
      writer_z_digit(out, node -> sub);
      return; }
   if (node -> id == G_0_DIGIT) {
      writer_0_digit(out, node -> sub);
      return; }
   if (node -> id == G_1_DIGIT) {
      writer_1_digit(out, node -> sub);
      return; }
}
void writer_octal_digit (string &out, NODE *node) {
   if (node -> id == G_X_DIGIT) {
      writer_x_digit(out, node -> sub);
      return; }
   if (node -> id == G_Z_DIGIT) {
      writer_z_digit(out, node -> sub);
      return; }
   if (node -> id == G_0_DIGIT) {
      writer_0_digit(out, node -> sub);
      return; }
   if (node -> id == G_1_DIGIT) {
      writer_1_digit(out, node -> sub);
      return; }
   if (node -> id == G_2_DIGIT) {
      writer_2_digit(out, node -> sub);
      return; }
   if (node -> id == G_3_DIGIT) {
      writer_3_digit(out, node -> sub);
      return; }
   if (node -> id == G_4_DIGIT) {
      writer_4_digit(out, node -> sub);
      return; }
   if (node -> id == G_5_DIGIT) {
      writer_5_digit(out, node -> sub);
      return; }
   if (node -> id == G_6_DIGIT) {
      writer_6_digit(out, node -> sub);
      return; }
   if (node -> id == G_7_DIGIT) {
      writer_7_digit(out, node -> sub);
      return; }
}
void writer_hex_digit (string &out, NODE *node) {
   if (node -> id == G_X_DIGIT) {
      writer_x_digit(out, node -> sub);
      return; }
   if (node -> id == G_Z_DIGIT) {
      writer_z_digit(out, node -> sub);
      return; }
   if (node -> id == G_0_DIGIT) {
      writer_0_digit(out, node -> sub);
      return; }
   if (node -> id == G_1_DIGIT) {
      writer_1_digit(out, node -> sub);
      return; }
   if (node -> id == G_2_DIGIT) {
      writer_2_digit(out, node -> sub);
      return; }
   if (node -> id == G_3_DIGIT) {
      writer_3_digit(out, node -> sub);
      return; }
   if (node -> id == G_4_DIGIT) {
      writer_4_digit(out, node -> sub);
      return; }
   if (node -> id == G_5_DIGIT) {
      writer_5_digit(out, node -> sub);
      return; }
   if (node -> id == G_6_DIGIT) {
      writer_6_digit(out, node -> sub);
      return; }
   if (node -> id == G_7_DIGIT) {
      writer_7_digit(out, node -> sub);
      return; }
   if (node -> id == G_8_DIGIT) {
      writer_8_digit(out, node -> sub);
      return; }
   if (node -> id == G_9_DIGIT) {
      writer_9_digit(out, node -> sub);
      return; }
   if (node -> id == G_A_DIGIT) {
      writer_a_digit(out, node -> sub);
      return; }
   if (node -> id == G_B_DIGIT) {
      writer_b_digit(out, node -> sub);
      return; }
   if (node -> id == G_C_DIGIT) {
      writer_c_digit(out, node -> sub);
      return; }
   if (node -> id == G_D_DIGIT) {
      writer_d_digit(out, node -> sub);
      return; }
   if (node -> id == G_E_DIGIT) {
      writer_e_digit(out, node -> sub);
      return; }
   if (node -> id == G_F_DIGIT) {
      writer_f_digit(out, node -> sub);
      return; }
}
void writer_x_digit (string &out, NODE *node) {
   out.append(" x");
}
void writer_z_digit (string &out, NODE *node) {
   out.append(" z");
}
void writer_0_digit (string &out, NODE *node) {
   out.append(" 0");
}
void writer_1_digit (string &out, NODE *node) {
   out.append(" 1");
}
void writer_2_digit (string &out, NODE *node) {
   out.append(" 2");
}
void writer_3_digit (string &out, NODE *node) {
   out.append(" 3");
}
void writer_4_digit (string &out, NODE *node) {
   out.append(" 4");
}
void writer_5_digit (string &out, NODE *node) {
   out.append(" 5");
}
void writer_6_digit (string &out, NODE *node) {
   out.append(" 6");
}
void writer_7_digit (string &out, NODE *node) {
   out.append(" 7");
}
void writer_8_digit (string &out, NODE *node) {
   out.append(" 8");
}
void writer_9_digit (string &out, NODE *node) {
   out.append(" 9");
}
void writer_a_digit (string &out, NODE *node) {
   out.append(" a");
}
void writer_b_digit (string &out, NODE *node) {
   out.append(" b");
}
void writer_c_digit (string &out, NODE *node) {
   out.append(" c");
}
void writer_d_digit (string &out, NODE *node) {
   out.append(" d");
}
void writer_e_digit (string &out, NODE *node) {
   out.append(" e");
}
void writer_f_digit (string &out, NODE *node) {
   out.append(" f");
}
void writer_us_digit (string &out, NODE *node) {
   out.append(" _");
}
void writer_sv_attribute_instance (string &out, NODE *node) {
   out.append(" (*");if (node -> id == G_SV_ATTR_SPEC) { writer_sv_attr_spec(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_SV_LIST_ATTR_SPEC) { writer_sv_list_attr_spec(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" *)");
}
void writer_sv_attr_spec_h0 (string &out, NODE *node) {
   out.append(" =");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_attr_spec (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_ATTR_SPEC_H0) {
      writer_sv_attr_spec_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_list_attr_spec (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_ATTR_SPEC) {
      writer_sv_attr_spec(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_class_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_tf_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_genvar_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hierarchical_array_identifier (string &out, NODE *node) {
   if (node -> id == G_SV_HIERARCHICAL_IDENTIFIER) {
      writer_sv_hierarchical_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hierarchical_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_SV_HIERARCHICAL_IDENTIFIER_LIST) {
      writer_sv_hierarchical_identifier_list(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_sv_hierarchical_identifier_list (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_BIT_SELECT_LIST) {
      writer_sv_constant_bit_select_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" .");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hierarchical_parameter_identifier_h1 (string &out, NODE *node) {
   out.append(" .");
   if (node -> id == G_SV_HIERARCHICAL_PARAMETER_IDENTIFIER) {
      writer_sv_hierarchical_parameter_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hierarchical_parameter_identifier (string &out, NODE *node) {
   if (node -> id == G_SV_HIERARCHICAL_IDENTIFIER) {
      writer_sv_hierarchical_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_HIERARCHICAL_PARAMETER_IDENTIFIER_H1) {
      writer_sv_hierarchical_parameter_identifier_h1(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_hierarchical_variable_identifier (string &out, NODE *node) {
   if (node -> id == G_SV_HIERARCHICAL_IDENTIFIER) {
      writer_sv_hierarchical_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_index_variable_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_instance_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_module_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_net_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_port_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_ps_or_hierarchical_array_identifier (string &out, NODE *node) {
   if (node -> id == G_SV_HIERARCHICAL_ARRAY_IDENTIFIER) {
      writer_sv_hierarchical_array_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_type_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_sv_variable_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_hierarchical_name_h2 (string &out, NODE *node) {
   out.append(" .");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_hierarchical_name (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_HIERARCHICAL_NAME_H2) {
      writer_hierarchical_name_h2(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_si (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_list_of_si (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_system_si (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_simple_identifier (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_usi (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_list_of_usi (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_USI) {
      writer_usi(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_semikolon (string &out, NODE *node) {
   out.append(" ;");
}
void writer_pdvl_grammar (string &out, NODE *node) {
   out.append(" <\"");
   while (node -> id == G_PDVL_DECLARATION) {
      writer_pdvl_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" \">");
}
void writer_pdvl_declaration (string &out, NODE *node) {
   if (node -> id == G_PDVL_BUILD_COMMAND) {
      writer_pdvl_build_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_CLUSTER_DECLARATION) {
      writer_pdvl_cluster_declaration(out, node -> sub);
      return; }
}
void writer_pdvl_cluster_declaration (string &out, NODE *node) {
   if (node -> id == G_PDVL_CLUSTER_IDENTIFIER) {
      writer_pdvl_cluster_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_cluster_identifier (string &out, NODE *node) {
   if (node -> id == G_PDVL_CLUSTER_CL_SI) {
      writer_pdvl_cluster_cl_si(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_CLUSTER_SI) {
      writer_pdvl_cluster_si(out, node -> sub);
      return; }
}
void writer_pdvl_cluster_cl_si (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_pdvl_cluster_si (string &out, NODE *node) {
   out.append(" cluster");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_cluster_declaration_body (string &out, NODE *node) {
   if (node -> id == G_PDVL_SUB_CLUSTER_DECLARATION) {
      writer_pdvl_sub_cluster_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_PARAMETER_DECLARATION) {
      writer_sv_parameter_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_TYPE_DECLARATION) {
      writer_sv_type_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_COND_DECLARATION) {
      writer_pdvl_cond_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_EVENT_DECLARATION) {
      writer_pdvl_event_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_ITEM_DECLARATION) {
      writer_pdvl_item_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_REG_DECLARATION) {
      writer_pdvl_reg_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_LATCH_DECLARATION) {
      writer_pdvl_latch_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_DATA_DECLARATION) {
      writer_pdvl_data_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IF_DECLARATION) {
      writer_pdvl_if_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_CASE_DECLARATION) {
      writer_pdvl_case_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_FOREACH_DECLARATION) {
      writer_pdvl_foreach_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_FOR_DECLARATION) {
      writer_pdvl_for_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_DECLARATION) {
      writer_pdvl_transaction_declaration(out, node -> sub);
      return; }
   if (node -> id == G_SV_FUNCTION_DECLARATION) {
      writer_sv_function_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_THEOREM_DECLARATION) {
      writer_pdvl_theorem_declaration(out, node -> sub);
      return; }
}
void writer_pdvl_sub_cluster_declaration (string &out, NODE *node) {
   if (node -> id == G_PDVL_CLUSTER_IDENTIFIER) {
      writer_pdvl_cluster_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_item_declaration (string &out, NODE *node) {
   out.append(" item");
   if (node -> id == G_SV_ATTRIBUTE_INSTANCE) {
      writer_sv_attribute_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE) {
      writer_pdvl_identifier_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_BLOCKING_ASSIGN_EXPRESSION) {
      writer_sv_blocking_assign_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_reg_declaration (string &out, NODE *node) {
   out.append(" reg");
   if (node -> id == G_SV_ATTRIBUTE_INSTANCE) {
      writer_sv_attribute_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE) {
      writer_pdvl_identifier_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_MACRO_LIST) {
      writer_pdvl_transaction_macro_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_latch_declaration (string &out, NODE *node) {
   out.append(" latch");
   if (node -> id == G_SV_ATTRIBUTE_INSTANCE) {
      writer_sv_attribute_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE) {
      writer_pdvl_identifier_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_MACRO_LIST) {
      writer_pdvl_transaction_macro_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_identifier_type (string &out, NODE *node) {
   if (node -> id == G_PDVL_IDENTIFIER_TYPE_PREV0) {
      writer_pdvl_identifier_type_prev0(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE_PREV1) {
      writer_pdvl_identifier_type_prev1(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE_PREV2) {
      writer_pdvl_identifier_type_prev2(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE_PREV3) {
      writer_pdvl_identifier_type_prev3(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE_PREV4) {
      writer_pdvl_identifier_type_prev4(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE_PREV5) {
      writer_pdvl_identifier_type_prev5(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE_PREV6) {
      writer_pdvl_identifier_type_prev6(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IDENTIFIER_TYPE_PREV7) {
      writer_pdvl_identifier_type_prev7(out, node -> sub);
      return; }
}
void writer_pdvl_identifier_type_prev0 (string &out, NODE *node) {
   if (node -> id == G_PDVL_PACKED_DIMENSION_LIST) {
      writer_pdvl_packed_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_LIST) {
      writer_pdvl_identifier_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_UNPACKED_DIMENSION_LIST) {
      writer_pdvl_unpacked_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_identifier_type_prev1 (string &out, NODE *node) {
   if (node -> id == G_PDVL_PACKED_DIMENSION_LIST) {
      writer_pdvl_packed_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_LIST) {
      writer_pdvl_identifier_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_identifier_type_prev2 (string &out, NODE *node) {
   if (node -> id == G_PDVL_ENUM_DATA_TYPE) {
      writer_pdvl_enum_data_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_LIST) {
      writer_pdvl_identifier_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_identifier_type_prev3 (string &out, NODE *node) {
   if (node -> id == G_PDVL_IDENTIFIER_LIST) {
      writer_pdvl_identifier_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_UNPACKED_DIMENSION_LIST) {
      writer_pdvl_unpacked_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_identifier_type_prev4 (string &out, NODE *node) {
   if (node -> id == G_PDVL_STRUCT_OR_UNION_DATA_TYPE) {
      writer_pdvl_struct_or_union_data_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_LIST) {
      writer_pdvl_identifier_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_UNPACKED_DIMENSION_LIST) {
      writer_pdvl_unpacked_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_identifier_type_prev5 (string &out, NODE *node) {
   if (node -> id == G_PDVL_STRUCT_OR_UNION_DATA_TYPE) {
      writer_pdvl_struct_or_union_data_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_LIST) {
      writer_pdvl_identifier_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_identifier_type_prev6 (string &out, NODE *node) {
   if (node -> id == G_PDVL_TYPE_IDENTIFIER_DATA_TYPE) {
      writer_pdvl_type_identifier_data_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_IDENTIFIER_LIST) {
      writer_pdvl_identifier_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_identifier_type_prev7 (string &out, NODE *node) {
   if (node -> id == G_PDVL_IDENTIFIER_LIST) {
      writer_pdvl_identifier_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_identifier_list (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_LIST_OF_SI) {
      writer_list_of_si(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_pdvl_packed_dimension_list (string &out, NODE *node) {
   if (node -> id == G_PDVL_PACKED_OR_C_STYLE) {
      writer_pdvl_packed_or_c_style(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_PACKED_DIMENSION_LIST) {
      writer_pdvl_packed_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_packed_or_c_style (string &out, NODE *node) {
   if (node -> id == G_SV_PACKED_DIMENSION) {
      writer_sv_packed_dimension(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_C_STYLE_DIMENSION) {
      writer_pdvl_c_style_dimension(out, node -> sub);
      return; }
}
void writer_pdvl_c_style_dimension (string &out, NODE *node) {
   out.append(" [");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ]");
}
void writer_pdvl_unpacked_dimension_list (string &out, NODE *node) {
   if (node -> id == G_SV_UNPACKED_DIMENSION) {
      writer_sv_unpacked_dimension(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_UNPACKED_DIMENSION_LIST) {
      writer_pdvl_unpacked_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_enum_data_type (string &out, NODE *node) {
   out.append(" enum");
   if (node -> id == G_SV_PACKED_DIMENSION_LIST) {
      writer_sv_packed_dimension_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   if (node -> id == G_SV_ENUM_NAME_DECLARATION_LIST) {
      writer_sv_enum_name_declaration_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" }");
}
void writer_pdvl_struct_or_union_data_type (string &out, NODE *node) {
   if (node -> id == G_SV_STRUCT_UNION) {
      writer_sv_struct_union(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PACKED_KEYWORD) {
      writer_sv_packed_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_SV_STRUCT_UNION_MEMBER) {
      writer_sv_struct_union_member(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_type_identifier_data_type (string &out, NODE *node) {
   if (node -> id == G_SV_CLASS_SCOPE) {
      writer_sv_class_scope(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_TYPE_IDENTIFIER) {
      writer_sv_type_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_macro_list (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_MACRO_LIST_PREV0) {
      writer_pdvl_transaction_macro_list_prev0(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_MACRO_LIST_PREV1) {
      writer_pdvl_transaction_macro_list_prev1(out, node -> sub);
      return; }
}
void writer_pdvl_transaction_macro_list_prev0 (string &out, NODE *node) {
   if (node -> id == G_PDVL_AT_CONDITION) {
      writer_pdvl_at_condition(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
   out.append(" }");
   if (node -> id == G_PDVL_TRANSACTION_MACRO_LIST) {
      writer_pdvl_transaction_macro_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_macro_list_prev1 (string &out, NODE *node) {
   if (node -> id == G_PDVL_AT_CONDITION) {
      writer_pdvl_at_condition(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_DATA_DECLARATION_BODY) {
      writer_pdvl_data_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
   if (node -> id == G_PDVL_TRANSACTION_MACRO_LIST) {
      writer_pdvl_transaction_macro_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_data_declaration (string &out, NODE *node) {
   if (node -> id == G_PDVL_DATA_IDENTIFIER) {
      writer_pdvl_data_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TF_PORT_LIST_BRACKETS) {
      writer_pdvl_tf_port_list_brackets(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_DATA_DECLARATION_BODY) {
      writer_pdvl_data_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_data_identifier (string &out, NODE *node) {
   if (node -> id == G_PDVL_DATA_IDENTIFIER_BY_NAME) {
      writer_pdvl_data_identifier_by_name(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_AND_DATA_IDENTIFIER_BY_NAME) {
      writer_pdvl_transaction_and_data_identifier_by_name(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_DATA_SI) {
      writer_pdvl_data_si(out, node -> sub);
      return; }
}
void writer_pdvl_data_identifier_by_name (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_pdvl_transaction_and_data_identifier_by_name (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_pdvl_data_si (string &out, NODE *node) {
   out.append(" data");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_data_declaration_body (string &out, NODE *node) {
   if (node -> id == G_SV_STATEMENT_ITEM_BLOCKING_ASSIGNMENT) {
      writer_sv_statement_item_blocking_assignment(out, node -> sub);
      return; }
   if (node -> id == G_SV_CASE_STATEMENT) {
      writer_sv_case_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_CONDITIONAL_STATEMENT) {
      writer_sv_conditional_statement(out, node -> sub);
      return; }
   if (node -> id == G_SV_LOOP_STATEMENT) {
      writer_sv_loop_statement(out, node -> sub);
      return; }
}
void writer_pdvl_cond_declaration (string &out, NODE *node) {
   if (node -> id == G_PDVL_COND_DECLARATION_LEVEL_BODY) {
      writer_pdvl_cond_declaration_level_body(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_COND_DECLARATION_BODY_PORT) {
      writer_pdvl_cond_declaration_body_port(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_COND_DECLARATION_BODY) {
      writer_pdvl_cond_declaration_body(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_COND_DECLARATION_LEVEL) {
      writer_pdvl_cond_declaration_level(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_COND_DECLARATION_REG) {
      writer_pdvl_cond_declaration_reg(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_COND_DECLARATION_SIMPLE) {
      writer_pdvl_cond_declaration_simple(out, node -> sub);
      return; }
}
void writer_pdvl_cond_declaration_level_body (string &out, NODE *node) {
   if (node -> id == G_PDVL_COND_IDENTIFIER) {
      writer_pdvl_cond_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_LEVEL_IDENTIFIER) {
      writer_pdvl_level_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_COND_SIGNAL_NAME) {
      writer_pdvl_cond_signal_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_COND_CONDITIONAL_STATEMENT) {
      writer_pdvl_cond_conditional_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_cond_declaration_body_port (string &out, NODE *node) {
   if (node -> id == G_PDVL_COND_IDENTIFIER) {
      writer_pdvl_cond_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TF_PORT_LIST_BRACKETS) {
      writer_pdvl_tf_port_list_brackets(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_COND_CONDITIONAL_STATEMENT) {
      writer_pdvl_cond_conditional_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_cond_declaration_body (string &out, NODE *node) {
   if (node -> id == G_SV_ATTRIBUTE_INSTANCE) {
      writer_sv_attribute_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_COND_IDENTIFIER) {
      writer_pdvl_cond_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_COND_CONDITIONAL_STATEMENT) {
      writer_pdvl_cond_conditional_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_tf_port_list_brackets_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_FUNCTION_PORT_LIST) {
      writer_sv_function_port_list(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_tf_port_list_brackets (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SV_FUNCTION_PORT_LIST) { writer_sv_function_port_list(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_PDVL_TF_PORT_LIST_BRACKETS_H0) { writer_pdvl_tf_port_list_brackets_h0(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" )");
}
void writer_pdvl_cond_declaration_level (string &out, NODE *node) {
   if (node -> id == G_PDVL_COND_IDENTIFIER) {
      writer_pdvl_cond_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_LEVEL_IDENTIFIER) {
      writer_pdvl_level_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_COND_SIGNAL_NAME) {
      writer_pdvl_cond_signal_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_level_identifier (string &out, NODE *node) {
   if (node -> id == G_PDVL_HIGH_LEVEL_IDENTIFIER) {
      writer_pdvl_high_level_identifier(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_LOW_LEVEL_IDENTIFIER) {
      writer_pdvl_low_level_identifier(out, node -> sub);
      return; }
}
void writer_pdvl_high_level_identifier (string &out, NODE *node) {
   out.append(" high");
}
void writer_pdvl_low_level_identifier (string &out, NODE *node) {
   out.append(" low");
}
void writer_pdvl_cond_signal_name (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_cond_declaration_reg (string &out, NODE *node) {
   if (node -> id == G_PDVL_LIST_OF_COND_IDENTIFIERS) {
      writer_pdvl_list_of_cond_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" reg");
   out.append(" ;");
}
void writer_pdvl_cond_declaration_simple (string &out, NODE *node) {
   if (node -> id == G_SV_ATTRIBUTE_INSTANCE) {
      writer_sv_attribute_instance(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_LIST_OF_COND_IDENTIFIERS) {
      writer_pdvl_list_of_cond_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_list_of_cond_identifiers (string &out, NODE *node) {
   if (node -> id == G_PDVL_LIST_OF_COND_IDENTIFIERS_SI) {
      writer_pdvl_list_of_cond_identifiers_si(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_LIST_OF_COND_IDENTIFIERS_BY_NAME) {
      writer_pdvl_list_of_cond_identifiers_by_name(out, node -> sub);
      return; }
}
void writer_pdvl_list_of_cond_identifiers_si (string &out, NODE *node) {
   out.append(" cond");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_list_of_cond_identifiers_by_name (string &out, NODE *node) {
   if (node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) {
      writer_pdvl_cond_identifier_by_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_PDVL_LIST_OF_COND_IDENTIFIERS_BY_NAME_EXTENSION) {
      writer_pdvl_list_of_cond_identifiers_by_name_extension(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_pdvl_list_of_cond_identifiers_by_name_extension (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) {
      writer_pdvl_cond_identifier_by_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_cond_identifier (string &out, NODE *node) {
   if (node -> id == G_PDVL_COND_IDENTIFIER_BY_NAME) {
      writer_pdvl_cond_identifier_by_name(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_COND_SI) {
      writer_pdvl_cond_si(out, node -> sub);
      return; }
}
void writer_pdvl_cond_identifier_by_name (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_pdvl_cond_si (string &out, NODE *node) {
   out.append(" cond");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_cond_conditional_statement (string &out, NODE *node) {
   out.append(" if");
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   if (node -> id == G_PDVL_IMPLICIT_COND_HANDLE) {
      writer_pdvl_implicit_cond_handle(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_implicit_cond_handle (string &out, NODE *node) {
   out.append(" this");
}
void writer_pdvl_cond_macro_list (string &out, NODE *node) {
   out.append(" initial");
   out.append(" {");
   while (node -> id == G_PDVL_DATA_DECLARATION_BODY) {
      writer_pdvl_data_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_event_declaration (string &out, NODE *node) {
   if (node -> id == G_PDVL_LIST_OF_EVENT_IDENTIFIERS) {
      writer_pdvl_list_of_event_identifiers(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EDGE_IDENTIFIER) {
      writer_sv_edge_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_EVENT_SIGNAL_NAME) {
      writer_pdvl_event_signal_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_list_of_event_identifiers (string &out, NODE *node) {
   if (node -> id == G_PDVL_LIST_OF_EVENT_IDENTIFIERS_SI) {
      writer_pdvl_list_of_event_identifiers_si(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_LIST_OF_EVENT_IDENTIFIERS_BY_NAME) {
      writer_pdvl_list_of_event_identifiers_by_name(out, node -> sub);
      return; }
}
void writer_pdvl_list_of_event_identifiers_si_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_list_of_event_identifiers_si (string &out, NODE *node) {
   out.append(" event");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_PDVL_LIST_OF_EVENT_IDENTIFIERS_SI_H0) {
      writer_pdvl_list_of_event_identifiers_si_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_pdvl_list_of_event_identifiers_by_name (string &out, NODE *node) {
   if (node -> id == G_PDVL_EVENT_IDENTIFIER_BY_NAME) {
      writer_pdvl_event_identifier_by_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_PDVL_LIST_OF_EVENT_IDENTIFIERS_BY_NAME_EXTENSION) {
      writer_pdvl_list_of_event_identifiers_by_name_extension(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_pdvl_list_of_event_identifiers_by_name_extension (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_PDVL_EVENT_IDENTIFIER_BY_NAME) {
      writer_pdvl_event_identifier_by_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_event_identifier (string &out, NODE *node) {
   if (node -> id == G_PDVL_EVENT_IDENTIFIER_BY_NAME) {
      writer_pdvl_event_identifier_by_name(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_EVENT_SI) {
      writer_pdvl_event_si(out, node -> sub);
      return; }
}
void writer_pdvl_event_identifier_by_name (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_pdvl_event_si (string &out, NODE *node) {
   out.append(" event");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_event_signal_name (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_declaration (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_DECLARATION_BODY) {
      writer_pdvl_transaction_declaration_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_declaration_body (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_REPLACE) {
      writer_pdvl_transaction_replace(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_IDENTIFIER) {
      writer_pdvl_transaction_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_TRANSACTION_STATEMENT) {
      writer_pdvl_transaction_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_transaction_replace (string &out, NODE *node) {
   out.append(" replace");
}
void writer_pdvl_transaction_identifier (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_IDENTIFIER_BY_NAME) {
      writer_pdvl_transaction_identifier_by_name(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_SI) {
      writer_pdvl_transaction_si(out, node -> sub);
      return; }
}
void writer_pdvl_transaction_identifier_by_name (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_pdvl_transaction_si (string &out, NODE *node) {
   out.append(" trans");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_statement (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_AT_STATEMENT) {
      writer_pdvl_transaction_at_statement(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_FINITE_STATEMENT) {
      writer_pdvl_transaction_finite_statement(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_PIPE_STATEMENT) {
      writer_pdvl_transaction_pipe_statement(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_PRIORITY_LIST) {
      writer_pdvl_transaction_priority_list(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_UNIQUE_SINGLE) {
      writer_pdvl_transaction_unique_single(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_UNIQUE_LIST) {
      writer_pdvl_transaction_unique_list(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_UNIQUE0_SINGLE) {
      writer_pdvl_transaction_unique0_single(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_UNIQUE0_LIST) {
      writer_pdvl_transaction_unique0_list(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_NEXT_STATE_STATEMENT) {
      writer_pdvl_next_state_statement(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_EMIT_DELAYED_EVENT) {
      writer_pdvl_emit_delayed_event(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_DO_NOT_EMIT) {
      writer_pdvl_do_not_emit(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_EMIT) {
      writer_pdvl_emit(out, node -> sub);
      return; }
}
void writer_pdvl_transaction_body (string &out, NODE *node) {
   out.append(" {");
   while (node -> id == G_PDVL_TRANSACTION_STATEMENT) {
      writer_pdvl_transaction_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_priority_unique_propagate (string &out, NODE *node) {
   out.append(" propagate");
}
void writer_pdvl_transaction_priority_list (string &out, NODE *node) {
   out.append(" priority");
   if (node -> id == G_PDVL_PRIORITY_UNIQUE_PROPAGATE) {
      writer_pdvl_priority_unique_propagate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY) {
      writer_pdvl_transaction_priority_unique_list_entry(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY) {
      writer_pdvl_transaction_priority_unique_default_entry(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" }");
}
void writer_pdvl_transaction_priority_unique_list_entry (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) {
      writer_pdvl_transaction_at_single_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_priority_unique_default_entry (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_DEFAULT_SINGLE_STATEMENT) {
      writer_pdvl_transaction_default_single_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_unique_single (string &out, NODE *node) {
   out.append(" unique");
   if (node -> id == G_PDVL_PRIORITY_UNIQUE_PROPAGATE) {
      writer_pdvl_priority_unique_propagate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY) {
      writer_pdvl_transaction_priority_unique_list_entry(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_unique_list (string &out, NODE *node) {
   out.append(" unique");
   if (node -> id == G_PDVL_PRIORITY_UNIQUE_PROPAGATE) {
      writer_pdvl_priority_unique_propagate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY) {
      writer_pdvl_transaction_priority_unique_list_entry(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY) {
      writer_pdvl_transaction_priority_unique_default_entry(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" }");
}
void writer_pdvl_transaction_unique0_single (string &out, NODE *node) {
   out.append(" unique0");
   if (node -> id == G_PDVL_PRIORITY_UNIQUE_PROPAGATE) {
      writer_pdvl_priority_unique_propagate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY) {
      writer_pdvl_transaction_priority_unique_list_entry(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_unique0_list (string &out, NODE *node) {
   out.append(" unique0");
   if (node -> id == G_PDVL_PRIORITY_UNIQUE_PROPAGATE) {
      writer_pdvl_priority_unique_propagate(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_LIST_ENTRY) {
      writer_pdvl_transaction_priority_unique_list_entry(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_PRIORITY_UNIQUE_DEFAULT_ENTRY) {
      writer_pdvl_transaction_priority_unique_default_entry(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" }");
}
void writer_pdvl_transaction_state_body (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SEMIKOLON) {
      writer_semikolon(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_state_statement (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_PDVL_TRANSACTION_STATEMENT) {
      writer_pdvl_transaction_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_if_declaration (string &out, NODE *node) {
   out.append(" if");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
   while (node -> id == G_PDVL_ELSE_IF_DECLARATION) {
      writer_pdvl_else_if_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_PDVL_ELSE_DECLARATION) {
      writer_pdvl_else_declaration(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_else_if_declaration (string &out, NODE *node) {
   out.append(" else");
   out.append(" if");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_else_declaration (string &out, NODE *node) {
   out.append(" else");
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_case_declaration (string &out, NODE *node) {
   out.append(" case");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   while (node -> id == G_PDVL_CASE_DECLARATION_ITEM) {
      writer_pdvl_case_declaration_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" endcase");
}
void writer_pdvl_case_declaration_item (string &out, NODE *node) {
   if (node -> id == G_PDVL_CASE_DECLARATION_DEFAULT) {
      writer_pdvl_case_declaration_default(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_CASE_DECLARATION_CONSTANT_EXPRESSION) {
      writer_pdvl_case_declaration_constant_expression(out, node -> sub);
      return; }
}
void writer_pdvl_case_declaration_constant_expression (string &out, NODE *node) {
   if (node -> id == G_PDVL_LIST_OF_CONSTANT_EXPRESSION) {
      writer_pdvl_list_of_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_case_declaration_default (string &out, NODE *node) {
   out.append(" default");
   out.append(" :");
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_for_declaration (string &out, NODE *node) {
   out.append(" for");
   out.append(" (");out.append(" int");if (node -> id == G_SV_GENVAR_INITIALIZATION) { writer_sv_genvar_initialization(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ;");if (node -> id == G_SV_GENVAR_EXPRESSION) { writer_sv_genvar_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ;");if (node -> id == G_SV_GENVAR_ITERATION) { writer_sv_genvar_iteration(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_foreach_declaration (string &out, NODE *node) {
   out.append(" foreach");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" in");
   if (node -> id == G_PDVL_FOREACH_LIST_DEF) {
      writer_pdvl_foreach_list_def(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_at_condition (string &out, NODE *node) {
   if (node -> id == G_PDVL_CONDITION_CONTROL) {
      writer_pdvl_condition_control(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_CONDITION_EXPRESSION) {
      writer_pdvl_condition_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_condition_control (string &out, NODE *node) {
   if (node -> id == G_PDVL_AT_FALSE_CONDITION) {
      writer_pdvl_at_false_condition(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_AT_TRUE_CONDITION) {
      writer_pdvl_at_true_condition(out, node -> sub);
      return; }
}
void writer_pdvl_at_false_condition (string &out, NODE *node) {
   out.append(" @");
   out.append(" !");
}
void writer_pdvl_at_true_condition (string &out, NODE *node) {
   out.append(" @");
}
void writer_pdvl_condition_expression (string &out, NODE *node) {
   if (node -> id == G_PDVL_CONDITION_EXPRESSION_PREV0) {
      writer_pdvl_condition_expression_prev0(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_CONDITION_EXPRESSION_PREV1) {
      writer_pdvl_condition_expression_prev1(out, node -> sub);
      return; }
}
void writer_pdvl_condition_expression_prev0 (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_EXPRESSION_LIST_BRACKETS) {
      writer_pdvl_expression_list_brackets(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_condition_expression_prev1 (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_pdvl_expression_list_brackets (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SV_EXPRESSION) { writer_sv_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_SV_EXPRESSION_LIST) { writer_sv_expression_list(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" )");
}
void writer_pdvl_at_keyword_prio (string &out, NODE *node) {
   out.append(" prioxity");
}
void writer_pdvl_at_keyword (string &out, NODE *node) {
   if (node -> id == G_PDVL_AT_KEYWORD_PRIO) {
      writer_pdvl_at_keyword_prio(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_at_statement (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) {
      writer_pdvl_transaction_at_single_else_statement(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) {
      writer_pdvl_transaction_at_single_statement(out, node -> sub);
      return; }
}
void writer_pdvl_transaction_at_single_statement (string &out, NODE *node) {
   if (node -> id == G_PDVL_AT_CONDITION) {
      writer_pdvl_at_condition(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SEMIKOLON) {
      writer_semikolon(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_default_single_statement (string &out, NODE *node) {
   out.append(" default");
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SEMIKOLON) {
      writer_semikolon(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_at_single_else_statement (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV0) {
      writer_pdvl_transaction_at_single_else_statement_prev0(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV1) {
      writer_pdvl_transaction_at_single_else_statement_prev1(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT_PREV2) {
      writer_pdvl_transaction_at_single_else_statement_prev2(out, node -> sub);
      return; }
}
void writer_pdvl_transaction_at_single_else_statement_prev0 (string &out, NODE *node) {
   if (node -> id == G_PDVL_AT_CONDITION) {
      writer_pdvl_at_condition(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" else");
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SEMIKOLON) {
      writer_semikolon(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_at_single_else_statement_prev1 (string &out, NODE *node) {
   if (node -> id == G_PDVL_AT_CONDITION) {
      writer_pdvl_at_condition(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" else");
   if (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_ELSE_STATEMENT) {
      writer_pdvl_transaction_at_single_else_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SEMIKOLON) {
      writer_semikolon(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_at_single_else_statement_prev2 (string &out, NODE *node) {
   if (node -> id == G_PDVL_AT_CONDITION) {
      writer_pdvl_at_condition(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" else");
   if (node -> id == G_PDVL_TRANSACTION_AT_SINGLE_STATEMENT) {
      writer_pdvl_transaction_at_single_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SEMIKOLON) {
      writer_semikolon(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_finite_statement (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_FINITE_KEYWORD) {
      writer_pdvl_transaction_finite_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_PDVL_TRANSACTION_FINITE_ONE_HOT_KEYWORD) {
      writer_pdvl_transaction_finite_one_hot_keyword(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_FINITE_IDENTIFIER) {
      writer_pdvl_transaction_finite_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_TRANSACTION_FINITE_CASE_ITEM) {
      writer_pdvl_transaction_finite_case_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_transaction_finite_keyword (string &out, NODE *node) {
   out.append(" finite");
}
void writer_pdvl_transaction_finite_one_hot_keyword (string &out, NODE *node) {
   out.append(" one_hot");
}
void writer_pdvl_transaction_finite_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_finite_case_item (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_pipe_statement (string &out, NODE *node) {
   if (node -> id == G_PDVL_PIPE_CONST_TRANSACTION_STATEMENT) {
      writer_pdvl_pipe_const_transaction_statement(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_PIPE_RANGE_TRANSACTION_STATEMENT) {
      writer_pdvl_pipe_range_transaction_statement(out, node -> sub);
      return; }
}
void writer_pdvl_pipe_const_transaction_statement (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_PIPE_KEYWORD) {
      writer_pdvl_transaction_pipe_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_pipe_range_transaction_statement (string &out, NODE *node) {
   if (node -> id == G_PDVL_TRANSACTION_PIPE_KEYWORD) {
      writer_pdvl_transaction_pipe_keyword(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_PACKED_DIMENSION) {
      writer_sv_packed_dimension(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_TRANSACTION_BODY) {
      writer_pdvl_transaction_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_transaction_pipe_keyword (string &out, NODE *node) {
   out.append(" pipe");
}
void writer_pdvl_next_state_statement (string &out, NODE *node) {
   out.append(" #");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_emit_delayed_event (string &out, NODE *node) {
   if (node -> id == G_SV_DELAY_CONTROL) {
      writer_sv_delay_control(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SV_EXPRESSION) {
      writer_sv_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_emit (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_PDVL_EXPRESSION_LIST_BRACKETS) {
      writer_pdvl_expression_list_brackets(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_do_not_emit (string &out, NODE *node) {
   out.append(" !");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_build_command (string &out, NODE *node) {
   out.append(" build");
   if (node -> id == G_SV_MODULE_IDENTIFIER) {
      writer_sv_module_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_BUILD_COMMAND_BODY) {
      writer_pdvl_build_command_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_build_command_body (string &out, NODE *node) {
   if (node -> id == G_SV_PARAMETER_DECLARATION) {
      writer_sv_parameter_declaration(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_PLACE_COMMAND) {
      writer_pdvl_place_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_UNIQUIFY_COMMAND) {
      writer_pdvl_uniquify_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_JOIN_BODY_COMMAND) {
      writer_pdvl_join_body_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_JOIN_CLUSTER_COMMAND) {
      writer_pdvl_join_cluster_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_REMOVE_COMMAND) {
      writer_pdvl_remove_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_REPLACE_COMMAND) {
      writer_pdvl_replace_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_MOVE_COMMAND) {
      writer_pdvl_move_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_ROUTE_COMMAND) {
      writer_pdvl_route_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_IF_COMMAND) {
      writer_pdvl_if_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_CASE_COMMAND) {
      writer_pdvl_case_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_FOR_COMMAND) {
      writer_pdvl_for_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_FOREACH_COMMAND) {
      writer_pdvl_foreach_command(out, node -> sub);
      return; }
}
void writer_pdvl_uniquify_command (string &out, NODE *node) {
   out.append(" uniquify");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_place_command (string &out, NODE *node) {
   out.append(" place");
   if (node -> id == G_SV_MODULE_IDENTIFIER) {
      writer_sv_module_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_join_body_command (string &out, NODE *node) {
   if (node -> id == G_PDVL_JOIN_BODY_COMMAND_PREV0) {
      writer_pdvl_join_body_command_prev0(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_JOIN_BODY_COMMAND_PREV1) {
      writer_pdvl_join_body_command_prev1(out, node -> sub);
      return; }
}
void writer_pdvl_join_body_command_prev0 (string &out, NODE *node) {
   out.append(" join");
   if (node -> id == G_PDVL_JOIN_BODY) {
      writer_pdvl_join_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_join_body_command_prev1 (string &out, NODE *node) {
   out.append(" join");
   if (node -> id == G_PDVL_JOIN_BODY) {
      writer_pdvl_join_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SEMIKOLON) {
      writer_semikolon(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_join_body (string &out, NODE *node) {
   out.append(" {");
   while (node -> id == G_PDVL_CLUSTER_DECLARATION_BODY) {
      writer_pdvl_cluster_declaration_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_join_cluster_command (string &out, NODE *node) {
   if (node -> id == G_PDVL_JOIN_CLUSTER_BODY_COMMAND) {
      writer_pdvl_join_cluster_body_command(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_JOIN_CLUSTER_SINGLE_COMMAND) {
      writer_pdvl_join_cluster_single_command(out, node -> sub);
      return; }
}
void writer_pdvl_join_cluster_body_command (string &out, NODE *node) {
   out.append(" join");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_JOIN_CLUSTER_BODY) {
      writer_pdvl_join_cluster_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_join_cluster_body (string &out, NODE *node) {
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_join_cluster_single_command (string &out, NODE *node) {
   out.append(" join");
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_replace_command (string &out, NODE *node) {
   out.append(" replace");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_remove_command (string &out, NODE *node) {
   out.append(" remove");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_LIST_OF_SI) {
      writer_list_of_si(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_move_command (string &out, NODE *node) {
   out.append(" move");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_LIST_OF_SI) {
      writer_list_of_si(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_route_command (string &out, NODE *node) {
   out.append(" route");
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   if (node -> id == G_HIERARCHICAL_NAME) {
      writer_hierarchical_name(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_PDVL_ROUTE_SIGNAL_IDENTIFIER) {
      writer_pdvl_route_signal_identifier(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" ;");
}
void writer_pdvl_route_signal_identifier (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_if_command (string &out, NODE *node) {
   out.append(" if");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   out.append(" {");
   while (node -> id == G_PDVL_BUILD_COMMAND_BODY) {
      writer_pdvl_build_command_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
   while (node -> id == G_PDVL_ELSE_IF_COMMAND) {
      writer_pdvl_else_if_command(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   if (node -> id == G_PDVL_ELSE_COMMAND) {
      writer_pdvl_else_command(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_else_if_command (string &out, NODE *node) {
   out.append(" else");
   out.append(" if");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   out.append(" {");
   while (node -> id == G_PDVL_BUILD_COMMAND_BODY) {
      writer_pdvl_build_command_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_else_command (string &out, NODE *node) {
   out.append(" else");
   out.append(" {");
   while (node -> id == G_PDVL_BUILD_COMMAND_BODY) {
      writer_pdvl_build_command_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_case_command (string &out, NODE *node) {
   out.append(" case");
   out.append(" (");if (node -> id == G_SV_CONSTANT_EXPRESSION) { writer_sv_constant_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   while (node -> id == G_PDVL_CASE_COMMAND_ITEM) {
      writer_pdvl_case_command_item(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" endcase");
}
void writer_pdvl_case_command_item (string &out, NODE *node) {
   if (node -> id == G_PDVL_CASE_COMMAND_DEFAULT) {
      writer_pdvl_case_command_default(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_CASE_COMMAND_CONSTANT_EXPRESSION) {
      writer_pdvl_case_command_constant_expression(out, node -> sub);
      return; }
}
void writer_pdvl_case_command_constant_expression (string &out, NODE *node) {
   if (node -> id == G_PDVL_LIST_OF_CONSTANT_EXPRESSION) {
      writer_pdvl_list_of_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   out.append(" {");
   while (node -> id == G_PDVL_BUILD_COMMAND_BODY) {
      writer_pdvl_build_command_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_list_of_constant_expression_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_list_of_constant_expression (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_PDVL_LIST_OF_CONSTANT_EXPRESSION_H0) {
      writer_pdvl_list_of_constant_expression_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_pdvl_case_command_default (string &out, NODE *node) {
   out.append(" default");
   out.append(" :");
   out.append(" {");
   while (node -> id == G_PDVL_BUILD_COMMAND_BODY) {
      writer_pdvl_build_command_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_for_command (string &out, NODE *node) {
   out.append(" for");
   out.append(" (");out.append(" int");if (node -> id == G_SV_GENVAR_INITIALIZATION) { writer_sv_genvar_initialization(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ;");if (node -> id == G_SV_GENVAR_EXPRESSION) { writer_sv_genvar_expression(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" ;");if (node -> id == G_SV_GENVAR_ITERATION) { writer_sv_genvar_iteration(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
   out.append(" {");
   while (node -> id == G_PDVL_BUILD_COMMAND_BODY) {
      writer_pdvl_build_command_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_foreach_command (string &out, NODE *node) {
   out.append(" foreach");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" in");
   if (node -> id == G_PDVL_FOREACH_LIST_DEF) {
      writer_pdvl_foreach_list_def(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   while (node -> id == G_PDVL_BUILD_COMMAND_BODY) {
      writer_pdvl_build_command_body(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" }");
}
void writer_pdvl_foreach_list_def (string &out, NODE *node) {
   if (node -> id == G_PDVL_FOREACH_LIST) {
      writer_pdvl_foreach_list(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_FOREACH_CONSTANT_EXPRESSION) {
      writer_pdvl_foreach_constant_expression(out, node -> sub);
      return; }
}
void writer_pdvl_foreach_list (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_USI) { writer_usi(out, node -> sub);if (node -> next != NULL) node = node -> next; }while (node -> id == G_LIST_OF_USI) { writer_list_of_usi(out, node -> sub);if (node -> next == NULL) break; node = node -> next; }out.append(" )");
}
void writer_pdvl_foreach_constant_expression (string &out, NODE *node) {
   if (node -> id == G_SV_CONSTANT_EXPRESSION) {
      writer_sv_constant_expression(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_gallina_grammar (string &out, NODE *node) {
   while (node -> id == G_GA_DECLARATION) {
      writer_ga_declaration(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_ga_declaration (string &out, NODE *node) {
   if (node -> id == G_GA_INDUCTIVE_DECLARATION) {
      writer_ga_inductive_declaration(out, node -> sub);
      return; }
   if (node -> id == G_GA_DEFINITION_DECLARATION) {
      writer_ga_definition_declaration(out, node -> sub);
      return; }
   if (node -> id == G_GA_FIXPOINT_DECLARATION) {
      writer_ga_fixpoint_declaration(out, node -> sub);
      return; }
}
void writer_ga_inductive_declaration_h0 (string &out, NODE *node) {
   if (node -> id == G_GA_INDUCTIVE_TERM) {
      writer_ga_inductive_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_inductive_declaration (string &out, NODE *node) {
   out.append(" Inductive");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_GA_TYPE) {
      writer_ga_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :=");
   while (node -> id == G_GA_INDUCTIVE_DECLARATION_H0) {
      writer_ga_inductive_declaration_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" .");
}
void writer_ga_inductive_term (string &out, NODE *node) {
   if (node -> id == G_GA_INDUCTIVE_TERM_PREV0) {
      writer_ga_inductive_term_prev0(out, node -> sub);
      return; }
   if (node -> id == G_GA_INDUCTIVE_TERM_PREV1) {
      writer_ga_inductive_term_prev1(out, node -> sub);
      return; }
}
void writer_ga_inductive_term_prev0_h0 (string &out, NODE *node) {
   if (node -> id == G_GA_ARGS) {
      writer_ga_args(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_inductive_term_prev0 (string &out, NODE *node) {
   out.append(" |");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_INDUCTIVE_TERM_PREV0_H0) {
      writer_ga_inductive_term_prev0_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_ga_inductive_term_prev1 (string &out, NODE *node) {
   out.append(" |");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_definition_declaration_h1 (string &out, NODE *node) {
   if (node -> id == G_GA_ARGS) {
      writer_ga_args(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_definition_declaration (string &out, NODE *node) {
   out.append(" Definition");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_DEFINITION_DECLARATION_H1) {
      writer_ga_definition_declaration_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" :");
   if (node -> id == G_GA_TYPE) {
      writer_ga_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :=");
   if (node -> id == G_GA_TERM) {
      writer_ga_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" .");
}
void writer_ga_fixpoint_declaration_h2 (string &out, NODE *node) {
   if (node -> id == G_GA_ARGS) {
      writer_ga_args(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_fixpoint_declaration (string &out, NODE *node) {
   out.append(" Fixpoint");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_FIXPOINT_DECLARATION_H2) {
      writer_ga_fixpoint_declaration_h2(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" :");
   if (node -> id == G_GA_TYPE) {
      writer_ga_type(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :=");
   if (node -> id == G_GA_TERM) {
      writer_ga_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" .");
}
void writer_ga_args (string &out, NODE *node) {
   if (node -> id == G_GA_ARGS_PREV0) {
      writer_ga_args_prev0(out, node -> sub);
      return; }
   if (node -> id == G_GA_ARGS_PREV1) {
      writer_ga_args_prev1(out, node -> sub);
      return; }
}
void writer_ga_args_prev0 (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SI) { writer_si(out, node -> sub);if (node -> next != NULL) node = node -> next; }if (node -> id == G_SI) { writer_si(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" :");if (node -> id == G_GA_TYPE) { writer_ga_type(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_ga_args_prev1 (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_SI) { writer_si(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" :");if (node -> id == G_GA_TYPE) { writer_ga_type(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_ga_type (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_theorem_declaration (string &out, NODE *node) {
   if (node -> id == G_PDVL_THEOREM_DECLARATION_BODY) {
      writer_pdvl_theorem_declaration_body(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_theorem_declaration_body (string &out, NODE *node) {
   if (node -> id == G_PDVL_THEOREM_IDENTIFIER) {
      writer_pdvl_theorem_identifier(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" {");
   if (node -> id == G_PDVL_THEOREM_STATEMENT) {
      writer_pdvl_theorem_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" }");
}
void writer_pdvl_theorem_identifier (string &out, NODE *node) {
   if (node -> id == G_PDVL_THEOREM_IDENTIFIER_BY_NAME) {
      writer_pdvl_theorem_identifier_by_name(out, node -> sub);
      return; }
   if (node -> id == G_PDVL_THEOREM_SI) {
      writer_pdvl_theorem_si(out, node -> sub);
      return; }
}
void writer_pdvl_theorem_identifier_by_name (string &out, NODE *node) {
   out.append(" ");
   printLexNode(out, node);
}
void writer_pdvl_theorem_si (string &out, NODE *node) {
   out.append(" theorem");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_pdvl_theorem_statement (string &out, NODE *node) {
   if (node -> id == G_GA_HYPOTHESIS_STATEMENT) {
      writer_ga_hypothesis_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_THEOREM_STATEMENT) {
      writer_ga_theorem_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_ga_theorem_declaration (string &out, NODE *node) {
   out.append(" Theorem");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" :");
   if (node -> id == G_GA_HYPOTHESIS_STATEMENT) {
      writer_ga_hypothesis_statement(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_THEOREM_STATEMENT) {
      writer_ga_theorem_statement(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_ga_hypothesis_statement (string &out, NODE *node) {
   if (node -> id == G_GA_TERM) {
      writer_ga_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" =");
   if (node -> id == G_GA_TERM) {
      writer_ga_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" .");
}
void writer_ga_theorem_statement (string &out, NODE *node) {
   if (node -> id == G_GA_TERM) {
      writer_ga_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" .");
}
void writer_ga_term (string &out, NODE *node) {
   if (node -> id == G_GA_TERM_PREV0) {
      writer_ga_term_prev0(out, node -> sub);
      return; }
   if (node -> id == G_GA_TERM_PREV1) {
      writer_ga_term_prev1(out, node -> sub);
      return; }
   if (node -> id == G_GA_TERM_PREV2) {
      writer_ga_term_prev2(out, node -> sub);
      return; }
   if (node -> id == G_GA_TERM_PREV3) {
      writer_ga_term_prev3(out, node -> sub);
      return; }
}
void writer_ga_term_prev0_h0 (string &out, NODE *node) {
   out.append(" ,");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_term_prev0_h1 (string &out, NODE *node) {
   if (node -> id == G_GA_MATCH_TERM) {
      writer_ga_match_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_term_prev0 (string &out, NODE *node) {
   out.append(" match");
   if (node -> id == G_SI_NEST) {
      writer_si_nest(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_TERM_PREV0_H0) {
      writer_ga_term_prev0_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" with");
   while (node -> id == G_GA_TERM_PREV0_H1) {
      writer_ga_term_prev0_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
   out.append(" end");
}
void writer_ga_term_prev1 (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_GA_TERM) { writer_ga_term(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_ga_term_prev2_h2 (string &out, NODE *node) {
   if (node -> id == G_GA_TERM) {
      writer_ga_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_term_prev2 (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_TERM_PREV2_H2) {
      writer_ga_term_prev2_h2(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_ga_term_prev3_h3 (string &out, NODE *node) {
   if (node -> id == G_GA_TERM) {
      writer_ga_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_term_prev3 (string &out, NODE *node) {
   if (node -> id == G_SV_NUMBER) {
      writer_sv_number(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_TERM_PREV3_H3) {
      writer_ga_term_prev3_h3(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_si_nest (string &out, NODE *node) {
   if (node -> id == G_SI_NEST_PREV0) {
      writer_si_nest_prev0(out, node -> sub);
      return; }
   if (node -> id == G_SI_NEST_PREV1) {
      writer_si_nest_prev1(out, node -> sub);
      return; }
}
void writer_si_nest_prev0 (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" (");if (node -> id == G_SI_NEST) { writer_si_nest(out, node -> sub);if (node -> next != NULL) node = node -> next; }out.append(" )");
}
void writer_si_nest_prev1 (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_match_option (string &out, NODE *node) {
   if (node -> id == G_GA_MATCH_OPTION_PREV0) {
      writer_ga_match_option_prev0(out, node -> sub);
      return; }
   if (node -> id == G_GA_MATCH_OPTION_PREV1) {
      writer_ga_match_option_prev1(out, node -> sub);
      return; }
   if (node -> id == G_GA_MATCH_OPTION_PREV2) {
      writer_ga_match_option_prev2(out, node -> sub);
      return; }
}
void writer_ga_match_option_prev0_h0 (string &out, NODE *node) {
   if (node -> id == G_GA_MATCH_OPTION) {
      writer_ga_match_option(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_match_option_prev0 (string &out, NODE *node) {
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   while (node -> id == G_GA_MATCH_OPTION_PREV0_H0) {
      writer_ga_match_option_prev0_h0(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_ga_match_option_prev1_h1 (string &out, NODE *node) {
   if (node -> id == G_GA_MATCH_OPTION) {
      writer_ga_match_option(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_match_option_prev1 (string &out, NODE *node) {
   out.append(" _");
   while (node -> id == G_GA_MATCH_OPTION_PREV1_H1) {
      writer_ga_match_option_prev1_h1(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_ga_match_option_prev2_h2 (string &out, NODE *node) {
   if (node -> id == G_GA_MATCH_OPTION) {
      writer_ga_match_option(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_match_option_prev2 (string &out, NODE *node) {
   out.append(" ,");
   while (node -> id == G_GA_MATCH_OPTION_PREV2_H2) {
      writer_ga_match_option_prev2_h2(out, node -> sub);
      if (node -> next == NULL) break;
      node = node -> next; }
}
void writer_ga_match_term (string &out, NODE *node) {
   out.append(" |");
   if (node -> id == G_GA_MATCH_OPTION) {
      writer_ga_match_option(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
   out.append(" =>");
   if (node -> id == G_GA_TERM) {
      writer_ga_term(out, node -> sub);
      if (node -> next != NULL) node = node -> next; }
}
void writer_ga_term_args (string &out, NODE *node) {
   out.append(" (");if (node -> id == G_GA_TERM) { writer_ga_term(out, node -> sub);return; }out.append(" )");
   if (node -> id == G_SI) {
      writer_si(out, node -> sub);
      return; }
}
void printLexNode(string &out, NODE *node) {
   for (int cnt = 0; cnt < 4; cnt++) {
      char c = (node -> id >> (8 * cnt)) & 0xff;
      if ( ( (c >= 'a') & (c <= 'z') ) | ( (c >= 'A') & (c <= 'Z') ) | ( (c >= '0') & (c <= '9') ) | (c == '_') | (c == '$')) out.append(1u, c); }
   if (node -> next != NULL) printLexNode(out, node -> next); }

void writer_clear_space (string &out, size_t pos) {
   pos = out.find(" ", pos);
   while (pos != std::string::npos) {
      out.replace(pos, 1, "");
      pos = out.find(" ", pos); } }

