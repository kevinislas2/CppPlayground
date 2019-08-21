
/*
Demonstration of neural networks using composite design pattern.
*/

#include <iostream>
#include <vector>

using namespace std;

// CRTP (Curiously recurrent template pattern)

// Forward declare SomeNeurons
template <typename Self>
struct SomeNeurons {
    template <typename T> void connect_to(T& other);
};

struct Neuron : SomeNeurons<Neuron>
{
    vector<Neuron*> in, out;
    unsigned int id;

    Neuron() {
        static int id{1};
        this->id = id++;
    }

    Neuron* begin() { return this;}
    Neuron* end() {return this+1;}

    friend ostream &operator<<(ostream &os, const Neuron &neuron) {
        for (Neuron* n : neuron.in) {
            os << n->id << "\t-->\t[" << neuron.id << "]\n";
        }

        for (Neuron* n : neuron.out) {
            os << "[" << neuron.id << "]\t-->\t" << n->id << "\n";
        }

        return os;
    }
};

struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer> {           // Not recommended to inherit from std since they do not have virtual destructors

    NeuronLayer(int count)
    {
        while (count --> 0){
            emplace_back(Neuron{});
        }
    }

    friend ostream &operator<<(ostream &os, const NeuronLayer &obj) {
        for (auto& n : obj) {
            os << n;
        }

        return os;
    }
};

template <typename Self>
template <typename T>
void SomeNeurons<Self>::connect_to(T& other) {
    Self *This = static_cast<Self*>(this);              // This ensures that the actual type is used within the for loop;

    for (Neuron& from : *This) {
        for (Neuron& to : other) {
            from.out.push_back(&to);
            to.in.push_back(&from);
        }
    }
}

int main()
{

    Neuron n1, n2;
    n1.connect_to(n2);              //1.- Neuron->Neuron

    cout << n1 << n2 << '\n';

    NeuronLayer layer1{2}, layer2{3};
    
    n1.connect_to(layer1);          //2.- Neuron->Layer
    layer1.connect_to(n1);          //3.- Layer->Neuron
    layer1.connect_to(layer2);      //4.- Layer->Layer

    return 0;
}