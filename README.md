# Arvore-B
## Descrição das Pastas
- **input:** Um arquivo com várias entradas desorganizadas que vai ser processado pela árvore.
- **output:** Diretório de resultados (a árvore organizada e talvez os resultados de outras aplicações).
- **resources:** Recursos necessários para os programas, como bibliotecas personalizadas.
- **sideapps:** Para programas que não são a árvore em si, como medidores de desempenho ou geradores de entrada.
- **tree:** Código da Árvore-B.

## Dentro dessa pasta: 
Arquivos permitidos dentro dessa pasta:
- Makefile.
- Arquivos específicos do git (como esse aqui).

## Compatibilidade Multi-sistema
A util "RegisterMaker" só funciona em sistemas UNIX devido ao uso implementado de random() e time().

## Outros
Usar `make clean` antes de sincronizar o diretório com o github ou o cão puxa o seu pé de noite.