import aluno as a;
import turma as t;

alunos = []
alunos.append(a.Aluno('Fabio', 'Teixeira', 11));
alunos.append(a.Aluno('Fabiano', 'Teixeira', 7));
alunos.append(a.Aluno('Melissa', 'Teixeira', 8));
alunos.append(a.Aluno('Rafael', 'Teixeira', 9));
alunos.append(a.Aluno('Angela', 'Teixeira', 6));

turmaObject = t.Turma();
turmaObject.cadastrarAlunos(alunos);

turmaObject.mostrarAlunos();
print('*'*30)
print('Aluno com menor nota:', turmaObject.menorNota.mostrarAluno())
print('Aluno com maior nota:', turmaObject.maiorNota.mostrarAluno())
turmaObject.maiorNota.mostrarAluno();
