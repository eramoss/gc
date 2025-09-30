#include "dsun.h"

#include "Lexico.h"
#include "Semantico.h"
#include "Sintatico.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string readFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Não foi possível abrir o arquivo: " + filename);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_code>" << std::endl;
    return 1;
  }

  std::string input_code;
  try {
    input_code = readFile(argv[1]);
  } catch (const std::runtime_error &e) {
    std::cerr << "Erro: " << e.what() << std::endl;
    return 1;
  }

  Lexico lexico;
  Sintatico sintatico;
  Semantico semantico;

  lexico.setInput(input_code.c_str());

  try {
    sintatico.parse(&lexico, &semantico);

    std::cout << "\n--- SUCESSO ---\n"
              << "Análise e Interpretação concluídas." << std::endl;

  } catch (const LexicalError &e) {
    std::cerr << "\n--- ERRO LÉXICO ---\n"
              << "Posição: " << e.getPosition()
              << "\nMensagem: " << e.getMessage() << std::endl;
  } catch (const SyntacticError &e) {
    std::cerr << "\n--- ERRO SINTÁTICO ---\n"
              << "Posição: " << e.getPosition()
              << "\nMensagem: " << e.getMessage() << std::endl;
  } catch (const SemanticError &e) {
    std::cerr << "\n--- ERRO SEMÂNTICO ---\n" << e.getMessage() << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "\n--- ERRO INESPERADO ---\n" << e.what() << std::endl;
  }

  return 0;
}
