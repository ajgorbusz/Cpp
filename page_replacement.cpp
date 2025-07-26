/**
 * @brief Symulator Algorytmów Zastępowania Stron
 * 
 * Program symuluje działanie dwóch podstawowych algorytmów zastępowania stron:
 * FIFO (First-In-First-Out) i MFU (Most Frequently Used).
 * 
 * Kontekst:
 * - W systemach operacyjnych, procesy pracują z dużą ilością danych
 * - Nie wszystkie dane mogą być przechowywane w pamięci RAM
 * - Algorytmy zastępowania stron decydują, które strony danych powinny być
 *   przechowywane w RAM, a które mogą być przeniesione na dysk
 * 
 * Zaimplementowane Algorytmy:
 * 1. FIFO (First-In-First-Out)
 *    - Prosty algorytm "pierwszy wchodzi, pierwszy wychodzi"
 *    - Zastępuje najstarszą stronę w pamięci
 *    - Możliwe występowanie anomali Belady (paradoksalne zwiększenie błędów stron)
 * 
 * 2. MFU (Most Frequently Used)
 *    - Zaawansowany algorytm oparty na częstotliwości użycia stron
 *    - Zastępuje stronę, która była najczęściej używana
 *    - Próbuje przewidzieć, które strony będą potrzebne w przyszłości
 * 
 * Funkcje programu:
 * - Symulacja pracy algorytmów na podanej sekwencji odniesień
 * - Wyświetlanie stanu ramek pamięci po każdym kroku
 * - Liczenie i wyświetlanie statystyk (liczba błędów stron, współczynnik trafień)
 * - Zapis wyników do pliku CSV dla dalszej analizy
 * 
 * Wyniki:
 * - Program pokazuje, jak różne algorytmy radzą sobie z tym samym obciążeniem
 * - Umożliwia porównanie wydajności FIFO i MFU
 * - Pomaga zrozumieć zachowania algorytmów w różnych scenariuszach
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <fstream>

/**
 * @brief Implementuje algorytm FIFO (First-In-First-Out)
 * 
 * Algorytm FIFO (First-In-First-Out) to prosty, ale nie zawsze optymalny sposób
 * zastępowania stron w pamięci.
 * 
 * Mechanizm działania:
 * - Działa na zasadzie "pierwszy wchodzi, pierwszy wychodzi"
 * - Gdy wystąpi błąd strony (strona nie jest w pamięci):
 *   - Znajduje najstarszą stronę w pamięci (ta która najdłużej tam przebywała)
 *   - Zastępuje ją nową stroną
 * - Nie uwzględnia częstotliwości ani wzoru użycia stron
 * 
 * Wady algorytmu:
 * - Możliwe występowanie anomali Belady
 * - Nie uwzględnia przyszłych potrzeb procesu
 * - Może prowadzić do nieefektywnego wykorzystania pamięci
 * 
 * @param reference_string Sekwencja odniesień do stron (np. [1, 2, 3, 4])
 * @param frame_size Liczba dostępnych ramek pamięci (np. 3)
 * @param csv_file Opcjonalny wskaźnik do pliku CSV do zapisu wyników
 */
void fifo(const std::vector<int>& reference_string, int frame_size, std::ofstream* csv_file = nullptr) {
    std::vector<int> frames(frame_size, -1);
    int page_faults = 0;
    int next_victim = 0;

    std::cout << "\nSymulacja FIFO (" << frame_size << " ramki):\n";
    std::cout << "Referencja\tStrony w ramakch\tPage Fault\n";
    std::cout << "---------------------------------------------\n";

    if (csv_file) {
        *csv_file << "Algorithm,Frame Size,Reference,Pages in Frames,Page Fault\n";
    }

    for (int page : reference_string) {
        bool page_fault = true;
        
        for (int i = 0; i < frame_size; i++) {
            if (frames[i] == page) {
                page_fault = false;
                break;
            }
        }

        if (page_fault) {
            frames[next_victim] = page;
            next_victim = (next_victim + 1) % frame_size;
            page_faults++;
        }

        std::cout << std::setw(3) << page << "\t\t";
        for (int frame : frames) {
            if (frame != -1) {
                std::cout << frame << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << "\t" << (page_fault ? "TAK" : "NIE") << "\n";

        if (csv_file) {
            std::string frames_str = "";
            for (int frame : frames) {
                if (frame != -1) {
                    frames_str += std::to_string(frame) + " ";
                } else {
                    frames_str += "_ ";
                }
            }
            *csv_file << "FIFO," << frame_size << "," << page << "," << frames_str << "," << (page_fault ? "YES" : "NO") << "\n";
        }
    }

    std::cout << "\nLiczba page fault'ów: " << page_faults << "\n";
    std::cout << "Stopień trafień: " << std::fixed << std::setprecision(2)
              << ((reference_string.size() - page_faults) / static_cast<double>(reference_string.size())) * 100 << "%\n";

    if (csv_file) {
        *csv_file << "\nAlgorithm,Frame Size,Total Page Faults,Hit Rate\n";
        *csv_file << "FIFO," << frame_size << "," << page_faults << "," << std::fixed << std::setprecision(2)
                  << ((reference_string.size() - page_faults) / static_cast<double>(reference_string.size())) * 100 << "%\n";
    }
}

/**
 * @brief Implementuje algorytm MFU (Most Frequently Used)
 * 
 * Algorytm MFU (Most Frequently Used) to zaawansowany sposób zastępowania stron,
 * który opiera się na analizie częstotliwości użycia.
 * 
 * Mechanizm działania:
 * - Dla każdej strony utrzymuje licznik jej użycia
 * - Gdy wystąpi błąd strony:
 *   - Znajduje stronę o najwyższej częstotliwości użycia
 *   - Zastępuje ją nową stroną
 * - Założenie: często używane strony będą potrzebne ponownie
 * 
 * Zalety algorytmu:
 * - Lepiej radzi sobie z powtarzającymi się wzorami użycia
 * - Próbuje przewidzieć przyszłe potrzeby procesu
 * - Zazwyczaj daje lepsze wyniki niż FIFO
 * 
 * Wady:
 * - Większa złożoność implementacji
 * - Wymaga więcej pamięci do przechowywania liczników
 * - Może nie być optymalny dla losowych wzorów użycia
 * 
 * @param reference_string Sekwencja odniesień do stron (np. [1, 2, 3, 4])
 * @param frame_size Liczba dostępnych ramek pamięci (np. 3)
 * @param csv_file Opcjonalny wskaźnik do pliku CSV do zapisu wyników
 */
void mfu(const std::vector<int>& reference_string, int frame_size, std::ofstream* csv_file = nullptr) {
    std::vector<int> frames(frame_size, -1);
    std::unordered_map<int, int> frequency;
    int page_faults = 0;

    std::cout << "\nSymulacja MFU (" << frame_size << " ramki):\n";
    std::cout << "Referencja\tStrony w ramkach\tPage Fault\n";
    std::cout << "---------------------------------------------\n";

    if (csv_file) {
        *csv_file << "Algorithm,Frame Size,Reference,Pages in Frames,Page Fault\n";
    }

    for (int page : reference_string) {
        bool page_fault = true;
        
        for (int i = 0; i < frame_size; i++) {
            if (frames[i] == page) {
                page_fault = false;
                frequency[page]++;
                break;
            }
        }

        if (page_fault) {
            int victim_index = -1;
            int max_frequency = 0;
            
            for (int i = 0; i < frame_size; i++) {
                if (frames[i] == -1) {
                    victim_index = i;
                    break;
                }
            }

            if (victim_index == -1) {
                for (int i = 0; i < frame_size; i++) {
                    if (frames[i] != -1) {
                        if (frequency[frames[i]] > max_frequency) {
                            max_frequency = frequency[frames[i]];
                            victim_index = i;
                        }
                    }
                }
            }

            frames[victim_index] = page;
            frequency[page]++;
            page_faults++;
        }

        std::cout << std::setw(3) << page << "\t\t";
        for (int frame : frames) {
            if (frame != -1) {
                std::cout << frame << " ";
            } else {
                std::cout << "_ ";
            }
        }
        std::cout << "\t" << (page_fault ? "TAK" : "NIE") << "\n";

        if (csv_file) {
            std::string frames_str = "";
            for (int frame : frames) {
                if (frame != -1) {
                    frames_str += std::to_string(frame) + " ";
                } else {
                    frames_str += "_ ";
                }
            }
            *csv_file << "MFU," << frame_size << "," << page << "," << frames_str << "," << (page_fault ? "YES" : "NO") << "\n";
        }
    }

    std::cout << "\nLiczba page fault'ów: " << page_faults << "\n";
    std::cout << "Stopień trafień: " << std::fixed << std::setprecision(2)
              << ((reference_string.size() - page_faults) / static_cast<double>(reference_string.size())) * 100 << "%\n";

    if (csv_file) {
        *csv_file << "\nAlgorithm,Frame Size,Total Page Faults,Hit Rate\n";
        *csv_file << "MFU," << frame_size << "," << page_faults << "," << std::fixed << std::setprecision(2)
                  << ((reference_string.size() - page_faults) / static_cast<double>(reference_string.size())) * 100 << "%\n";
    }
}

/**
 * @brief Punkt wejścia programu głównego
 * 
 * Główna funkcja odpowiadająca za inicjalizację i uruchomienie symulacji.
 */
int main() {
    // Definicja sekwencji odniesień do stron
    // Przykład obciążenia zawierający różne wzorce użycia:
    // - Kolejne odniesienia (1, 2, 3, 4)
    // - Powtarzające się odniesienia (2, 1)
    // - Zmiany zestawu roboczego (5, 6)
    // - Wzorce lokalności (2, 1, 2, 3)
    std::vector<int> reference_string = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};

    // Liczba dostępnych ramek pamięci
    int frame_size = 3;

    // Wyświetlanie sekwencji odniesień do stron
    std::cout << "Sekwencja odniesień do stron:\n";
    for (int page : reference_string) {
        std::cout << page << " ";
    }
    std::cout << "\n\n";

    // Tworzenie pliku CSV do zapisu wyników
    std::ofstream csv_file("page_replacement_results.csv");
    if (!csv_file.is_open()) {
        std::cerr << "Nie można utworzyć pliku CSV\n";
        return 1;
    }

    // Uruchomienie algorytmu FIFO
    // Wyświetla wyniki w konsoli i zapisuje do pliku CSV
    fifo(reference_string, frame_size, &csv_file);

    // Uruchomienie algorytmu MFU
    // Wyświetla wyniki w konsoli i zapisuje do pliku CSV
    mfu(reference_string, frame_size, &csv_file);

    // Zamykanie pliku CSV
    csv_file.close();
    
    return 0;
}
