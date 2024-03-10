import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Iterator;
import java.util.Scanner;
import java.util.HashMap;
import java.util.Map;

// Classe para definir uma equipe de personagens
class Equipe {
    private List<Personagem> personagens;

    public Equipe() {
        this.personagens = new ArrayList<>();
    }

    // Método para adicionar um personagem à equipe
    public void adicionarPersonagem(Personagem personagem) {
        personagens.add(personagem);
    }

    // Método para buscar um personagem na equipe pelo ID
    public Personagem buscarPersonagemPorID(int ID) {
        for (Personagem personagem : personagens) {
            if (personagem.getID() == ID) {
                return personagem;
            }
        }
        return null;
    }

    // Método para retornar todos os personagens da equipe
    public List<Personagem> getPersonagens() {
        return personagens;
    }

    // Método para computar pontos de experiência para a equipe
    public void ganharPEEquipe(int nivelInimigo) {
        for (Personagem personagem : personagens) {
            personagem.ganharPE(nivelInimigo);
        }
    }

    // Método para determinar o próximo atacante da equipe
    public Personagem proximoAtacante() {
        Personagem proximo = null;
        int menorTempo = Integer.MAX_VALUE;
        for (Personagem personagem : personagens) {
            if (personagem.getTempoEspera() < menorTempo) {
                menorTempo = personagem.getTempoEspera();
                proximo = personagem;
            }
        }
        return proximo;
    }

    // Método para atualizar o tempo de espera da equipe
    public void atualizarTempoEspera() {
        for (Personagem personagem : personagens) {
            if (personagem.getTempoEspera() > 0) {
                personagem.setTempoEspera(personagem.getTempoEspera() - 1);
            }
        }
    }
}

// Classe para definir uma habilidade
class Habilidade {
    private static int contadorID = 0;
    private int ID;
    private String nome;
    private PesosDeAtributos pesosDano;
    private PesosDeAtributos pesosMana;
    private int tempo;
    private boolean afetaTodos;
    private boolean afetaAmigos;

    public Habilidade(String nome, PesosDeAtributos pesosDano, PesosDeAtributos pesosMana, int tempo, boolean afetaTodos, boolean afetaAmigos) {
        this.ID = ++contadorID;
        this.nome = nome;
        this.pesosDano = pesosDano;
        this.pesosMana = pesosMana;
        this.tempo = tempo;
        this.afetaTodos = afetaTodos;
        this.afetaAmigos = afetaAmigos;
    }

    public int getID() {
        return ID;
    }

    public String getNome() {
        return nome;
    }

    public PesosDeAtributos getPesosDano() {
        return pesosDano;
    }

    public PesosDeAtributos getPesosMana() {
        return pesosMana;
    }

    public int getTempo() {
        return tempo;
    }

    public boolean isAfetaTodos() {
        return afetaTodos;
    }

    public boolean isAfetaAmigos() {
        return afetaAmigos;
    }
}

// Classe para definir os pesos de atributos associados a uma habilidade
class PesosDeAtributos {
    private float forca;
    private float agilidade;
    private float inteligencia;

    public PesosDeAtributos(float forca, float agilidade, float inteligencia) {
        this.forca = forca;
        this.agilidade = agilidade;
        this.inteligencia = inteligencia;
    }

    public float getForca() {
        return forca;
    }

    public float getAgilidade() {
        return agilidade;
    }

    public float getInteligencia() {
        return inteligencia;
    }
}


// Classe para definir um personagem
class Personagem {
    private static int contadorID = 0;
    private int ID;
    private String nome;
    private int nivel;
    private int PE;
    private float PV;
    private float PM;
    int tempoEspera;
    private Classe classe;
    private Map<Integer, Integer> cooldowns;

    public Personagem(String nome, Classe classe) {
        this.ID = ++contadorID;
        this.nome = nome;
        this.classe = classe;
        this.nivel = 1;
        this.PE = 0;
        calcularPV();
        calcularPM();
        this.tempoEspera = 0;
        this.cooldowns = new HashMap<>();
    }

    // Métodos para cálculo dos PV e PM máximos
    private void calcularPV() {
        PV = nivel * classe.getForca() + (nivel * classe.getAgilidade() / 2);
    }

    private void calcularPM() {
        PM = nivel * classe.getInteligencia() + (nivel * classe.getAgilidade() / 3);
    }

    // Método para computar o ganho de PE
    public void ganharPE(int nivelInimigo) {
        PE += nivelInimigo * 5;
        if (PE >= nivel * 25) {
            subirNivel();
        }
    }

    // Método para subir de nível
    private void subirNivel() {
        nivel++;
        PE = 0;
        // Incrementar atributos conforme a classe
        calcularPV();
        calcularPM();
    }

    // Método para atacar um inimigo
    public void atacar(Personagem inimigo, Habilidade habilidade) {
        int habilidadeID = habilidade.getID();
    
        if (tempoEspera == 0 && (!cooldowns.containsKey(habilidadeID) || cooldowns.get(habilidadeID) == 0)) {
            if (habilidade.getPesosMana() != null && PM >= habilidade.getPesosMana().getInteligencia()) {
                Random random = new Random();
                int dano = calcularDano(habilidade);
                inimigo.registrarDano(dano);
                PM -= habilidade.getPesosMana().getInteligencia();
                tempoEspera = habilidade.getTempo();
    
                // Adicionar a habilidade ao cooldown
                cooldowns.put(habilidadeID, habilidade.getTempo());
            } else if (habilidade.getPesosMana() == null) {
                System.out.println("A habilidade " + habilidade.getNome() + " não consome mana.");
            } else {
                System.out.println("Não há mana suficiente para usar a habilidade " + habilidade.getNome());
            }
        } else {
            System.out.println("A habilidade " + habilidade.getNome() + " está em tempo de espera. Escolha outra ação.");
        }
    
        // Reduzir o tempo de espera do herói
        if (tempoEspera > 0) {
            tempoEspera--;
        }
    
        // Reduzir o tempo de espera das habilidades em cooldown
        for (Integer id : cooldowns.keySet()) {
            int cooldown = cooldowns.get(id);
            if (cooldown > 0) {
                cooldowns.put(id, cooldown - 1);
            }
        }
    
        // Remover habilidades com cooldown expirado
        cooldowns.entrySet().removeIf(entry -> entry.getValue() <= 0);
    }

    // Método para calcular o dano causado por uma habilidade
    private int calcularDano(Habilidade habilidade) {
        PesosDeAtributos pesosDano = habilidade.getPesosDano();
        int dano = (int) (nivel * Math.ceil(pesosDano.getForca() * classe.getForca() +
                pesosDano.getAgilidade() * classe.getAgilidade() +
                pesosDano.getInteligencia() * classe.getInteligencia()));
        return dano;
    }

    // Método para registrar o dano sofrido
    public void registrarDano(int dano) {
        PV -= dano;
        if (PV <= 0) {
            PV = 0;
        }
    }

    public void imprimirFicha() {
        System.out.println("Ficha do Personagem:");
        System.out.println("---------");
        System.out.println("Nome: " + getNome());
        System.out.println("Classe: " + getClasse().getClass().getSimpleName());
        System.out.println("Nível: " + getNivel());
        System.out.println("PV: " + getPV());
        System.out.println("PM: " + getPM());
        System.out.println("Tempo de Espera: " + getTempoEspera());
        System.out.println();
    }

    // Métodos getters e setters
    public int getID() {
        return ID;
    }

    public String getNome() {
        return nome;
    }

    public int getNivel() {
        return nivel;
    }

    public int getPE() {
        return PE;
    }

    public float getPV() {
        return PV;
    }

    public float getPM() {
        return PM;
    }

    public int getTempoEspera() {
        return tempoEspera;
    }

    public Classe getClasse() {
        return classe;
    }

    public void setTempoEspera(int tempoEspera) {
        this.tempoEspera = tempoEspera;
    }
}

// Classe abstrata para definir uma classe de personagem
abstract class Classe {
    protected int forca;
    protected int agilidade;
    protected int inteligencia;
    protected List<Habilidade> habilidades;

    public Classe(int forca, int agilidade, int inteligencia) {
        this.forca = forca;
        this.agilidade = agilidade;
        this.inteligencia = inteligencia;
        this.habilidades = new ArrayList<>();
    }

    public abstract void adicionarHabilidades();

    public int getForca() {
        return forca;
    }

    public int getAgilidade() {
        return agilidade;
    }

    public int getInteligencia() {
        return inteligencia;
    }

    public List<Habilidade> getHabilidades() {
        return habilidades;
    }
}

// Classe para definir o Arqueiro
class Arqueiro extends Classe {
    public Arqueiro() {
        super(1, 3, 2);
        adicionarHabilidades();
    }

    @Override
    public void adicionarHabilidades() {
        habilidades.add(new Habilidade("Socar", new PesosDeAtributos(0.3f, 0.1f, 0), null, 3, false, false));
        habilidades.add(new Habilidade("Atirar Flecha", new PesosDeAtributos(0.3f, 0.5f, 0), null, 4, false, false));
        habilidades.add(new Habilidade("Flecha Encantada", new PesosDeAtributos(0.3f, 0.5f, 0.4f), new PesosDeAtributos(0.2f, 1, 0), 7, false, false));
    }
}

// Classe para definir o Guerreiro
class Guerreiro extends Classe {
    public Guerreiro() {
        super(4, 1, 2);
        adicionarHabilidades();
    }

    @Override
    public void adicionarHabilidades() {
        habilidades.add(new Habilidade("Socar", new PesosDeAtributos(0.3f, 0.1f, 0), null, 4, false, false));
        habilidades.add(new Habilidade("Golpe de Espada", new PesosDeAtributos(0.7f, 0.3f, 0), null, 5, false, false));
        habilidades.add(new Habilidade("Espada Flamejante", new PesosDeAtributos(0.5f, 0.5f, 0.4f), new PesosDeAtributos(0.2f, 1, 0), 7, false, false));
    }
}

// Classe para definir o Mago
class Mago extends Classe {
    public Mago() {
        super(1, 2, 4);
        adicionarHabilidades();
    }

    @Override
    public void adicionarHabilidades() {
        habilidades.add(new Habilidade("Socar", new PesosDeAtributos(0.1f, 0.1f, 0), null, 2, false, false));
        habilidades.add(new Habilidade("Enfraquecer", new PesosDeAtributos(0.3f, 0.2f, 0.5f), new PesosDeAtributos(0, 0, 0.5f), 5, false, false));
        habilidades.add(new Habilidade("Cura Amigo", new PesosDeAtributos(0.5f, 0.2f, 0.8f), new PesosDeAtributos(0, 0, 0.7f), 4, false, true));
    }
}

// Classe para definir o Monstro
class Monstro extends Classe {
    public Monstro() {
        super(5, 2, 1);
        adicionarHabilidades();
    }

    @Override
    public void adicionarHabilidades() {
        habilidades.add(new Habilidade("Socar", new PesosDeAtributos(0.8f, 0.4f, 0), null, 5, false, false));
        habilidades.add(new Habilidade("Chutar", new PesosDeAtributos(1.0f, 0.5f, 0), null, 8, false, false));
        habilidades.add(new Habilidade("Grito Atordoante", new PesosDeAtributos(0.4f, 0.2f, 0), null, 6, true, false));
    }
}

// Classe para controlar o jogp

class Jogo {
    private Equipe equipeHerois;
    private Equipe equipeInimigos;
    private Scanner scanner;

    public Jogo() {
        this.equipeHerois = new Equipe();
        this.equipeInimigos = new Equipe();
        this.scanner = new Scanner(System.in);
    }

    public void iniciarJogo() {
        criarPersonagensManualmente();
        simularBatalhas();
    }

    private void criarPersonagensManualmente() {
        System.out.println("Bem-vindo ao jogo! Vamos criar sua equipe de heróis.");

        for (int i = 1; i <=3; i++) {
            System.out.println("Criando herói " + i);
            System.out.print("Digite o nome do herói: ");
            String nome = scanner.nextLine();

            System.out.println("Escolha a classe do herói:");
            System.out.println("1. Arqueiro");
            System.out.println("2. Guerreiro");
            System.out.println("3. Mago");
            int opcaoClasse = Integer.parseInt(scanner.nextLine());

            Classe classe;
            switch (opcaoClasse) {
                case 1:
                    classe = new Arqueiro();
                    break;
                case 2:
                    classe = new Guerreiro();
                    break;
                case 3:
                    classe = new Mago();
                    break;
                default:
                    System.out.println("Opção inválida. Escolhendo Arqueiro por padrão.");
                    classe = new Arqueiro();
                    break;
            }

            equipeHerois.adicionarPersonagem(new Personagem(nome, classe));
        }
    }

    private void simularBatalhas() {
        // Lógica para criar inimigos ou carregar do arquivo
        Monstro monstro1 = new Monstro();
        Monstro monstro2 = new Monstro();
        equipeInimigos.adicionarPersonagem(new Personagem("Monstro1", monstro1));
        equipeInimigos.adicionarPersonagem(new Personagem("Monstro2", monstro2));

        System.out.println("Início da batalha!");

        while (!equipeHerois.getPersonagens().isEmpty() && !equipeInimigos.getPersonagens().isEmpty()) {
            imprimirEstadoBatalha();
    

        // Heróis escolhem ação
        for (Personagem heroi : equipeHerois.getPersonagens()) {
            if (heroi.getTempoEspera() == 0) {
                System.out.println("\nAção para " + heroi.getNome() + ":");
                System.out.println("1. Atacar");
                System.out.print("Escolha a ação: ");
                int opcaoAcao = Integer.parseInt(scanner.nextLine());

                if (opcaoAcao == 1) {
                    escolherAlvoEAtacar(heroi, equipeInimigos);
                } else {
                    System.out.println("Opção inválida. Perdendo turno.");
                }
            } else {
                System.out.println(heroi.getNome() + " está esperando (" + heroi.getTempoEspera() + " turnos restantes).");
                heroi.setTempoEspera(heroi.getTempoEspera() - 1); // Reduzir o tempo de espera
            }
        }

        // Inimigos escolhem ação
        for (Iterator<Personagem> iterator = equipeInimigos.getPersonagens().iterator(); iterator.hasNext();) {
            Personagem inimigo = iterator.next();
            if (!equipeHerois.getPersonagens().isEmpty()) {
                Personagem alvo = escolherAlvo(equipeHerois);
                Habilidade habilidade = escolherHabilidade(inimigo.getClasse());
                inimigo.atacar(alvo, habilidade);
                System.out.println(inimigo.getNome() + " atacou " + alvo.getNome() + " com " + habilidade.getNome() + " causando " + habilidade.getPesosDano().getForca() + " de dano!");

                if (alvo.getPV() <= 0) {
                    System.out.println(alvo.getNome() + " foi derrotado!");
                    iterator.remove(); // Remover inimigo derrotado
                    equipeHerois.atualizarTempoEspera(); // Atualizar o tempo de espera dos heróis após cada ação inimiga
                }

                // Remover inimigo da equipe se estiver derrotado
                if (inimigo.getPV() <= 0) {
                    System.out.println(inimigo.getNome() + " foi derrotado!");
                    iterator.remove(); // Remover inimigo derrotado
                    equipeHerois.atualizarTempoEspera(); // Atualizar o tempo de espera dos heróis após cada ação inimiga
                }
            }
        }

        // Atualizar o tempo de espera
        equipeHerois.atualizarTempoEspera();
        equipeInimigos.atualizarTempoEspera();
    }

    // Imprimir resultado da batalha    
    imprimirResultadoBatalha();
}

private void escolherAlvoEAtacar(Personagem heroi, Equipe equipeInimiga) {
    System.out.println("Escolha o inimigo para atacar:");

    for (int i = 0; i < equipeInimiga.getPersonagens().size(); i++) {
        Personagem inimigo = equipeInimiga.getPersonagens().get(i);
        System.out.println((i + 1) + ". " + inimigo.getNome());
    }

    System.out.print("Escolha o número do inimigo: ");
    int opcaoInimigo = Integer.parseInt(scanner.nextLine());

    if (opcaoInimigo >= 1 && opcaoInimigo <= equipeInimiga.getPersonagens().size()) {
        Personagem alvo = equipeInimiga.getPersonagens().get(opcaoInimigo - 1);

        System.out.println("Escolha a habilidade:");

        for (int i = 0; i < heroi.getClasse().getHabilidades().size(); i++) {
            Habilidade habilidade = heroi.getClasse().getHabilidades().get(i);
            System.out.println((i + 1) + ". " + habilidade.getNome() + " (Cooldown: " + heroi.getTempoEspera() + " turnos)");
        }

        System.out.print("Escolha o número da habilidade: ");
        int opcaoHabilidade = Integer.parseInt(scanner.nextLine());

        if (opcaoHabilidade >= 1 && opcaoHabilidade <= heroi.getClasse().getHabilidades().size()) {
            Habilidade habilidadeSelecionada = heroi.getClasse().getHabilidades().get(opcaoHabilidade - 1);

            if (heroi.getTempoEspera() == 0 || habilidadeSelecionada.getTempo() == 0) {
                heroi.atacar(alvo, habilidadeSelecionada);
                System.out.println(heroi.getNome() + " atacou " + alvo.getNome() + " com " + habilidadeSelecionada.getNome() +
                        " causando " + habilidadeSelecionada.getPesosDano().getForca() + " de dano!");
            } else {
                System.out.println("A habilidade " + habilidadeSelecionada.getNome() +
                        " está em tempo de espera. Escolha outra ação.");
            }
        } else {
            System.out.println("Opção inválida. Perdendo turno.");
        }
    } else {
        System.out.println("Opção inválida. Perdendo turno.");
    }
}

    private Personagem escolherAlvo(Equipe equipe) {
        System.out.println("Escolha o herói para atacar:");

        for (int i = 0; i < equipe.getPersonagens().size(); i++) {
            Personagem heroi = equipe.getPersonagens().get(i);
            System.out.println((i + 1) + ". " + heroi.getNome());
        }

        System.out.print("Escolha o número do herói: ");
        int opcaoHeroi = Integer.parseInt(scanner.nextLine());

        if (opcaoHeroi >= 1 && opcaoHeroi <= equipe.getPersonagens().size()) {
            return equipe.getPersonagens().get(opcaoHeroi - 1);
        } else {
            System.out.println("Opção inválida. Escolhendo aleatoriamente.");
            return equipe.proximoAtacante();
        }
    }

    private Habilidade escolherHabilidade(Classe classe) {
        System.out.println("Escolha a habilidade:");

        List<Habilidade> habilidades = classe.getHabilidades();
        for (int i = 0; i < habilidades.size(); i++) {
            Habilidade habilidade = habilidades.get(i);
            System.out.println((i + 1) + ". " + habilidade.getNome());
        }

        System.out.print("Escolha o número da habilidade: ");
        int opcaoHabilidade = Integer.parseInt(scanner.nextLine());

        if (opcaoHabilidade >= 1 && opcaoHabilidade <= habilidades.size()) {
            return habilidades.get(opcaoHabilidade - 1);
        } else {
            System.out.println("Opção inválida. Escolhendo aleatoriamente.");
            Random random = new Random();
            return habilidades.get(random.nextInt(habilidades.size()));
        }
    }

    private void imprimirEstadoBatalha() {
        System.out.println("\n---- Estado Atual da Batalha ----");
        System.out.println("Equipe dos Heróis:");
        imprimirInformacoesEquipe(equipeHerois);
        System.out.println("Equipe dos Inimigos:");
        imprimirInformacoesEquipe(equipeInimigos);
    }

    private void imprimirResultadoBatalha() {
        System.out.println("\n---- Resultado da Batalha ----");
        if (equipeHerois.getPersonagens().isEmpty()) {
            System.out.println("Os heróis foram derrotados! :(");
        } else {
            System.out.println("Os heróis venceram a batalha! :)");
        }
    }

    private void imprimirInformacoesEquipe(Equipe equipe) {
        for (Personagem personagem : equipe.getPersonagens()) {
            System.out.println(personagem.getNome() + " - PV: " + personagem.getPV() + " | PM: " + personagem.getPM() + " | Tempo de Espera: " + personagem.getTempoEspera());
        }
    }

    public static void main(String[] args) {
        Jogo jogo = new Jogo();
        jogo.iniciarJogo();
    }
}
