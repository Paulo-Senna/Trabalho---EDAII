import pandas as pd
import matplotlib.pyplot as plt

def plotar_graficos():
    # 1. Carregar os dados dos arquivos CSV
    # Certifique-se de que os nomes dos arquivos e colunas correspondem aos seus dados
    try:
        df_insercao = pd.read_csv('resultado_insercao.csv')
        df_remocao = pd.read_csv('resultado_remocao.csv')
    except FileNotFoundError:
        print("Erro: Arquivos CSV não encontrados na pasta atual.")
        return

    # Definir as cores e estilos para padronizar as 5 linhas
    estilos = {
        'AVL': {'label': 'Árvore AVL', 'color': 'blue', 'linestyle': '-'},
        'RB': {'label': 'Árvore Rubro-Negra', 'color': 'red', 'linestyle': '-'},
        'B1': {'label': 'Árvore B (Ordem 1)', 'color': 'green', 'linestyle': '--'},
        'B5': {'label': 'Árvore B (Ordem 5)', 'color': 'orange', 'linestyle': '--'},
        'B10': {'label': 'Árvore B (Ordem 10)', 'color': 'purple', 'linestyle': '--'}
    }

    # ==========================================
    # GRÁFICO 1: Operação de Adição (Inserção)
    # ==========================================
    plt.figure(figsize=(10, 6))
    
    for coluna, config in estilos.items():
        plt.plot(df_insercao['n'], df_insercao[coluna], 
                 label=config['label'], color=config['color'], 
                 linestyle=config['linestyle'], linewidth=2)

    plt.title('Complexidade Algorítmica - Operação de Adição', fontsize=14, fontweight='bold')
    plt.xlabel('Tamanho do Conjunto de Dados (1 a 10000)', fontsize=12)
    plt.ylabel('Esforço Computacional', fontsize=12)
    plt.legend(title='Estruturas de Dados')
    plt.grid(True, linestyle=':', alpha=0.7)
    
    # Salvar e mostrar o gráfico
    plt.tight_layout()
    plt.savefig('grafico_adicao.png', dpi=300) # Salva o gráfico em alta resolução
    plt.show()

    # ==========================================
    # GRÁFICO 2: Operação de Remoção
    # ==========================================
    plt.figure(figsize=(10, 6))
    
    for coluna, config in estilos.items():
        plt.plot(df_remocao['n'], df_remocao[coluna], 
                 label=config['label'], color=config['color'], 
                 linestyle=config['linestyle'], linewidth=2)

    plt.title('Complexidade Algorítmica - Operação de Remoção', fontsize=14, fontweight='bold')
    plt.xlabel('Tamanho do Conjunto de Dados (1 a 10000)', fontsize=12)
    plt.ylabel('Esforço Computacional', fontsize=12)
    plt.legend(title='Estruturas de Dados')
    plt.grid(True, linestyle=':', alpha=0.7)
    
    # Salvar e mostrar o gráfico
    plt.tight_layout()
    plt.savefig('grafico_remocao.png', dpi=300) # Salva o gráfico em alta resolução
    plt.show()

if __name__ == "__main__":
    plotar_graficos()