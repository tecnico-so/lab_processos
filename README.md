# Guião sobre programação com processos

![IST](img/IST_DEI.png)

## Objetivos

No final deste guião, deverá ser capaz de:

* criar processos utilizando `fork` e esperar pela sua terminação utilizando `wait`;
* executar outros programas utilizando funções da família `exec`.

## Introdução

Um processo é uma instância de um programa em execução.

Cada processo possui, entre outros elementos, um identificador de processo (PID, *process identifier*), um estado de execução e um espaço de endereçamento.

Um processo pode criar um novo processo através de `fork`.

Depois de uma chamada bem-sucedida, existem dois processos: o processo pai e o processo filho.
Ambos continuam a executar a partir da instrução seguinte à chamada, mas recebem valores de retorno diferentes e passam a executar de forma independente.

Quando o processo pai precisa de esperar pela terminação de um processo filho, deve utilizar `wait`.
Esta função permite também obter informação sobre o estado de terminação do processo filho.

Por sua vez, a família de funções `exec` permite substituir o programa executado por um processo por outro programa executável.

Neste guião, irá acompanhar esta progressão através de três exemplos:

* `fork.c`, que cria um processo filho;
* `forkwait.c`, que acrescenta a espera pela terminação do filho;
* `forkexec.c`, que executa outro programa no processo filho.

Em cada exemplo, observe o código, execute o programa e responda às questões propostas.

### Antes de começar

Para realizar os exemplos e o exercício, vai precisar de um sistema operativo compatível com a norma POSIX (*Portable Operating System Interface*), de preferência um sistema Unix, como o Ubuntu Linux.

Se ainda não tiver um sistema deste tipo disponível no seu computador pessoal, pode utilizar um dos computadores do laboratório.

Para obter os exemplos de código, clone o repositório usando o comando:

```console
git clone https://github.com/tecnico-so/lab_processos.git
```

Ao longo do guião, poderá ser útil observar os processos em execução.

O comando `ps` apresenta informação sobre os processos associados ao terminal atual (`-f` é *full format*):

```console
ps -f
```

O comando `pstree` apresenta os processos organizados em árvore, tornando mais fácil observar as relações entre processos pai e filho:

```console
pstree
```

## 1. Criar um processo filho

Comece por observar o ficheiro [`fork.c`](fork/fork.c).

O programa chama [`fork`](https://man7.org/linux/man-pages/man2/fork.2.html) para criar um novo processo.

A partir dessa chamada, o processo pai e o processo filho continuam a executar o mesmo código, mas o valor devolvido por `fork` permite distinguir os dois processos.

No processo filho, as variáveis `idata` e `istack` são multiplicadas por três.

No processo pai, o programa espera alguns segundos antes de continuar.

Observe o código.

Compile e execute o programa:

```console
cd fork
make
./fork
```

Execute o programa várias vezes e compare os resultados.

Responda:

**a)** Quantos processos se executam a seguir a uma chamada bem-sucedida a `fork`?

**b)** Que valor é devolvido por `fork` no processo filho? E no processo pai? Que valor indica que ocorreu um erro?

**c)** Que valores de `idata` e `istack` são apresentados pelo processo filho? Que valores das mesmas variáveis são apresentados pelo processo pai?

**d)** Qual é a finalidade da chamada a `sleep` neste exemplo?

## 2. Esperar pelo processo filho

Observe agora o ficheiro [`forkwait.c`](fork/forkwait.c).

A estrutura geral do programa é semelhante à do exemplo anterior, mas o processo pai deixa de utilizar `sleep` e passa a utilizar [`wait`](https://man7.org/linux/man-pages/man2/wait.2.html).

Compile e execute o programa.

**a)** O que acontece ao processo pai enquanto o processo filho ainda não terminou?

**b)** A linha final produzida pelo processo pai pode aparecer antes da linha final produzida pelo processo filho?

**c)** Qual é a diferença essencial entre utilizar `sleep` e utilizar `wait` neste caso?

## 3. Executar outro programa

Observe o ficheiro [`forkexec.c`](fork/forkexec.c).

Neste exemplo, o processo pai continua a criar um filho com `fork`, mas o processo filho passa a executar outro programa através de uma função da família [`exec`](https://man7.org/linux/man-pages/man3/exec.3.html).
Neste caso, é utilizada a função `execl`, que recebe os argumentos do novo programa individualmente:

```c
execl("/bin/ls", "ls", "-la", (char *) NULL);
```

faz com que o processo filho passe a executar o programa `/bin/ls` com a opção `-la`.
O NULL é interpretado como um terminador.

O processo pai utiliza [`waitpid`](https://man7.org/linux/man-pages/man2/waitpid.2.html) para esperar especificamente pela terminação do processo filho criado por este `fork`[^wmacros].

[^wmacros]: As *macros* `WIFEXITED(status)` permitem verificar, respetivamente, se o processo filho terminou normalmente e qual foi o seu código de saída.
Estão documentadas em [`wait(2)`](https://man7.org/linux/man-pages/man2/wait.2.html).

Observe o código e compare-o com os dois exemplos anteriores.

**a)** Que processo executa a chamada a `execl`?

**b)** O que acontece ao programa anteriormente executado pelo processo filho quando `execl` é bem-sucedido?

**c)** O PID do processo filho muda depois de uma chamada bem-sucedida a `execl`?

**d)** O processo pai termina antes ou depois do comando `ls -la`?

---

## Mini-exercício

***Multi File Checker***

Pretende-se implementar um programa que processe vários ficheiros recorrendo a processos distintos.
O programa chama-se `mfcheck` que abrevia ***m**ulti* ***f**ile* ***check**er*.

Ao longo deste exercício, o programa será construído progressivamente.

### 1. Criar um processo

Implemente o programa `mfcheck.c`, que recebe o nome do ficheiro a processar:

```console
./mfcheck names.txt
```

O programa deverá criar um processo filho com [`fork`](https://man7.org/linux/man-pages/man2/fork.2.html).

O processo filho deverá apresentar:

```text
Getting ready to process names.txt...
```

Depois disso, deverá esperar cinco segundos com [`sleep`](https://man7.org/linux/man-pages/man3/sleep.3.html) e terminar.

O processo pai deverá apresentar o seu PID e esperar pela terminação do filho.

### 2. Executar comando existente em vez do código à medida

O comando ***w**ord **c**ount*:

```console
wc -l names.txt
```

permite também contar as linhas de um ficheiro, escrevendo depois o número e o nome do ficheiro.

Modifique o processo filho para executar `wc -l` através de uma função da família [`exec`](https://man7.org/linux/man-pages/man3/exec.3.html).

Garanta também que uma falha de `exec` é corretamente tratada.

### 3. Processar vários ficheiros

Generalize o programa para aceitar vários ficheiros:

```console
./mfcheck Lusiadas.txt nomes.txt names.txt
```

Crie um processo filho por ficheiro.

Todos os filhos devem ser criados antes de o processo pai começar a esperar pela sua terminação.

A ordem dos resultados não tem de coincidir com a ordem dos argumentos.

O processo pai **não** deverá receber o número de palavras produzido por `wc`.
Deverá apenas determinar se cada filho terminou com sucesso.

No final de tudo, o pai deve apresentar um resumo:

```text
3 files
2 succeeded
1 failed
```

Teste também com ficheiros inexistentes.

---

O resto do enunciado será entregue no início da aula e estenderá a solução desenvolvida até este ponto.

### Avaliação em aula

Quando tiver concluído o exercício, chame o docente do laboratório, para que possa demonstrar a solução em execução e responder a perguntas sobre a implementação.

**A avaliação é presencial e individual.**

Não basta que o código funcione, é necessário saber explicar como foi implementado e por que funciona.

Podem também ser pedidas modificações de pormenor no momento.

---

## Conclusão

Um processo criado por `fork` começa com uma cópia do estado do processo que o criou, mas executa num espaço de endereçamento separado.
Assim, alterações à memória do processo filho não afetam a memória do processo pai.

Quando precisa de aguardar pela terminação de um processo filho, o processo pai deve utilizar uma operação de espera, como `wait` ou `waitpid`.

As funções da família `exec` permitem substituir o programa executado por um processo, mantendo o próprio processo e, consequentemente, o respetivo PID.

Estes mecanismos estão na base da implementação de *shells* e servidores e permitem distribuir trabalho por vários processos, explorando concorrência e, quando existem recursos de processamento suficientes, paralelismo.

---

Contactos para sugestões ou correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt).
