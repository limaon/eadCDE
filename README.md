#### Sobre o Projeto
Este projeto tem como objetivo desenvolver um Sistema de Controle de Estoque em linguagem C, proporcionando uma experiência prática de aplicação dos conhecimentos adquiridos em programação. O sistema visa fornecer uma solução eficiente para empresas gerenciarem seus estoques, automatizando processos relacionados à gestão de produtos.

#### Funcionalidades
- **Gestão de Estoque:** Adicione, atualize, exclua e visualize itens no estoque.
- **Menu de Ações:** Navegue por um menu interativo para gerenciar o estoque.
- **Tratamento de Dados:** As informações dos produtos são processadas e validadas antes de serem armazenadas.
- **Validação de Entradas:** O sistema verifica a validade das entradas do usuário, garantindo a robustez.
- **Estrutura de Dados:** Utilização de pilhas e filas para armazenar dados de estoque.

#### Como Usar
1. Clone o repositório para sua máquina local.
2. Compile o código usando um compilador C de sua escolha. Se disponível, use o Makefile fornecido para compilação automática.
3. Execute o programa compilado e siga as instruções do menu para gerenciar o estoque.

#### Requisitos
- Compilador C (GCC recomendado)
- Sistema operacional compatível (Linux, macOS, Windows via WSL ou Cygwin)

#### Compilação e Execução
```bash
gcc -o controle_estoque main.c funcoes.c -I.
./controle_estoque
```

ou

```bash
make ; ./estoque
```

### TODO

- [ ] **Implementação das Estruturas de Dados:**
  - [ ] Definir e implementar a pilha para armazenamento dos produtos.
  - [ ] Definir e implementar a fila para operações de estoque.
- [ ] **Desenvolvimento das Funcionalidades:**
  - [ ] Implementar a adição de itens ao estoque.
  - [ ] Implementar a visualização do estoque.
  - [ ] Implementar a atualização de informações de itens.
  - [ ] Implementar a exclusão de itens do estoque.
- [ ] **Validação e Tratamento de Entradas:**
  - [ ] Implementar a validação de entradas do usuário.
  - [ ] Implementar o tratamento de entradas inválidas.
- [ ] **Alocação Dinâmica de Memória:**
  - [ ] Utilizar alocação dinâmica para a gestão eficiente da memória.
- [ ] **Testes:**
  - [ ] Desenvolver testes para validar as funcionalidades do sistema.
- [ ] **Documentação:**
  - [ ] Atualizar o README.md com detalhes específicos de implementação.
  - [ ] Documentar as funções e estruturas de dados utilizadas.
