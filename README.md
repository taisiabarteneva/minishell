# minishell :shell:

School 42 team project (teammate [desssai](https://github.com/desssai)). Implementation of a command-line shell

For more detailed info about the projects see `subject.pdf` in the root of the repository 

## Implemented features
- Redirection `>` `<` `>>` `<<`
- Pipes `|`
- Signals handler `Ctrl-C` `Ctrl-D` `Ctrl-\` `Ctrl-Z`
- Built-ins 
  - echo
  - pwd
  - cd
  - export
  - unset
  - env
  - exit
- Accurate status codes and error messages
- Environment variables handler
- Executables based on `PATH` environment variable or relative/absolute path
- History of commands
- Wildcard matching `*`
- `readline` library used

## How to run
Compile and launch using
```
$ make
```

## Example

![188963179-d2b65c84-9175-4fc3-b1e0-fed7eba9e3d6](https://user-images.githubusercontent.com/95509213/189460555-c1f2c57a-23f5-4f70-a623-ab311fac8173.gif)

