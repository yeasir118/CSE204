#include <bits/stdc++.h>
using namespace std;

class Player{
public:
  int reflex_time;
  int player_no;
  Player* next;

  Player(int,int);
  Player(const Player&);

  void print();
  
  Player& operator=(const Player&);
  ~Player();
};

Player::Player(int reflex_time, int player_no = -1){
  this->reflex_time = reflex_time;
  this->player_no = player_no;
  next = nullptr;
}

Player::Player(const Player& obj){
  reflex_time = obj.reflex_time;
  player_no = obj.player_no;
  next = obj.next;
}

Player& Player::operator=(const Player& obj){
  if(this != &obj){
    reflex_time = obj.reflex_time;
    player_no = obj.player_no;
    next = obj.next;
  }
  return *this;
}

void Player::print(){
  cout<<player_no<<" ";
}

Player::~Player(){
  next = nullptr;
}

class Game{
public:
  Player* root;
  Player* curr;
  int no_of_players;
  int curr_player_no;

  int elapsed_time;
  Player* player_holding_ball;
  int rem_reflex_time;

  Game(int);

  void insert(int);
  void print();
  void print_player(int);
  bool eliminate(int);
  void simulate_game(int);
  void insert_middle(int,int);
  void reverse(int);
  void finish(int);
  ~Game();
};

Game::Game(int no_of_players){
  curr_player_no = 1;
  elapsed_time = 0;
  player_holding_ball = nullptr;
  rem_reflex_time = 0;
  root = nullptr;
  curr = nullptr;
}

void Game::insert(int reflex_time){
  Player* new_player = new Player(reflex_time, curr_player_no++);
  if(root == nullptr){
    root = new_player;
    curr = root;
    curr->next = root;

    player_holding_ball = root;
    rem_reflex_time = root->reflex_time;
  }else{
    new_player->next = curr->next;
    curr->next = new_player;
    curr = curr->next;
  }
  no_of_players++;
}

void Game::insert_middle(int time, int reflex_time){
  simulate_game(time);
  Player* new_player = new Player(reflex_time, curr_player_no++);
  Player* temp = root;
  while(temp->next != player_holding_ball){
    temp = temp->next;
  }
  new_player->next = temp->next;
  temp->next = new_player;
  if(temp == curr){
    curr = new_player;
  }
  no_of_players++;
}

void Game::print(){
  Player* temp = root;

  cout<<"Printing Players: "<<endl;
  for(int i=0;i<no_of_players;i++){
    temp->print();
    temp = temp->next;
  }
  cout<<endl;
}

void Game::simulate_game(int time){
  int rem_time = time - elapsed_time; // time is always greater than elapsed_time 
  elapsed_time += rem_time;

  while(rem_time > 0){
    if(rem_time > rem_reflex_time){
      rem_time -= rem_reflex_time;
      player_holding_ball = player_holding_ball->next;
      rem_reflex_time = player_holding_ball->reflex_time;
    }else{
      rem_reflex_time -= rem_time;
      rem_time = 0;
    }
  }
}

void Game::print_player(int time){
  simulate_game(time);
  cout<<"Player "<<player_holding_ball->player_no<<" is holding the pillow at t="<<time<<endl;
}

bool Game::eliminate(int time){
  simulate_game(time);

  Player* prev = root;
  Player* temp = player_holding_ball;
  while(prev->next != temp){
    prev = prev->next;
  }

  prev->next = temp->next;
  if(temp == curr){
    curr = prev;
  }
  if(temp == root){
    root = temp->next;
  }
  cout<<"Player "<<temp->player_no<<" has been eliminated at t="<<time<<endl;
  player_holding_ball = temp->next;
  cout<<"Player "<<player_holding_ball->player_no<<" is holding the pillow at t="<<time<<endl;
  rem_reflex_time = player_holding_ball->reflex_time;
  delete temp;
  no_of_players--;

  if(root == curr){
    cout<<"Game Over: Player "<<root->player_no<<" wins!"<<endl;
    return true;
  }
  return false;
}

void Game::reverse(int time){
  simulate_game(time);

  Player* prev = nullptr;
  Player* current = root;
  Player* next = nullptr;

  do{
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }while(current != root);

  root->next = prev;
  root = prev;

  // Player* temp = root;
  // Player* prev = curr;
  // Player* next = nullptr;

  // bool curr_set = false;
  // do{
  //   next = temp->next;
  //   temp->next = prev;
  //   prev = temp;
  //   temp = next;
  //   if(!curr_set){
  //     curr = temp;
  //     curr_set = true;
  //   }
  // }while(temp != root);
}

void Game::finish(int time){
  simulate_game(time);
  cout<<"Game Over: Player "<<player_holding_ball->player_no<<" is holding the pillow at t="<<time<<", pillow passing sequence = Player ";
  Player* temp = player_holding_ball;
  do{
    if(temp->next != player_holding_ball) cout<<temp->player_no<<", ";
    else cout<<temp->player_no;
    temp = temp->next;
  }while(temp != player_holding_ball);
  cout<<endl;
}

Game::~Game(){
  if(!root) return;

  Player* temp = root->next;
  while(temp != root){
    Player* next_player = temp->next;
    delete temp;
    temp = next_player;
  }
  delete root;
}

int main(){
  // Player* player = new Player(3);
  // Player* player1 = new Player(5);
  // player->next = player1;

  // Player* temp = player;
  // while(temp != nullptr){
  //   cout<<temp->reflex_time<<" ";
  //   temp = temp->next;
  // }
  // cout<<endl;

  // temp = player;
  // while(temp != nullptr){
  //   temp = player->next;
  //   delete player;
  //   player = temp;
  // }

  // -------------------
  Game game(3);
  game.insert(4);
  game.insert(5);
  game.insert(2);

  game.print_player(6);
  game.eliminate(6);
  game.print_player(7);
  game.print_player(8);
  game.print_player(9);
  game.insert_middle(10, 1);
  game.print_player(12);
  game.print_player(13);
  game.print_player(15);
  game.print_player(17);
  game.reverse(22);
  game.print_player(23);
  game.print_player(24);
  game.finish(25);
  // --------------------

  // --------------------
  // Game game(3);
  // game.insert(4);
  // game.insert(5);
  // game.insert(2);

  // game.print_player(6);
  // game.eliminate(6);
  // game.print_player(6);
  // game.finish(7);
  // --------------------


  // --------------------
  // Game game(3);
  // game.insert(4);
  // game.insert(5);
  // game.insert(2);

  // game.reverse(5);
  // game.finish(6);
  // --------------------

  // --------------------
  // Game game(3);
  // game.insert(4);
  // game.insert(5);
  // game.insert(2);

  // game.eliminate(1);
  // if(game.eliminate(2)) return 0;
  // game.insert_middle(3, 5);
  // game.eliminate(5);
  // game.finish(10);
  // --------------------

  return 0;
}