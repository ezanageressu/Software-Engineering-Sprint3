#include <iostream>
#include "intelligence.h"

Intelligence::Intelligence(){
    this->intelligenceIsActive = false;
    this->intelligenceBalance = 0;
}

void Intelligence::increaseIntelligence(){
    if(this->intelligenceBalance<200){
        this->intelligenceBalance++;
    }
}

