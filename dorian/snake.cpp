#include "snake.hpp"
#include "MainSDLWindow.hpp"
#include "playground.hpp"

Segment::Segment(int row, int col, Direction direction, Segment* next){
    this->row = row;
    this->col = col;
    this->direction = direction;
    this->next = next;
}

Segment::~Segment(){

}

int Segment::GetRow(void){
    return row;
}

int Segment::GetCol(void){
    return col;
}

Direction Segment::GetDirection(void){
    return direction;
}

Segment* Segment::GetNext(void){
    return next;
}

void Segment::SetNext(Segment* nextSegment){
    next = nextSegment;
}

void Segment::SetDirection(Direction newDirection){
    direction = newDirection;
}

Snake::Snake(int startingRow, int startingCol, Direction startingDirection, int length){

    Segment* segment = NULL;
    for(int i=length-1;i>0;i--){ // on part de la queue du serpent jusqu'au dernier segment avant la tête
        switch (startingDirection){
            case RIGHT:
                segment = new Segment(startingRow, startingCol-i, startingDirection, segment);
                break;
            case LEFT:
                segment = new Segment(startingRow, startingCol+i, startingDirection, segment);
                break;
            case DOWN:
                segment = new Segment(startingRow-i, startingCol, startingDirection, segment);
                break;
            case UP:
                segment = new Segment(startingRow+i, startingCol, startingDirection, segment);
                break;
        }

        if(i==length-1){ // si on est à la première itération, on est donc à la queue
            tail = segment;
        }
    }

    head = new Segment(startingRow, startingCol, startingDirection, segment);
}

Snake::~Snake(){

}

void Snake::ChangeDirection(Direction newDirection){
    Direction current_direction = head->GetDirection();
    if((newDirection == LEFT and current_direction != RIGHT) || (newDirection == RIGHT and current_direction != LEFT)){
        head->SetDirection(newDirection);
    }
    else if((newDirection == UP and current_direction != DOWN) || (newDirection == DOWN and current_direction != UP)){
        head->SetDirection(newDirection);
    }
}

bool Snake::Move(Playground* playground){
    Direction directionToMove = head->GetDirection();
    switch (directionToMove){
        case RIGHT:
            if(head->GetCol() == playground->GetNbCols()-1){
                return false;
            }
            head = new Segment(head->GetRow(), head->GetCol()+1, directionToMove, head);
            break;
        case LEFT:
            if(head->GetCol() == 0){
                return false;
            }
            head = new Segment(head->GetRow(), head->GetCol()-1, directionToMove, head);
            break;
        case DOWN:
            if(head->GetRow() == playground->GetNbRows()-1){
                return false;
            }
            head = new Segment(head->GetRow()+1, head->GetCol(), directionToMove, head);
            break;
        case UP:
            if(head->GetRow() == 0){
                return false;
            }
            head = new Segment(head->GetRow()-1, head->GetCol(), directionToMove, head);
            break;
    }

    Segment* actualSegment = head;
    Segment* previousSegment = nullptr;
    while (actualSegment->GetNext() != nullptr){
        previousSegment = actualSegment;
        actualSegment = actualSegment->GetNext();
    }

    if (previousSegment != nullptr){
        previousSegment->SetNext(nullptr);
        tail = previousSegment;
        delete actualSegment;
    }

    return true;
}

bool  Snake::TestCollisions(Playground* playground){
    int leftLimit = -1;
    int topLimit = -1;
    int rightLimit = playground->GetNbCols();
    int bottomLimit = playground->GetNbRows();

    // Test collision avec les bords du playground //
    if(head->GetCol() >= rightLimit){
        return false; // game over //
    }
    else if(head->GetCol() <= leftLimit){
        return false; // game over //
    }

    if(head->GetRow() >= bottomLimit){
        return false; // game over //
    }
    else if(head->GetRow() <= topLimit){
        return false; // game over //
    }

    // Test collisions de la tête avec la queue du serpent //

    // Test collision avec un fruit --> le manger //

    return true; // la partie peut continuer //
}


void Snake::draw(MainSDLWindow* mainWindow, int tile_size){
    Segment* actual_segment = head;
    while(actual_segment != nullptr)
    {
        SDL_Renderer* mainWindowRenderer = mainWindow->GetRenderer();
        SDL_Rect playground = mainWindow->GetPlaygroundZone();
        SDL_SetRenderDrawColor(mainWindowRenderer, 255, 255, 255, 255);
        SDL_RenderSetViewport(mainWindowRenderer, &playground);
        SDL_Rect rectToDraw = {actual_segment->GetCol()*tile_size, actual_segment->GetRow()*tile_size, tile_size, tile_size};
        SDL_RenderFillRect(mainWindowRenderer, &rectToDraw);
        actual_segment = actual_segment->GetNext();
    }
}