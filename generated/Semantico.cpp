#include "Semantico.h"
#include "SemanticError.h"
#include <bitset>
#include <cmath>
#include <iostream>

max_int Semantico::pop_stack() {
  if (stack.empty()) {
    throw SemanticError("Erro: pilha de calculo vazia what have you done?");
  }
  max_int value = stack.back();
  stack.pop_back();
  return value;
}

void Semantico::executeAction(int action, const Token *token) {
  max_int val1, val2, result;
  std::string lexeme = token->getLexeme();

  switch (action) {

  case 99: {
    id_ = lexeme;
    break;
  }

  case 0: {
    result = pop_stack();

    if (id_.empty()) {
      throw SemanticError("Erro: sem id para atribuir o valor no assing");
    }

    symbols[id_] = result;

    id_.clear();
    break;
  }

  case 1: {
    if (symbols.count(lexeme) == 0) {
      throw SemanticError("Erro: variavel '" + lexeme + "' não existe bro");
    }
    stack.push_back(symbols[lexeme]);
    break;
  }
  case 2: {
    try {
      max_int bin_val = std::stoll(lexeme, nullptr, 2);
      stack.push_back(bin_val);
    } catch (const std::exception &e) {
      throw SemanticError("Erro: binario muito grande ou invalido");
    }
    break;
  }

  case 3:
  case 4: {
    val2 = pop_stack();
    val1 = pop_stack();
    result = (action == 3) ? (val1 + val2) : (val1 - val2);
    stack.push_back(result);
    break;
  }

  case 5:
  case 6: {
    val2 = pop_stack();
    val1 = pop_stack();
    if (action == 6 && val2 == 0.0) {
      throw SemanticError("Erro: divisão por zero oh no");
    }
    result = (action == 5) ? (val1 * val2) : (val1 / val2);
    stack.push_back(result);
    break;
  }

  case 7: {
    val2 = pop_stack();
    val1 = pop_stack();
    stack.push_back(std::pow(val1, val2));
    break;
  }

  case 8: {
    if (f_args.size() != 2) {
      throw SemanticError("Erro: log precisa de 2 argumentos, "
                          "Foram fornecidos " +
                          std::to_string(f_args.size()) + ".");
    }
    val2 = f_args.back();
    f_args.pop_back();
    val1 = f_args.back();
    f_args.pop_back();

    if (val2 <= 0) {
      throw SemanticError("Erro: dominio invalido prolog (val < 0)");
    }
    if (val1 <= 0 || val1 == 1) {
      throw SemanticError("Erro: base invalida prolog (deve ser > 0 e != 1)");
    }

    result = std::log(val1) / std::log(val2);

    stack.push_back(result);
    break;
  }

  case 10: {
    if (f_args.empty()) {
      throw SemanticError("Erro: PRINT requer pelo menos 1 argumento.");
    }

    for (size_t i = 0; i < f_args.size(); ++i) {
      std::string p = "";
      if (print_type == "base2") {
        p = std::bitset<64>(f_args[i]).to_string();
        p.erase(0, p.find_first_not_of('0'));
      } else if (print_type == "base10") {
        p = std::to_string(f_args[i]);
      } else {
        std::cerr << "-p não aceito [base2, base10]: " + print_type
                  << std::endl;
        exit(1);
      }

      std::cout << p;
      if (i < f_args.size() - 1) {
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
    break;
  }

  case 100: {
    f_args.clear();
    break;
  }
  case 101: {
    max_int arg = pop_stack();
    f_args.push_back(arg);
    break;
  }

  default:
    break;
  }
}
