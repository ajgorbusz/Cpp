#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <fstream>

// Struktura reprezentująca zadanie CPU-bound
// Struktura zawiera wszystkie niezbędne informacje dla harmonogramu procesów
struct Process {
    // Unikalny identyfikator procesu
    int id;
    
    // Czas przybycia procesu do systemu
    int arrival_time;
    
    // Ilość czasu CPU wymagana do wykonania procesu
    int burst_time;
    
    // Czas zakończenia wykonania procesu
    int completion_time;
    
    // Całkowity czas od przybycia do zakończenia
    int turnaround_time;
    
    // Czas spędzony w kolejce gotowych
    int waiting_time;
    
    // Przeciążony operator porównania do sortowania procesów według czasu przybycia
    // Używany w harmonogramie FCFS do utrzymania kolejności procesów
    bool operator<(const Process& other) const {
        return arrival_time < other.arrival_time;
    }
};

// Algorytm First-Come, First-Served (FCFS)
// Ten nietykalny algorytm harmonizuje procesy na podstawie kolejności ich przybycia
// Jest prosty, ale może prowadzić do efektu "korku", gdzie krótsze procesy czekają za dłuższymi
void fcfs(std::vector<Process>& processes, std::ofstream* csv_file = nullptr) {
    // Sortowanie procesów według czasu przybycia, aby utrzymać kolejność FCFS
    std::sort(processes.begin(), processes.end());
    
    // Śledzenie aktualnego czasu systemowego
    int current_time = 0;
    
    // Przetwarzanie każdego zadania w kolejności przybycia
    for (auto& p : processes) {
        // Zapewnienie, że nie zaczniemy przetwarzania przed przybyciem procesu
        current_time = std::max(current_time, p.arrival_time);
        
        // Obliczanie czasu zakończenia (aktualny czas + czas bursta)
        p.completion_time = current_time + p.burst_time;
        
        // Obliczanie metryk wydajności
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;
        
        // Aktualizacja aktualnego czasu do momentu zakończenia procesu
        current_time = p.completion_time;

        // Zapis wyników do pliku CSV
        if (csv_file) {
            *csv_file << "FCFS," << p.id << "," << p.arrival_time << "," << p.burst_time << ","
                     << p.completion_time << "," << p.turnaround_time << "," << p.waiting_time << "\n";
        }
    }
}

// Algorytm Round Robin (RR)
// Ten algorytm tykalny przydzielający czas CPU w ustalonych interwałach (kwantach)
// Procesy są harmonizowane w kolejce cyklicznej, zapewniając lepszy czas odpowiedzi
void round_robin(std::vector<Process>& processes, int quantum, std::ofstream* csv_file = nullptr) {
    // Kolejka gotowych do zarządzania procesami w kolejności FIFO
    std::queue<Process> ready_queue;
    
    // Inicjalizacja kolejki gotowych wszystkimi procesami
    for (auto& p : processes) {
        ready_queue.push(p);
    }
    
    // Śledzenie aktualnego czasu systemowego
    int current_time = 0;
    
    // Przetwarzanie do momentu zakończenia wszystkich zadań
    while (!ready_queue.empty()) {
        // Pobieranie następnego procesu z kolejki
        Process current = ready_queue.front();
        ready_queue.pop();
        
        // Zapewnienie, że nie zaczniemy przetwarzania przed przybyciem procesu
        if (current_time < current.arrival_time) {
            current_time = current.arrival_time;
        }
        
        // Jeśli proces wymaga więcej czasu niż kwant
        if (current.burst_time > quantum) {
            // Przydzielanie czasu kwantu
            current_time += quantum;
            // Redukowanie pozostałego czasu wybuchu
            current.burst_time -= quantum;
            // Wstawienie procesu z powrotem do kolejki na następny cykl
            ready_queue.push(current);
        } else {
            // Proces kończy się w ramach kwantu
            current_time += current.burst_time;
            current.completion_time = current_time;
            current.turnaround_time = current.completion_time - current.arrival_time;
            current.waiting_time = current.turnaround_time - current.burst_time;
            
            // Znalezienie oryginalnego procesu w wektorze i aktualizacja jego wartości
            for (auto& p : processes) {
                if (p.id == current.id) {
                    p.completion_time = current.completion_time;
                    p.turnaround_time = current.turnaround_time;
                    p.waiting_time = current.waiting_time;

                    // Zapis wyników do pliku CSV
                    if (csv_file) {
                        *csv_file << "RR," << p.id << "," << p.arrival_time << "," << p.burst_time << ","
                                 << p.completion_time << "," << p.turnaround_time << "," << p.waiting_time << "\n";
                    }
                    break;
                }
            }
        }
    }
}

// Funkcja wyświetlania wyników
// Ta funkcja wyświetla szczegółowe statystyki harmonogramowania i metryki wydajności
// Zapewnia kompleksowy widok wykonania procesów dla różnych algorytmów
void print_results(const std::vector<Process>& processes, const std::string& algorithm) {
    // Wyświetlanie nagłówka z nazwą algorytmu
    std::cout << "\nWyniki dla harmonogramowania " << algorithm << ":\n";
    
    // Formatowanie nagłówków tabeli z kolumnami o stałej szerokości
    std::cout << std::setw(10) << "Proces" 
              << std::setw(10) << "Przybycie" 
              << std::setw(10) << "Czas bursta" 
              << std::setw(15) << "Czas zakończenia" 
              << std::setw(15) << "Czas od przybycia do zakończenia" 
              << std::setw(10) << "Czas oczekiwania" 
              << std::endl;
    
    // Obliczanie średnich metryk
    double avg_turnaround = 0;
    double avg_waiting = 0;
    
    // Wyświetlanie statystyk poszczególnych procesów
    for (const auto& p : processes) {
        std::cout << std::setw(10) << p.id 
                  << std::setw(10) << p.arrival_time 
                  << std::setw(10) << p.burst_time 
                  << std::setw(15) << p.completion_time 
                  << std::setw(15) << p.turnaround_time 
                  << std::setw(10) << p.waiting_time 
                  << std::endl;
        
        // Akumulacja wartości do obliczeń średnich
        avg_turnaround += p.turnaround_time;
        avg_waiting += p.waiting_time;
    }
    
    // Obliczanie i wyświetlanie średnich metryk
    int n = processes.size();
    std::cout << "\nŚredni czas od przybycia do zakończenia: " << avg_turnaround / n << " ms\n";
    std::cout << "Średni czas oczekiwania: " << avg_waiting / n << " ms\n";
}

int main() {
    // Przykładowe procesy (id, czas przybycia, czas bursta)
    std::vector<Process> processes = {
        {1, 0, 24},
        {2, 4, 3},
        {3, 5, 3},
        {4, 6, 12},
        {5, 15, 6},
        {6, 18, 5},
        {7, 20, 8},
        {8, 22, 4},
        {9, 25, 10},
        {10, 28, 7},
        {11, 30, 9},
        {12, 32, 6},
        {13, 35, 11},
        {14, 38, 5},
        {15, 40, 8},
        {16, 42, 4},
        {17, 45, 10},
        {18, 48, 7},
        {19, 50, 9},
        {20, 52, 6},
        {21, 55, 11},
    };

    // Tworzenie pliku CSV do zapisu wyników
    std::ofstream csv_file("cpu_scheduler_results.csv");
    if (!csv_file.is_open()) {
        std::cerr << "Nie można utworzyć pliku CSV\n";
        return 1;
    }

    // Zapis nagłówka CSV
    csv_file << "Algorithm,Process ID,Arrival Time,Burst Time,Completion Time,Turnaround Time,Waiting Time\n";

    // Wyświetlanie procesów przed harmonogramowaniem
    std::cout << "Procesy przed harmonogramowaniem:\n";
    std::cout << std::setw(10) << "Proces"
              << std::setw(10) << "Przybycie"
              << std::setw(10) << "Czas bursta"
              << std::endl;
    for (const auto& p : processes) {
        std::cout << std::setw(10) << p.id
                  << std::setw(10) << p.arrival_time
                  << std::setw(10) << p.burst_time
                  << std::endl;
    }

    // Harmonogramowanie procesów
    std::vector<Process> fcfs_processes = processes;
    std::vector<Process> rr_processes = processes;

    // Algorytm FCFS
    fcfs(fcfs_processes, &csv_file);
    print_results(fcfs_processes, "FCFS");

    // Algorytm Round Robin z kwantem 4
    round_robin(rr_processes, 4, &csv_file);
    print_results(rr_processes, "Round Robin (Q=4)");

    // Zamykanie pliku CSV
    csv_file.close();

    return 0;
}
