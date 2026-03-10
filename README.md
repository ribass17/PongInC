# PongInC

Projeto Pong em C usando SDL2.

## Como executar localmente

```bash
make run
```

## Testes

O projeto possui um teste de build que valida se o binário é gerado corretamente:

```bash
make test
```

## CI/CD

Pipeline GitHub Actions em `.github/workflows/ci-cd.yml`:

- **CI**: instala dependências e executa `make test` em pushes/PRs para `main`.
- **CD**: em tags `v*`, compila o jogo e publica um artefato zipado com o binário.
