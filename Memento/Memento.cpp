#include <iostream>
#include <string>
#include <vector>


class Memento {
private:
    std::string state;

public:
    explicit Memento(const std::string& state) : state(state) {}
    std::string getState() const { return state; }
};


class TextEditor {
private:
    std::string text;

public:
    void write(const std::string& newText) {
        text += newText;
    }

    std::string getText() const {
        return text;
    }

    
    Memento save() const {
        return Memento(text);
    }


    void restore(const Memento& memento) {
        text = memento.getState();
    }
};


class History {
private:
    std::vector<Memento> snapshots;

public:
    void save(const Memento& memento) {
        snapshots.push_back(memento);
    }

    Memento undo() {
        if (snapshots.empty()) {
            throw std::out_of_range("Історія порожня!");
        }
        Memento lastSnapshot = snapshots.back();
        snapshots.pop_back();
        return lastSnapshot;
    }
};


int main() {
    TextEditor editor;
    History history;

    editor.write("Привіт, ");
    history.save(editor.save()); 

    editor.write("світ!");
    std::cout << "Текст: " << editor.getText() << std::endl;

    history.save(editor.save()); 

    editor.write(" Як справи?");
    std::cout << "Текст: " << editor.getText() << std::endl;


    editor.restore(history.undo());
    std::cout << "Відновлений текст: " << editor.getText() << std::endl;


    editor.restore(history.undo());
    std::cout << "Відновлений текст: " << editor.getText() << std::endl;

    return 0;
}
