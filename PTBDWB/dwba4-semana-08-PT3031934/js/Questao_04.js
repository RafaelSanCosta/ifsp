class Aluno{
    constructor(primeiroNome, segundoNome, primeiraNota, segundaNota)
    {
    this.primeiroNome = primeiroNome;
    this.segundoNome = segundoNome;
    this.primeiraNota = primeiraNota;
    this.segundaNota = segundaNota;
    }

    nomeCompleto(){
        return this.primeiroNome + " " + this.segundoNome;
    }

    media(){
        return ((this.primeiraNota * 0.6) + (this.segundaNota * 0.4)).toPrecision(2);
    }

    situacao(){
        if(this.media()>6){
            return "Aprovado"
        } else {
            return "Reprovado"
        }
    }
}

const aluno1 = new Aluno("Light", "Yagami", 10.0, 9.8);
const aluno2 = new Aluno("Naruto", "Uzumaki", 6.0, 6.5); 
const aluno3 = new Aluno("Sasuke", "Uchiha", 8.5, 9.0); 
const aluno4 = new Aluno("Edward", "Elric", 9.5, 9.2);  
const aluno5 = new Aluno("Monkey D.", "Luffy", 5.0, 4.5);    

let alunos = [aluno1, aluno2, aluno3, aluno4, aluno5];

/*
let text = "<ul>";
alunos.forEach(listaDeAlunos);
text += "</ul>";

document.getElementById("demo").innerHTML = text;

function listaDeAlunos(value) {
  text += "<li>" + value.toString() + "</li>";
} 
*/
//vi isso no w3schools e n funcionou

function mostrarAlunos(vetor) {
    alert("Nome Completo: "alunos[i].nomeCompleto() + 
    " | Media: " + alunos[i].media() + 
    " | Situação: " + alunos[i].situacao());
}

let text = "<p>";

for(var i=0; i<alunos.length;i++){
    text += alunos[i].nomeCompleto() + 
    " | Media: " + alunos[i].media() + 
    " | Situação: " + alunos[i].situacao() + 
    "<br>";

    mostrarAlunos(alunos[i]);
}

text += "</p>";
document.getElementById("demo").innerHTML = text;
