#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_preferences(int i);
pair* merge_sort(pair *arr, int length);
int return_strength(pair couple);
string populate_rank_name(int voter, int rank);
int cycle_end(int loser);
int find_winner(int cand);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    // int voter_count = get_int("Number of voters: ");
    int voter_count = 9;

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            // string name = get_string("Rank %i: ", j + 1);
            string name = populate_rank_name(i, j);
            // printf("voter name %s\n", name);
            
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        
        // for(int j = 0; j < candidate_count; j++){
        //     printf("Rank %i is %s\n", j+1, candidates[ranks[j]]);
        // }

        record_preferences(ranks);

        printf("\n");
    }
    
    // for(int i = 0; i < candidate_count; i++){
    //     for(int j = 0; j < candidate_count; j++){
    //         printf("Pref %s over %s: %i\n", candidates[i], candidates[j], 
    //             preferences[i][j]);
    //     }
    // }
    

    add_pairs();
    
    // for(int i = 0; i < pair_count; i++){
    //     printf("Pair: %i > %i\n", pairs[i].winner, pairs[i].loser);
    // }
    printf("\n");
    
    sort_pairs();
    
    // for(int i = 0; i < pair_count; i++){
    //     printf("Pair: %i > %i\n", pairs[i].winner, pairs[i].loser);
    // }
    
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(candidates[i], name) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    // TODO
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++){
        for(int j = i+1; j < candidate_count; j++){
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++){
        for(int j = i+1; j < candidate_count; j++){
            if(preferences[i][j] < preferences[j][i]){
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            } else if( preferences[i][j] > preferences[j][i]){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    
    merge_sort(pairs, pair_count);
    // TODO
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++){
        
        // if(i == 2){
        //     int cycleEnd = cycle_end(pairs[i].loser);
            
        //     // printf("cycleEnd: %i.\n winner: %i\n", cycleEnd, pairs[i].winner);
        // }
        
        // checks that current winner isn't the end of a cycle
        if(pairs[i].winner != cycle_end(pairs[i].loser)){
            locked[pairs[i].winner][pairs[i].loser] = true;
            printf("locked %i over %i\n", pairs[i].winner, pairs[i].loser);
        }
    }
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner = find_winner(pairs[0].winner);
    
    printf("Winner is: %s\n", candidates[winner]);
    // TODO
    return;
}




// My merge sort algorithm
pair* merge_sort(pair *arr, int length){
  if(length == 1){
    return arr;
  }
  
  int half = (length) / 2;
  int left_length = length - half;
  int right_length = length - left_length;
  int right_start = left_length;

  pair left_half[left_length];
  pair right_half[right_length];
  
//   printf("LEFT: length: %i, bytes: %lx\n", left_length, (length - half+1)*sizeof(int));
//   printf("RIGHT: length: %i, bytes: %lx\n", right_length, (right_length+1)*sizeof(int));
  
  memcpy(left_half, arr, (left_length+2) * sizeof(int)); 
  memcpy(right_half, &arr[right_start], (right_length+2) * sizeof(int)); 

  merge_sort(left_half, left_length);
  merge_sort(right_half, right_length);
  
//   for(int i=0; i<left_length; i++){
//       printf("left pair %i > %i\n", left_half[i].winner, left_half[i].loser);
//   }

//   for(int i=0; i<right_length; i++){
//       printf("right pair %i > %i\n", right_half[i].winner, right_half[i].loser);
//   }


  int i = 0;
  int left_iterator = 0;
  int right_iterator = 0;
  while(i < length){
    if(right_iterator == right_length){
      arr[i] = left_half[left_iterator];
      left_iterator++;
      
    } else if(left_iterator == left_length){
      arr[i] = right_half[right_iterator];
      right_iterator++;
      
    } else if(return_strength(left_half[left_iterator]) 
                < return_strength(right_half[right_iterator])){
      arr[i] = right_half[right_iterator];
      right_iterator++;
      
    } else if(return_strength(right_half[right_iterator]) 
                < return_strength(left_half[left_iterator])){
      arr[i] = left_half[left_iterator];
      left_iterator++;
    }
    i++;
  }
  return arr;
}

// Returns strength of pair win
int return_strength(pair couple){
    return preferences[couple.winner][couple.loser];
}

int cycle_end(int loser){
    
    int end = loser;
    
    for(int j = 0; j < candidate_count; j++){
        if(locked[loser][j]){
            end = cycle_end(j);
        } 
    }
    
    // if(end == -1){
    //     end = loser;
    // }
    
    // if(i == 2){
    //     printf("locked: %d\n", locked[pairs[0].winner][pairs[1].loser]);
    // }
            
    return end;
}

int find_winner(int cand){
    
    int found = cand;
    for(int i = 0; i < candidate_count; i++){
        if(locked[i][cand]){
            found = find_winner(i);
        }
    }
    
    // if(found == -1){
    //     found = cand;
    // }

    return found;
}



string populate_rank_name(int voter, int rank){
    // switch(voter){
    //     case 0: switch(rank){
    //         case 0: return "greed"; break;
    //         case 1: return "emma"; break;
    //         case 2: return "watson"; break;
    //     }; break;
    //     case 1: switch(rank){
    //         case 0: return "greed"; break;
    //         case 1: return "watson"; break;
    //         case 2: return "emma"; break;
    //     }; break;
    //     case 2: switch(rank){
    //         case 0: return "emma"; break;
    //         case 1: return "greed"; break;
    //         case 2: return "watson"; break;
    //     }
    // }
    
    
    switch(voter){
        case 0: switch(rank){
            case 0: return "Alice";
            case 1: return "Bob";
            case 2: return "Charlie";
        }; break;
        case 1: switch(rank){
            case 0: return "Alice";
            case 1: return "Bob";
            case 2: return "Charlie";
        }; break;
        case 2: switch(rank){
            case 0: return "Alice";
            case 1: return "Bob";
            case 2: return "Charlie";
        }; break;
        case 3: switch(rank){
            case 0: return "Bob";
            case 1: return "Charlie";
            case 2: return "Alice";
        }; break;
        case 4: switch(rank){
            case 0: return "Bob";
            case 1: return "Charlie";
            case 2: return "Alice";
        }; break;
        case 5: switch(rank){
            case 0: return "Charlie";
            case 1: return "Alice";
            case 2: return "Bob";
        }; break;
        case 6: switch(rank){
            case 0: return "Charlie";
            case 1: return "Alice";
            case 2: return "Bob";
        }; break;
        case 7: switch(rank){
            case 0: return "Charlie";
            case 1: return "Alice";
            case 2: return "Bob";
        }; break;
        case 8: switch(rank){
            case 0: return "Charlie";
            case 1: return "Alice";
            case 2: return "Bob";
        }; break;
    }
    
    // switch(voter){
    //     case 0: switch(rank){
    //         case 0: return "Alice";
    //         case 1: return "Charlie";
    //         case 2: return "Bob";
    //     }; break;
    //     case 1: switch(rank){
    //         case 0: return "Alice";
    //         case 1: return "Charlie";
    //         case 2: return "Bob";
    //     }; break;
    //     case 2: switch(rank){
    //         case 0: return "Bob";
    //         case 1: return "Alice";
    //         case 2: return "Charlie";
    //     }; break;
    //     case 3: switch(rank){
    //         case 0: return "Bob";
    //         case 1: return "Alice";
    //         case 2: return "Charlie";
    //     }; break;
    //     case 4: switch(rank){
    //         case 0: return "Bob";
    //         case 1: return "Alice";
    //         case 2: return "Charlie";
    //     }; break;
    //     case 5: switch(rank){
    //         case 0: return "Charlie";
    //         case 1: return "Alice";
    //         case 2: return "Bob";
    //     }; break;
    //     case 6: switch(rank){
    //         case 0: return "Charlie";
    //         case 1: return "Alice";
    //         case 2: return "Bob";
    //     }; break;
    //     case 7: switch(rank){
    //         case 0: return "Charlie";
    //         case 1: return "Alice";
    //         case 2: return "Bob";
    //     }; break;
    //     case 8: switch(rank){
    //         case 0: return "Charlie";
    //         case 1: return "Bob";
    //         case 2: return "Alice";
    //     }; break;
    // }
    
    
    return "yeast infection";
}