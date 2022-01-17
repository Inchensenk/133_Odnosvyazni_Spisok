﻿// 133_Odnosvyazni_Spisok.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//https://www.youtube.com/watch?v=SajrPhE6FoQ
/* Реализация методов односвязного списка из библиотеки STL:
    1.добавление в конец списка
    2.добавление в начало списка
    3.добавление в список по указанному индексу элемента
    4.удаление первого элемента
    5.удаление последнего элемента
    6.удаление по индексу
 */

#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

//Все методы, конструкторы и деструкторы будут реализованы вне класса, чтобы не загромождать класс
/*
Класс элемента списка будет вложенным в класс List и описан он будет в private секции, потому что этот элемент не должен быть на прямую доступен без класса List
назавем этот элемент Node (в переводе с англ. узел). Потому что наш элемент является узлом в цепочке элементов.

Так как наш класс Node будет доступен только внутри нашей private секции класса List, то мы можем незаморачиваться с инкапсуляцией, а просто реализавать все поля класса Node
в public секции, так как как разработчики, только мы сможем взаимодействовать напрямую с классом Node и каким-то образом контролировать состояние данных через геттер и сеттер
нам абсолютно не нужно, потому что этот класс больше никто нигде не увидит.

Так как мы реализовываем конкретный элемент который содержит данные и адрес, то и поля должны быть соответсвующие
адрес должен содержать адрес в памятим следующего элемента, по этому это должен быть указатель на тип Node, второе поле должно быть поле с данными
(с какого типа данными должен работать весь наш класс List и в частности наш элемент Node)

Чтобы не привязывать весь код к какому-то определенному типу данных, по тому что кода будет много и для каждого типа данных отдельно реализовывать этот код нет смысла,
 сделаем наш класс Node шаблонным и взаимодействие будет через поле обощенного типа (T)

 В конструкторе класса Node  нужно предусмотреть ьчастичную передачу данных, потому что к примеру при добавлении последнего элемента списка в конструкторе не будет указателя на следующий элемент
 и нам нужно будет жестко контролировать что у нас будет в этом указателе, для этого исползуем параметр по умолчанию (Node* pNext=nullptr). То есть по умолчанию у нас указатель
 на последний элемент будет указывать на nullptr, то есть никуда.

 Для поля data? если у нас к примеру та же самая ситуация, мы добавляем какой-то элемент, но нам просто нужно заранее подготовить этотэлемент в нашем списке, но данных у нас сейчас
 для него нету. При такой логике в поле data будет мусор, это очень нежелательно, поэтому мы можем также реализовать присваивание значения по умолчанию, но мы не знаем
 какой тип данных у нас здесь будет, это не проблема, так как можно использовать такую конструкцию T data=T()? эта конструкция работает следующим образом:
    если мы передадим класс,то у класса просто вызовится конструктор по умолчанию
    если мы передадим какой-то примитивный тип данных, то будет присвоено полю data значение по умолчанию этого примитивного типа данных
В любом случае, нам не особо важно что там будет, главное чтобы это был не мусор.

            С классом Node на данный момент мы пока закончили, теперь переходим к реализации организации взаимодействия узлов.
На прямую с классом Node взаимодействовать мы не можем, так как об этом классе знает только класс List именно по этому мы будем организовывать взаимодействие с Node  через класс List.

Для начала опредилимся какие поля будут храниться в классе List. Во первых когда мы обращаенмся к односвязному списку мы всегда должны знать о том, емть ли вообще у нас первый элемент.
потому что если у нас нету первого элемента то мы не можем начать идти по цепочке элементов и искать эдементы по какому-то индексу и добраться до последнего элемента.
Мы должны организовать в поле в котором будем хранить именно самый первый элемент нашего списка, а через него мы можем уже найти абсолютно любой элемент, потому что от
него будет идти цепочка с указателями на следующих своих соседей.

Мы назовем наш самый первый элемент Head (то есть голова с англ.). Из головы мы можем проследжить дальше в хвост весь наш список.
Если провести аналогию, то вот такая цепочка, чем-то похожа на игру змейка, где мы знаем о том что есть какая-то голова у змеи и от головы мы можем найти абсолютно любой
другой сегмент этой змеи, котороый идет за головой. 

Какого типа данных у нас будет эта голова? Она будет типа Node, но мы знаем что наш Node(узел) не привязан к какому-то конкретному типу данных, он у нас шаблонный.
По этому для того чтобы создать объект Node? который будет головой змеи, нужно указатьт ему какого типа данных он будет, на данный момент у нас есть возможность как то жестко тэто привязывать
Понятное дело что мы делали наш узел шаблонный для того чтобы жестко не привязывать этот тип. Какой выход из этой ситуации? Выход такой что наш класс List тоже должен быть шаблонным.
И тогда при создании обьекта Node мы будем передавать тот тип данных, с которым у нас был создан List.

Так как мы сделали класс List тоже шаблонным то и вынесенные конструктор и деструктор тоже должны быть шаблонными.

Голова списка head должна быть указателем, потому что все элементы односвязного списка будут выделяться в динамической памяти.
Нам еще понадобится поле которое будет хранить колличество элементов в нашем связанном списке, назовем его int size. Зачем нам хранить колличество элементов?
Если к примеру в нашем списке 1000 элементов, то нам нужно будет пройти по указателям адреса каждого элемента, что занимает долгий период времени, проще просто завести
переменную в которой мы будм обновлять при добавлении элемента или при удалении. К примеру добавили элемент, увеличили size на единицу, удалили элемент, уменьшили на единицу.
И в момет когда нам нужно узнать размер нашего списка, вместо того чтобы бежать по всему списку и считать эти элементы, му можем просто сразу возвращать значение этой переменной,
что гораздо быстрее. По этому переменная size нам необходима.

Сейчас на данный момент не наша переменная size не наш указатель на заголовок нашего списка head? не инициализированны, то есть там непонятно что.
Инициализация будет происходить в момент вызова конструктора List, в момент создания объекта. \
Реализация будет такова: 
    переменной будем присваивать 0 (size = 0;) Понятное дело что как только мы создали объект типа List у нас там еще нету элементов, по этому там и будет ноль.
    указателю head, который указывает на самый первый элемент списка, то есть на нулевой? у нас будет указывать на nullptr (head = nullptr;), таким образом мы 
будем точно знать что наш список на данный момент пуст.

По сути мы имеем уже некую заготовку нашего класса List, но мы пока ничего с ней делать не можем, поэтому реализуем методы.
Первым методом, будет метод push_back(название такое же как в библиотеке STL), который добавляет элемент в конец списка, точнее добавить данные в наш список, 
но реализовываться это будет через создание нового элемента и добавления его в конец. Принимает этот метод те самые наши данные которые мы будем добавлять в наш список.

Каким образом у нас будет реализовываться это добавление?
Во первых, мы должны проверить, есть ли что-то в заголовке нашего списка(в head), то естоь не пустой ли наш самый первый элемент, потому что если он пустой, то мы
должны его создать, а уже только потом добавлять какие-то элементы еще.

Мы знаем, если head у нас будет пустой, то он будет указывать на nullptr, то есть его просто не будет, потому что мы в нашем конструкторе пустому headу задаем указатель на nullptr.
Если наш head пустой, то мы должны создать новый элемент Node и передать ему в конструктор наши данные  head = new Node<T>(data);
Что делать в случае если head у нас будет не пустой, а там уже будут какой-то элемент, мы расмотрим чучуть позже.
Сейчас давайте сделаем вот что, мы уже можем создать объект нашего класса List (List<int> lst;) пусть он пока будет хранить целочисленные данные, назовем его lst 
и вызовем у нашего lst метод push_back и добавим туда значение 5 (lst.push_back(5)) 
Сделаем реализацию случая если head не пустой.
Во первых вызовим метод push_back еще раз и добавим туда 10 (lst.push_back(10)) и вернемся к реализации, если head не пуст то нам нужно создать новый элемент и присвоить адрес этого 
нового элемента самому последнему полю pNext? самому последнему адресу в нашем односвязном списке который указывает на nullptr.
Для этого нам понадобится временная переменная типа Node, это будет указатель на Node и назовем ее current? изначально мы сюда присваиваем значение нашего заголовка (Node<T>* current = this->head;)
Далее с помощью цикла while идти по всем нашим Node и искать самый последний, в условие цикла мы будем проверять на что указывает поле pNext, нашего текущего элемента,
текушего Node (узла) в котором мы находимся. если она не равна пустоте,
то в поле current мы будем присваивать указатель на следующий элемент (while (nullptr != current->pNext){current = current->pNext;})
и так до тех пор пока мы не найдем именно тот элемент, тот Node , у которого указатель pNext указывает на null.

Когда мы находим тот элемент у которого адрес указывает на null это значит что мы можем создавать новый объект типа Node и его адрес присвоить вместь NULL? то есть в конец нашего списка

Делать это мы будем после нашего списка while? когда поле pNext нашей текущей ноды в которой мы находимся уже будет равно nullptr  (current->pNext = new Node<T>(data);)
Для проверки реализации добавим несколько элементов в наш список (lst.push_back(5); lst.push_back(10); lst.push_back(22);)

Так как у нас после метода push_back колличество элементов в нашем списоке увеличивается на 1 то и size увеличиваем на 1 (size++;)
Так же нам нужно для переменной size написать геттер ( int GetSize() {return size}) потому что она в приват секции и мы ничего с ней делать не можем
Теперь в любой нужный нам момент у нашего списка мы можем получить значение size то есть колличество узлов.
К примеру если мы выведем наш size(cout<<lst.GetSize()<<endl;) после того как добавим в наш список 3 элемента(lst.push_back(5); lst.push_back(10); lst.push_back(22);)
Мы увидим что сосотояние о колличестве элементов у нас корректно отоброжается (в консоли выведется число 3)

Мы с вами реализовали добавление элементов, но как теперь нам получить доступ к такому элементу? Итерироваться по нашему списку мы будем с помощью оператора [].
Абсолютно так же как мы работали с массивом, но только это у нас будет список. для этого нам нужно собственно перегрузить [].
Прототип этого метода будет выглядеть вот так: (T& operator[](const int index);). Мы будем возващать ссылку на тип T, имеено ссылку потому что нам те данные которые мы будем возвращать
иметь возможность еще и изменять, а не только возвращать. синтаксис перегрузки оператора стандартный(ключевое слово operator, название оператора и принимаемым параметром у нас будет индекс)
Индекс- это номер того элемента который мы должны вернуть, то есть если бы это был массив и мы передали в квадратные скобки 0, то мы хотели бы получить 0-ой элемент,
так же точно это будет работать и с нашим односвязным списком только нам этот момент нужно самостоятельно реализовать.

Как должна работать реализация этого метода? К примеру нам нужно найти 2-й элемент, мы начинаем с headera 0-го элемента и у нас должна быть перменная счетчик которая будет считать,
в каком конкретном элементе мы сейчас находимся. и так мы заходим с хедера переходим в мледующий элемент и увеличиваем счетчик на единицу это уже 2ой элемент и если значение нашего счетчика то есть 2
совпвдает с индексом, котрый мы передали в параметр ([]), то мы должны вернуть данные этого узла. 

T& List<T>::operator[](const int index){Node<T>* current = this->head;} 
Временный объект current будет отвечать за то, в какой конкретно узле мы находимся, чтобы проверить адрес следующего элемента
Так же нам потребуется счетчик (int counter=0;)? который будет считать в каком элементе мы находимся в данный момент(по умолчанию, так как мы идем с самого начала списка этот счетчик равен нулю)
Далее у нас будет идти работа цикла while? который будет работать до тех пор пока указатель на текущую ноду не будет nullptr 
В цикле будет выполняться проверка, если значение нашего счетчика = индексу, то значит мы нашли нужный нам элемент и нам нужно его вернуть
вызываем оператор return и у нашего текущего элемента у current заберем данные из поля data, если же это условие не выполнилось значит мы еще не нашли нужный нам элемент
В таком случае в переменную, которая отвечает за то какой у нас текущий узел на данный момент, присвоим адрес следующего элемента, для этого мы у этой же переменной у текущего элемента, спросим адрес его следующего 
элемента, а счетчик counter увеличим на единицу? потому что мы уже перешли на следующий элемент
while (nullptr!=current) { if (inde[ == counter) {return current->data;} current = current->pNext; counter++;} эта логика будет работать до тех пор пока наша переменная current
не станет указывать на nullptr, так как в таком случае мы в конце списка и уже нечего искать, если мы укажем элемент индексом больше че у нас есть то мы выдем за гранпицы списка иполучим ошибку
Теперь чтобы вывести элемент списка делаем то же самое что и с массивами (cout<<lst[2]<<endl;) то есть обращаюсь ко второму элементу через [] и входящим элементом является индекс 
и мы должны найти такой же элемент который находится в нашем односвязном списке под индексом 2.

Теперь выводим все данный с помощью цикла for: 
когда мы работали с массивами нам нужно было, где-то отдельно хранить, в случае с динамическими данными и STL нам этого делать не нужно, потому что у нас наш список хранитколличество элементов из
которого у нас он состоит, у нас есть поле size которое за это отвечает и спомощью метода getSize мы можем прямо в цикле получать это значение

//если текущий индекс меньше чем колличество элементов в списке, то мы можем итерироваться по нему дальше
    for (size_t i = 0; i < lst.GetSize(); i++)
    {
        //вывод элементов списка
        cout << lst[i] << endl;
    } 

  Теперь организуем заполнение нашего листа с помощью случайных чисел:
  за то сколько будет этих чисел будет отвечать переменная int numbersCount; и будем вводить ее через cin, наш цикл отработает колличество итераций равных numbersCount

  int numbersCount;
    cin>> numbersCount;

    for (size_t i = 0; i < numbersCount; i++)
    {
        lst.push_back(rand() % 10);
    }

  урок 134 https://www.youtube.com/watch?v=8E6cPXE-IIA

  Организуем освобождение ресурсов, после того как список нам больше не будет нужен, тоесть когда объект типа list выходит из зоны видимости функции либо когда мы его просто уничтожаем в другой ситуации
  Зачем это нужно? Каждый элемент, который создается в списке, выделяется в динамической памяти с помощью оператора new но мы нигде не позаботились о том чтобы память, которая была выделена динамически под наши
  элементы, освобождать, по этому по сути когда мы работаем с односвязным списком в текущей реализации, мы каждый раз добавляя элемент в такой список получаем утечку памяти, потому что мы никогда, нигде эту память не освобождаем

  Как реализовать очистку памяти? Нам нужно с помощью адресов, пробежаться по всем элементам и удалить их.
  Самая простая реализация может быть сделана таким образом, если мы начнем удаление сначала, тоесть с самого первого элемента, потому что над ним операции в односвязном списке будут выполняться быстрее всего
  Благодаря такому подходу, мы косвенно реализуем такую задачу, в STL у динамических структур данных есть такой метод как pop_front и задачей этого метода состоит в том чтобы удалить самый первый элемент коллекции
  В данном случае нашей коллекцией элементов выступает наш односвязный список, поэтому мы реалиуем метод pop_front, а затем используем этот метод для реализации освобождения динамической памяти
  из всего нашего односвязного списка, если просто сделать delete head? то мы потерям связь со всеми элементами, так как list всегда через head ищет остальные элементы, поэтому после удаления head нужно переназначить headом следующий элемент
  
  template<typename T>
void List<T>::pop_front()
{
    //временный обьект temp хранящий адрес нулевого элеммента списка head
    Node<T> *temp = head;
    //присваиваем head адрес следующего элемента и по сути head-ом станет не 0-ой а первый элемнт а нулевой элемент мы просто запомнили во временной переменной temp
    head = head->pNext;
    //и теперь можно спокойно удалить наш бывший head
    delete temp;
    //уменьшаем счетчик элементов на единицу, после удаления нулевого элемента
    size--;
}

После тогокак мы реализовали метод pop_front, мы можем организовать и очистку всего списка, просто удаляя элементы из начала списка, а это самая быстрая операция, до тех пор 
пока у нас в списке просто будут элементы, когда у нас останется 0 элементов, мы прекратим выполнение такой операции.
В STL существует метод clear, который осущевствляет очистку памяти от динамических структур. Просто поместим в цикл метод pop_front()

template<typename T>
void List<T>::clear()
{
    //size целочисленное значение, а цикл while своим условием принимает булевое значение
    //когда мы передаем целочисленную переменную, в цикл, осуществляется преобразование целочисленной переменной в булевую
    //и любое значение большее или меньшее нуля будет true, а ноль это будет false
    //тоесть когда размер списка будет равен нулю, мы выйдем из списка
    while (size)
    {
        pop_front();
    }
}

Теперь можно использовать метод clear в деструкторе. Когда наш односвязный список будет выходить из зоны действия функции или будет уничтожаться каким-то другим образом, 
то в момент выхода из функции main  объект lst вызовет свой деструктор

Урок #135 https://www.youtube.com/watch?v=tj17qdFMj54
Наам осталось реализовать методы:
push_front- добавляет элемент в начало списка
pop_back- удаляет элемент с конца списка
insert - вставляет новый элемент по индексу и если по этому индексу уже есть элемент то он сдвигается а на его место вставляется новый
removeAt - удаление элемента из списка по указанному индексу

push_front():
для добавления нового элемента в список, нужно сначало его создать, затем сделать его head и в поле адреса нового head указать адрес старого head 
template<typename T>
void List<T>::push_front(T data)
{
    //для указателя создаем новый элемент котрый хранится в динамической памят
    head = new Node<T>(data, head);//new Node<T>(data)- создание нового элемента; эта запись (head =) говорит  что наш новый элемент становится head
    size++;
}

в конструкторе у Node принимаются 2 параметра значение и адрес, по умолчанию адрес nullptr, а так как нам в этот адрес нужно засунуть адрес старого head, то вторым параметром закидываем старый head 

head = new Node<T>(data, head); здесь очень важно понимать порядок того что за чем выполняется:
Изначально должен создаться объект в динамической памяти (new Node<T>()) чтобы мы могли присвоить его head
На момент создания этого объекта мы ему параметрами передаем информацию из поля data, которая была входящим параметром метода push_front, а также указатель на текущий head 
new Node<T>(data, head)? если он был nullptr, то есть не было еще элемента в списке, ничего страшного, просто мы добавим 1 элемент и его поле next будет указывать на null 
как будто у нас просто единственный элемент в списке, если нет то поле адреса нового элемента будет указывать на следующий элемент


insert():
Мы должны будем указать данные которые хотим указать и индекс по которому мы добавляем эти данные.
Для начала нужно добраться до элемента с таким индексом под которым мы хотим сделать вставку.
Прежде чем создавать новый элемент и помещать его под какимто индексом, нужно найти элемент с предыдущим индексом и сделать так чтобы он ссылался на новый элемент

template<typename T>
void List<T>::insert(T data, int index)
{
    if (0==index)
    {
        push_front(data);
    }
    else
    {
        //создаем временный указатель типа Node *previus и присваиваем ему значение head
        Node<T> *previus = this->head;
        //цикл для нахождения элемента с индексом предшествующему индексу передаваемому в параметр, то есть индексу на место которого мы хотим поместить новый объект
        //цикл будет проходить пока не доберется до предшествующего индекса (i < index - 1;)
        for (size_t i = 0; i < index - 1; i++)
        {
            //во временную переменную присваем указатель на следующую ноду нашего списка
            previus = previus->pNext;
        }
        //После отработки цикла, переменная previos будет содержать адрес того элемента который предшествует тому индексу элемента по которому мы хотим добавить новый элемент
        //к примеру если мы добавляем элемент под индексом 1, то переменная previos будет содержать значение и данные элемента 0

        //Создаем новый объект типа Node, передаем ему в конструктор данные и у предыдущего элемента берем поле pNext
        //на момент когда мы выполняем эту операцию список находится в таком состоянии: мы создали новый объект, но он у нас висит в воздухе
        //и мы с помощью этого кода previus->pNext обращаемся к переменной previos и ее полю pNext и значение поля адреса у нулевого элемента мы присваиваем полю нового элемента
        //то есть по сути теперь и нулевой и первый узел указывают на второй узел
        Node<T>* newNode = new Node<T>(data, previus->pNext);

        //присваем полю адреса нулевого узла адрес нового объекта, что бы он теперь указывал на вставленный объект
        previus->pNext = newNode;

        
        //увеличиваем счетчик
        size++;
    }
}

Эти 2 строки можно упростить(они для лучшего понимания что происходит)
Node<T>* newNode = new Node<T>(data, previus->pNext);
previus->pNext = newNode;

И тогда они примут вид(обычно пишут так): previus->pNext = new Node<T>(data, previus->pNext);


Удаление узла по индексу removeAt():
template<typename T>
void List<T>::removeAt(int index)
{
    //если индекс равен нулю
    if (0==index)
    {
        //то удаляем нулевой узел
        pop_front();
    }
    else
    {
#pragma region Нахождение предыдущего элемента относительно искомого индекса
        //Если бы это был реальный проект, то эту часть кода нужно было бы вынести в отдельный метод, так как он повторяется в нескольких методах, но для понимания лучше оставить так
        Node<T>* previous = this->head;
        for (size_t i = 0; i < index-1; i++)
        {
            previous = previous->pNext;
        }
#pragma endregion
        //предыдущему элементу указываем адрес элемента находящегося после элемента который мы удаляем
        //то есть поле адреса(адрес элемента стоящего после удаляемого) удаляемого узла передаем полю адреса узла стоящим перед удаляемым, чтобы связь в списке не нарушилась
        //переменная toDelete нужна, чтобы найти удаляемый элемент, так как после измения указателя у поля узла стоящим перед удаляемым узлом на адрес стоящего после удаляемого узла
        //если не сохранить адрес удаляемого узла, мы не сможем его найти и удалить, по этому переменная toDelete хранит адрес удаляемого узла
        Node <T>* toDelete = previous->pNext;
        //присваиваем предыдущему узлу адрес узла стоящего после удаляемого
        previous->pNext = toDelete->pNext;
        //очищаем память
        delete toDelete;
        //уменьшаем счетчик
        size--;
    }
}
удаление с конца списка pop_back():
для этого используем предыдущий метод и передаем ему индекс последнего элемента списка
template<typename T>
void List<T>::pop_back()
{
    removeAt(size-1);
}

*/
template <typename T>
class List
{
public:
    //конструктор
    List();
    //деструктор
    ~List();
    //удаляет нулевой элемент списка
    void pop_front();
    //добавление элемента в конец списка
    void push_back(T data);
    //очистка данных динамического списка
    void clear();
    //геттер возвращающий колличество элементов в списке 
    int GetSize() { return size; }
    //перегруженный оператор индексации, который по индексу возвращает данные из списка, которые находятся под этим индексом
    T& operator[](const int index);
    //добавляет ноду в начало списка
    void push_front(T data);
    //вставляет элемент по индексу
    void insert(T value, int index);
    //удаление по индексу
    void removeAt(int index);
    //удаление с конца списка
    void pop_back();
private:
    //вложенный класс Node, хранящий данные и указатель элемента списка
    template <typename T>
    class Node
    {
    public:
        //указатель типа Node с названием pNext (pointer next), хранящий адрес следующего элемента
        Node* pNext;
        //T - поле обобщенного типа
        T data;

        //конструктор узла
        Node(T data=T(), Node* pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }
    };
    int size;
    Node<T> *head;
};

template <typename T>
List<T>::List()
{
    //size хранит колличество элементов в односвязном списке 
    size = 0;
    //head указывает нга самый первый элемент списка, то есть ноду, то есть узел, то есть 0 элемент при индексации
    head = nullptr;
}

template <typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
void List<T>::pop_front()
{
    //временный обьект temp хранящий адрес нулевого элеммента списка head
    Node<T> *temp = head;
    //присваиваем head адрес следующего элемента и по сути head-ом станет не 0-ой а первый элемнт а нулевой элемент мы просто запомнили во временной переменной temp
    head = head->pNext;
    //и теперь можно спокойно удалить наш бывший head 
    delete temp;
    //уменьшаем счетчик элементов на единицу, после удаления нулевого элемента
    size--;
}

template<typename T>
void List<T>::push_back(T data)
{
    //проверка на наличие первого элемента head, пустой он или нет?
    //Если наш head пустой
    if (nullptr == head)
    {
        //то мы создаем новый элемент Node и передаем ему в конструктор наши данные
        head = new Node<T>(data);
    }
    else
    {
        Node<T>* current = this->head;
        //если текущий элемент(узел) не равен пустоте
        while (nullptr != current->pNext)
        {
            //то в поле current присваиваем указатель на следующий элемент(узел)
            current = current->pNext;
        }
        current->pNext = new Node<T>(data);
    }
    size++;
}

template<typename T>
void List<T>::clear()
{
    //size целочисленное значение, а цикл while своим условием принимает булевое значение
    //когда мы передаем целочисленную переменную, в цикл, осуществляется преобразование целочисленной переменной в булевую
    //и любое значение большее или меньшее нуля будет true, а ноль это будет false
    //тоесть когда размер списка будет равен нулю, мы выйдем из списка
    while (size)
    {
        pop_front();
    }
}

template<typename T>
T& List<T>::operator[](const int index)
{
    //инициализируем счетчик 0-м, это значит, что мы сейчас находимся в 0-м элементе 
    int counter = 0;
    //в указатель, который отвечает за текущий элемент в котором мы находимся, просто присваиваем значение нашего heada? потому что мы с него всегда начинаем поиск
    Node<T>* current = this->head;
    //пока current !=0 (текущий элемент!=0)
    while (nullptr!=current)
    {
        //проверяем совпадение счетчика с индексом который нам нужно искать
        if (index == counter)
        {
            //еслии значение совпало то возвращаем данные которые находятся в текущей ноде узле элементе и так далее
            return current->data;
        }
        //если не совпадает, присваеваем в текущий элемент поле следующего элемента
        current = current->pNext;
        //значение счетчика увеличиваем на единицу
        counter++;
    }
}

template<typename T>
void List<T>::push_front(T data)
{
    //для указателя создаем новый элемент котрый хранится в динамической памят
    head = new Node<T>(data, head);
    size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
    if (0==index)
    {
        push_front(data);
    }
    else
    {
        //создаем временный указатель типа Node *previus и присваиваем ему значение head 
        Node<T> *previus = this->head;
        //цикл для нахождения элемента с индексом предшествующему индексу передаваемому в параметр, то есть индексу на место которого мы хотим поместить новый объект
        //цикл будет проходить пока не доберется до предшествующего индекса (i < index - 1;)
        for (size_t i = 0; i < index - 1; i++)
        {
            //во временную переменную присваем указатель на следующую ноду нашего списка
            previus = previus->pNext;
        }
        //После отработки цикла, переменная previos будет содержать адрес того элемента который предшествует тому индексу элемента по которому мы хотим добавить новый элемент
        //к примеру если мы добавляем элемент под индексом 1, то переменная previos будет содержать значение и данные элемента 0

        //Создаем новый объект типа Node, передаем ему в конструктор данные и у предыдущего элемента берем поле pNext
        //на момент когда мы выполняем эту операцию список находится в таком состоянии: мы создали новый объект, но он у нас висит в воздухе
        //и мы с помощью этого кода previus->pNext обращаемся к переменной previos и ее полю pNext и значение поля адреса у нулевого элемента мы присваиваем полю нового элемента
        //то есть по сути теперь и нулевой и первый узел указывают на второй узел
        Node<T>* newNode = new Node<T>(data, previus->pNext);

        //присваем полю адреса нулевого узла адрес нового объекта, что бы он теперь указывал на вставленный объект
        previus->pNext = newNode;
        //увеличиваем счетчик
        size++;
    }
}

template<typename T>
void List<T>::removeAt(int index)
{
    //если индекс равен нулю
    if (0==index)
    {
        //то удаляем нулевой узел
        pop_front();
    }
    else
    {
#pragma region Нахождение предыдущего элемента относительно искомого индекса
        //Если бы это был реальный проект, то эту часть кода нужно было бы вынести в отдельный метод, так как он повторяется в нескольких методах, но для понимания лучше оставить так
        Node<T>* previous = this->head;
        for (size_t i = 0; i < index-1; i++)
        {
            previous = previous->pNext;
        }
#pragma endregion
        //предыдущему элементу указываем адрес элемента находящегося после элемента который мы удаляем
        //то есть поле адреса(адрес элемента стоящего после удаляемого) удаляемого узла передаем полю адреса узла стоящим перед удаляемым, чтобы связь в списке не нарушилась
        //переменная toDelete нужна, чтобы найти удаляемый элемент, так как после измения указателя у поля узла стоящим перед удаляемым узлом на адрес стоящего после удаляемого узла
        //если не сохранить адрес удаляемого узла, мы не сможем его найти и удалить, по этому переменная toDelete хранит адрес удаляемого узла
        Node <T>* toDelete = previous->pNext;
        //присваиваем предыдущему узлу адрес узла стоящего после удаляемого
        previous->pNext = toDelete->pNext;
        //очищаем память
        delete toDelete;
        //уменьшаем счетчик
        size--;
    }
}

template<typename T>
void List<T>::pop_back()
{
    removeAt(size-1);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List<int> lst;
    lst.push_front(5);
    lst.push_front(7);
    lst.push_front(101);
    
    //если текущий индекс меньше чем колличество элементов в списке, то мы можем итерироваться по нему дальше
    for (size_t i = 0; i < lst.GetSize(); i++)
    {
        //вывод элементов списка
        cout << lst[i] << endl;
    }
    cout << endl << "выполняю метод pop_back" << endl << endl;

    lst.pop_back();

    // если текущий индекс меньше чем колличество элементов в списке, то мы можем итерироваться по нему дальше
        for (size_t i = 0; i < lst.GetSize(); i++)
        {
            //вывод элементов списка
            cout << lst[i] << endl;
        }
    
    /*cout << endl << "Элементов в списке " << lst.GetSize() << endl << "выполняю метод clear" << endl << endl;
    lst.clear();
     
    cout << endl << "Элементов в списке " << lst.GetSize() << endl;*/

    /*int numbersCount;
    cout << "Введите колличесво элементов списка: ";
    cin>> numbersCount;

    for (size_t i = 0; i < numbersCount; i++)
    {
        lst.push_back(rand() % 110);
    }*/
}


