#include "turma.h"


Turma::Turma()
{

}

void Turma::inserirAluno(Aluno a)
{

    turma.push_back(a);
}
QVector<Aluno> Turma::getTurma(){
    return turma;
}
void Turma::Remove(int index)
{
    turma.remove(index);
}
Aluno Turma::operator[](int i)
{
    return turma[i];
}

int Turma::getMedia()
{
    int media = 0;
    for(Aluno a : turma){
        media+=a.getMedia();
    }
    return media/turma.size();
}

int Turma::getMaiorMedia()
{
    Aluno *menor = std::min_element(turma.begin(),turma.end(),compararPorMedia);

    return menor->getMedia();
}

int Turma::getMenorMedia()
{
    Aluno *maior = std::max_element(turma.begin(),turma.end(),compararPorMedia);
    return maior->getMedia();
}
bool Turma::ProcuraNome(Aluno aluno)
{

    bool aux = false;

    for(int i = 0; i < turma.size(); i++)
        if(aluno.getNome() == turma[i].getNome()){
            aux = true;
        }
    return aux;
    //return std::find(turma.constBegin(),turma.constEnd(),aluno) == turma.constEnd();
}
void Turma::ordenarPorNome()
{
    std::sort(turma.begin(),turma.end(),compararPorNome);
}

void Turma::ordenarPorMedia()
{
    std::sort(turma.begin(),turma.end(),compararPorMedia);
}

int Turma::size()
{
    return turma.size();
}

bool Turma::salvarTurma(QString arquivo)
{
    QFile file(arquivo);
    QString linha;
    if(!file.open(QIODevice::WriteOnly))
        return false;

    for(Aluno a : turma){
        linha = a.getNome() + ',' + QString::number(a.getMedia()) + '\n';
        file.write(linha.toLocal8Bit());
    }
    return true;

}

bool Turma::carregarTurma(QString arquivo)
{
    QFile file(arquivo);
    if(!file.open(QIODevice::ReadOnly))
        return false;

    QString linha;
    Aluno a;
    while(!file.atEnd()){
        linha = file.readLine();
        QStringList dados = linha.split(",");
        a.setNome(dados[0]);
        a.setMedia(dados[1].toDouble());
        inserirAluno(a);
    }
    return true;
}

bool compararPorMedia(Aluno a, Aluno b)
{
    return a.getMedia()>b.getMedia();
}
bool compararNome(Aluno a, Aluno b){
    return a.getNome()==b.getNome();
}
bool compararPorNome(Aluno a, Aluno b)
{
    return a.getNome()<b.getNome();
}
