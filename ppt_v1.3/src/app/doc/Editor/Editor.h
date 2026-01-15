#pragma once
#include <deque>
#include "Action.h"
namespace doc {
    class Editor
    {
    public:
        Editor()= default;
        Editor(std::shared_ptr<Ppt> doc) : doc(doc) {}
        void set_file(std::shared_ptr<Ppt> doc) {
            this->doc = doc;
        }
        std::shared_ptr<Ppt> get_doc() const {
            return doc;
        }
        void carry_out(std::shared_ptr<IAction> action) {
            undo_stack.push_front(action->carry_out(doc));
        }

        void undo(){
            redo_stack.push_front(undo_stack.front()->carry_out(doc));
            undo_stack.pop_front();
        }

        void redo(){
            undo_stack.push_front(redo_stack.front()->carry_out(doc));
            redo_stack.pop_front();
        }

    private:
        std::shared_ptr<Ppt> doc;
        std::deque<std::shared_ptr<IAction>> undo_stack;
        std::deque<std::shared_ptr<IAction>> redo_stack;
        
    };
    
}