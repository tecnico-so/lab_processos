# Guião sobre programação com processos

![IST](img/IST_DEI.png)  

## Objetivos

No final deste guião, deverá ser capaz de:

* criar processos utilizando `fork` e esperar pela sua terminação utilizando `wait`;
* executar outros programas com `exec`.

## Introdução

Muitos programas precisam de executar várias funções ao mesmo tempo.
Por exemplo, uma aplicação pode estar a processar dados enquanto recebe novos comandos, outra pode querer dividir um cálculo entre vários processadores para chegar mais depressa ao resultado pretendido.
Um servidor pode querer atender vários pedidos ao mesmo tempo.

Os processos, pelo contrário, possuem espaços de endereçamento separados. 
Depois de criar um novo processo, as alterações efetuadas na memória de um processo não modificam a memória do outro.

Neste guião vamos estudar exemplos de código e depois teremos um exercício.

### Antes de começar

Para os exemplos e o exercício vai precisar de um sistema operativo compatível com POSIX, de preferência um Unix, como o Ubuntu Linux ou outro.
Se ainda não o tiver disponível no seu computador pessoal, pode utilizar um dos computadores do laboratório.

Para obter os exemplos de código, clone este repositório, usando o comando: ``git clone https://github.com/tecnico-so/lab_processos.git``


## 1. Processos

Componha um programa paralelo `process.c` em que usa `fork` e `wait` para criar um processo filho a partir do processo atual.
Depois, tenha o cuidado de assegurar que a função `wait` só é chamada pelo processo pai, para esperar a terminação do filho.

Neste caso, a concorrência e paralelismo acontecerá com processos distintos.
Qual é o resultado impresso no terminal?

Crie um novo programa, `process.c`, inicialmente tão simples quanto possível.

O programa deverá criar um processo filho utilizando `fork`.

### 1.1. A função `fork`

Consulte a documentação de [`fork`](https://man7.org/linux/man-pages/man2/fork.2.html):

```console
man 2 fork
```

Responda:

**a)** Quantos processos continuam a executar o código depois de uma chamada a `fork` que termine com sucesso?

**b)** Que valor é devolvido por `fork` no processo filho?

**c)** Que valor é devolvido no processo pai?

**d)** Que valor indica um erro?

### 1.2. Identificar pai e filho

Utilize `getpid()` para obter o identificador de cada processo.

Pode também utilizar `getppid()` para obter o identificador do processo pai.

Modifique o programa para que cada processo apresente uma linha semelhante a:

```text
processo 1234, pai 1200
```

Execute o programa várias vezes.

**a)** Identifique qual das linhas foi produzida pelo processo original e qual foi produzida pelo processo filho.

**b)** A ordem das duas linhas é sempre a mesma?

**c)** O processo pai pode assumir que executa primeiro apenas porque foi ele que chamou `fork`?

### 1.3. Esperar pela terminação de processos

O processo pai pode utilizar `wait` para esperar pela terminação de um dos seus processos filhos.

Consulte a documentação de [`wait`](https://man7.org/linux/man-pages/man2/wait.2.html):

```console
man 2 wait
```

Modifique `process.c` para que:

1. o processo pai crie um processo filho;
2. o filho apresente uma mensagem e termine;
3. o pai chame `wait`;
4. o pai apresente uma mensagem apenas depois de `wait` terminar.

Execute o programa várias vezes.

Confirme que a mensagem final do pai aparece sempre depois da mensagem produzida pelo filho.


## Conclusão

Um processo criado por `fork` começa com um estado derivado do processo que o criou, mas executa num espaço de endereçamento separado. 
Alterações posteriores à memória do filho não alteram a memória do pai.

O processo pai pode utilizar `wait` para esperar pela terminação de um processo filho.

----

Contactos para sugestões/correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt)
