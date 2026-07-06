#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>
#include <unistd.h>
#include <stdlib.h>

struct node_t{
  int tickets;
  struct node_t *next;
  std::string process;
  int finish_time;
  int proc_runtime = 0;
  struct node_t *prev;
};

int number_of_tickets = 100 + 50 + 150;

int main(){
  int n_processes = 0;
  int sum_of_finish_time1 = 0;
  int sum_of_finish_time2 = 0;
  int number_of_process;
  struct node_t A = {100, nullptr, "A", 333};
  struct node_t B = {50, nullptr, "B", 162};
  struct node_t C = {150, nullptr, "C", 505};
  number_of_process = 3;

  A.next = &B;
  A.prev = nullptr;
  B.next = &C;
  B.prev = &A;
  C.prev = &B;
  struct node_t *head = &A;

    //random number generator
  std::random_device rd;
  std::mt19937 gen(rd());

  int i = 0;
  while(number_of_process > 0){
    std::uniform_int_distribution<int> distr(0, number_of_tickets - 1);
    int counter = 0;

    int winner = distr(gen);

    struct node_t *current  = head;

    while(current && number_of_process > 0){
      counter += current->tickets;
      if(counter > winner){
        break;
      }

      current = current->next;

    }

    current->proc_runtime++;
    i++;
    std::cout << "tick: " << i << " winner: " << current->process << " ticket: " << winner << " runtime: " << current->proc_runtime << std::endl;

    if(current->proc_runtime >= current->finish_time){
      std::cout << "process: " << current->process << " finished!\n";
      number_of_tickets -= current->tickets;
      sum_of_finish_time1 += i;
      sum_of_finish_time2 += (i * i);


      if(number_of_process > 1){

        if(current == head){
          head = current->next;

          if(head)
            head->prev = nullptr;
        } 

        else if(current->next == nullptr){
          current = current->prev;
          current->next = nullptr;
        }

        else {
          current->prev->next = current->next;
          current->next->prev = current->prev;
        }
      }
      
      number_of_process--;
      n_processes++;
      std::cout << "sucess!\n";
    }
  }

  double jains_index;

  jains_index = 
    (double)(sum_of_finish_time1 * sum_of_finish_time1) 
    / (n_processes * sum_of_finish_time2);

  std::cout << "Fairness Metric: " << jains_index << std::endl;

  return 0;
}
