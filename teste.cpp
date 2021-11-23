#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

class Forca{
public:
	enum Dificuldade
	{
		FACIL,
		MEDIO,
		DIFICIL
	};

private:
	//TODO: armazenar os scores?

	std::vector<std::pair<std::string, int>> m_palavras; //<! palavras e sua ocorrência no Corpus

	std::string m_arquivo_scores; //<! nome do arquivo contendo os scores

	std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras

	Dificuldade d = Dificuldade::FACIL; //<! dificuldade do jogo

	std::string m_palavra_atual; //<! palavra sendo testada atualmente

	int m_tentativas_restantes = 6; //<! tentativas restantes

public:
	/**
         * Cria a classe Forca
         * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com 
         * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
         * ou scores inválidos, use o método eh_valido.
         * @param palavras o arquivo que contém as palavras
         * @param scores o nome do arquivo que contém os scores
         * @see eh_valido 
         */
	Forca(std::string palavras_path, std::string scores_path){
		m_arquivo_palavras = palavras_path;
		m_arquivo_scores = scores_path;
		// check if files exists
		ifstream arquivo_palavras(m_arquivo_palavras);
		ifstream arquivo_scores(m_arquivo_scores);
		if(!arquivo_palavras.is_open() || !arquivo_scores.is_open()){
			throw "Arquivo não encontrado";
		}
	}

	/**
	 * Carrega e valida as palavras do arquivo de palavras e do arquivo de scores
	 * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
	 * razão correspondente de acordo com as especificações.
	 * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
	 */
	std::pair<bool, std::string> carrega_e_valida()
	{
		ifstream palavrasArq = ifstream(m_arquivo_palavras);
		ifstream scoresArq = ifstream(m_arquivo_scores);
		auto ispalavra = [](char c)
		{ return isalpha(c) || c == '-'; };
		pair<string, int> palavra;
		vector<pair<string, int>> dicionario;
		string linha;
		while (getline(palavrasArq, linha)){
			stringstream ss(linha);
			string p;
			ss >> p;
			if (p.size() >= 4 && all_of(p.begin(), p.end(), ispalavra)){
				palavra.first = p;
				string str_nivel;
				ss >> str_nivel;
				if (stoi(str_nivel) > 0){
					palavra.second = stoi(str_nivel);
					dicionario.push_back(palavra);
				}else{
					return {false, "Erro: Arquivo de Palavras inválido, algum nível está abaixo de 0."};
				}
			}else{
				return {false, "Erro: Arquivo de Palavras inválido, alguma palavra não possúi mais de 4 caracteres ou possúi caractere inválido."};
			}
		}
		palavrasArq.close();
		m_palavras = dicionario;

		while (getline(scoresArq, linha)){
			stringstream ss(linha);
			string line = ss.str();
			int count = 0;
			for (int i = 0; (i = s.find(';', i)) != std::string::npos; i++){
				count++;
			}
			if (count != 3){
					return {false, "Erro: Arquivo de Scores inválido, alguma linha possui mais ou menos de 3 pontuações."};
			}
		}

		return {true, ""};
	}


	/**
         * Modifica a dificuldade do jogo.
         * De acordo com a dificuldade configurada, o método proxima_palavra retornará palavras
         * diferentes.
         * @param d a dificuldade desejada
         * @see proxima_palavra
         */
	void set_dificuldade(Dificuldade d){
		this->d = d;
	}

	/**
         * Retorna a próxima palavra de acordo com a dificuldade atual.
         * Este método deve atualizar o atributo m_palavra_atual e retornar a palavra um texto no formato
         * "_ _ _ _ ... _" dependendo do tamanho de m_palavra_atual. O método também deve sortear as 
         * letras que devem aparecer dependendo do nível de dificuldade.
         * @return a próxima palavra do conjunto de palavras disponível de acordo com a dificuldade atual.
         */
	std::string proxima_palavra(){
		int media = 0;
		for (auto palavra : m_palavras){
			media += palavra.second;
		}
		media /= m_palavras.size();

		int palavra_escolhida = rand() % m_palavras.size();
		if (this->d == FACIL){
			while (m_palavras[palavra_escolhida].second < media)
			{
				int palavra_escolhida = m_palavras[rand() % m_palavras.size()].first;
			}
		}
		else if (this->d == MEDIO){
			while (m_palavras[palavra_escolhida].second < media)
			{
				int palavra_escolhida = m_palavras[rand() % m_palavras.size()].first;
			}
		}
		else if (this->d == DIFICIL){
			while (m_palavras[palavra_escolhida].second >= media)
			{
				int palavra_escolhida = m_palavras[rand() % m_palavras.size()].first;
			}
		}
	}	

	/**
         * Retorna a palavra atual que está sendo jogada.
         * @return o valor do atributo m_palavra_atual.
         */
	std::string get_palavra_atual();

	/**
         * Testa se uma letra pertence á palavra atual, retorna T se a letra pertence.
         * Este método testa se uma letra pertence à palavra atual e retorna True caso pertença. 
         * Caso contrário, o método deve atualizar o atributo m_tentativas_restantes, decrementando 
         * em 1, e retornar False.
         * @param palpite uma letra, que deve ser testada se pertence à palavra.
         * @return T se a palpite pertence à palavra, F caso contrário.
         */
	bool palpite(std::string palpite);

	/**
         * Em caso de Game Over este método deve retornar T.
         * @return T caso o m_tentativas_restantes do jogo esteja igual a 0, F caso contrário.
         */
	bool game_over();

	/**
         * Atualiza o número de tentativas restantes.
         * Este método é útil no caso do jogador escolher continuar o jogo.
         * @param tentativas atualiza o valor da variável m_tentativas_restantes.
         */
	void set_tentativas_restantes(int tentativas){
		this->tentativas_restantes = tentativas;
	}

	/**
         * Retorna a quantidade de tentativas restantes.
         * @return a quantidade de tentativas restantes.
         */
	int get_tentativas_restantes(){
		return m_tentativas_restantes;
	}

}


int main(int argc, const char **argv){
	return 0;
}