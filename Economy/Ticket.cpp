#include "Ticket.hpp"

Ticket::Ticket(QString ticketName)
{
    this->ticketName = ticketName;
}

Ticket::~Ticket()
{
    clear();
}

void Ticket::setName(const QString &name){
    this->ticketName = name;
}

QString Ticket::getName() const
{
    return this->ticketName;
}

float Ticket::getTotalCost(bool rounded) const{
    float total = 0;
    for (auto it=products.begin(); it!=products.end(); it++){
        total+=(*it)->getPrice();
    }

    if (rounded){
        total = round(total*100)/100;
    }

    return total;
}

Product* Ticket::addProduct(float price, std::vector<QString> buyers)
{
    return addProduct(Product(price,buyers));
}

Product* Ticket::addProduct(Product product){
    //Se devuelve un puntero al producto añadido para dar algo
    //de control al usuario sobre el producto.
    Product *pr = new Product(product);

    products.push_back(pr);

    return pr;

}

void Ticket::removeProduct(const Product *product){
    for (auto it = products.begin(); it!=products.end(); it++){
        if ((*it)==product){
            delete (*it);
            products.erase(it);
            break;
        }
    }
}

float Ticket::getPurchasePriceOf(QString name, bool rounded) const{
    float total = 0;
    for (auto it=products.begin(); it!=products.end(); it++){
        if ((*it)->buyedBy(name)){
            total+=(*it)->getPayout();
        }
    }

    if (rounded){
        total = round(total*100)/100;
    }

    return total;
}

void Ticket::clear(){
    for (unsigned int i = 0; i<products.size(); i++){
        delete products[i];
    }
    products.clear();
}

const Product *Ticket::productAt(int index) const{
return products[index];
}

unsigned int Ticket::countProducts() const{
    return products.size();
}

void Ticket::addPayer(QString name, float amount){
    //Se busca si el usuario ya es un pagador.
    for (unsigned int i=0; i<payers.size(); i++){
        if (payers[i].first==name){
            //Si ya es un pagador, se actualiza y se sale.
            payers[i].second = amount;
            return;
        }
    }
    //Si no se ha encontrado, se añade.
    payers.push_back(std::make_pair(name,amount));
}

std::vector<Debt> Ticket::computePayout(int *message) const
{
    //CATEGORIZACIÓN DE LOS USUARIOS

    //Usuarios negativos: han pagado demasiado y se les debe dinero.
    //Usuarios positivos: han pagado poco o nada y deben dinero.
    /*
     * Los usuarios se categorizarán y se aplicará un algoritmo que calcule
     * cuánto debe paga caga uno.
     * */
    std::vector<std::pair<QString,float>>negativeUser;

    float total = 0;
    for (unsigned int i = 0; i<payers.size(); i++){
        total+=payers[i].second;

        float neto = this->getPurchasePriceOf(payers[i].first)-payers[i].second;
        if (neto<0){
            negativeUser.push_back(std::make_pair(payers[i].first,payers[i].second));
        }
    }

    if (fabs(total-this->getTotalCost())>0.001){
        *message = MONEY_DOES_NOT_MATCH;
        return std::vector<Debt>();
    }

    std::vector<std::pair<QString,float>>positiveUser;

    //Los usuarios positivos serán aquellos que:
    // -No estén en el grupo de los negativos.
    // -Si es pagador, debe salir ganando aunque lo sea. Es decir, los usuarios con
    // una pérdida de 0 no serán ni negativos ni positivos.


    //Obtenemos la lista de compradores.
    QStringList buyers = this->getBuyers();

    //Y son estudiados individualmente.
    for (int i=0; i<buyers.size(); i++){
        //Guardamos lo que ha gastado.
        float spent = this->getPurchasePriceOf(buyers.at(i));
        bool isPayer = false;

        //Vamos a comprobar si es un pagador para aplicarle el descuento o no tenerlo en cuenta.
        for (unsigned int j=0; j<payers.size(); j++){
            if (buyers.at(i)==payers.at(j).first){
                isPayer=true;
                float payed = payers.at(j).second;

                float neto = spent-payed;
                if (neto>0){
                    positiveUser.push_back(std::make_pair(buyers[i],neto));
                }

                break;
            }
        }

        if (!isPayer){
            positiveUser.push_back(std::make_pair(buyers[i],spent));
        }

    }

    //ALGORITMO DE REPARTO

    std::vector<Debt>result;

    for (unsigned int i=0; i<negativeUser.size(); i++){
        //Paso 1: buscamos un usuario con un saldo negativo.

        float nUser = negativeUser[i].second;
        QString nUserName = negativeUser[i].first;

        //Paso 2: buscamos un usuario con saldo positivo que le de el dinero.
        for (unsigned int j=0; j<positiveUser.size(); j++){
            //Nos preguntamos, ¿este usuario puede pagar completamente al otro?
            float pUser = positiveUser[j].second;

            //Si el usuario ya no tiene ningún beneficio, significa que ya ha pagado
            //todo lo que podía. Se pasa al siguiente.
            if (pUser==0){
                continue;
            }

            QString pUserName = positiveUser[j].first;

            float incr = std::min(pUser,nUser);

            result.push_back(Debt(pUserName,incr,nUserName));

            nUser-=incr;
            pUser-=incr;

            positiveUser[j].second = pUser;
            negativeUser[i].second = nUser;

            if (nUser==0){
                //Si la deuda del usuario negativo ya ha sido pagada, pasamos al
                //siguiente usuario negativo.
                break;
            }

        }
    }
    *message = SUCCESS;
    return result;

}

std::vector<std::pair<QString,float>> Ticket::getPayers() const
{
    return this->payers;
}

float Ticket::getAmountPayedBy(QString name) const
{
    for (unsigned int i=0; i<payers.size(); i++){
        if (payers[i].first==name){
            return payers[i].second;
        }
    }
    return 0;
}

QStringList Ticket::getBuyers() const
{
    QStringList list;

    //Estudiamos cada producto.
    for (unsigned int i=0; i<products.size(); i++){
        //Obtenemos los compradores de cada producto.
        QStringList currentList = products[i]->getBuyers();
        //Los estudiamos individualmente.
        for (QString user : currentList){
            //Y, en el caso de que no estén ya en nuestra lista de retorno,
            //los añadimos.
            if (!list.contains(user)){
                list.append(user);
            }
        }
    }

    return list;
}



