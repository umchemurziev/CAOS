#include <future>
#include <thread>
#include <vector>

template <typename Function, typename Input, typename Output>
void process_element(Input x, Function &&f, std::promise<Output> *p)
{
    p->set_value(f(x));
}

template <class Input, class Output, class Function, class Callback>

void process_vector(const std::vector<Input> &&ins, Function &&f, Callback &&c)
{
    std::vector<Output> outs(ins.size());
    std::vector<std::promise<Output>> promises(ins.size());

    for (size_t i = 0; i < ins.size(); ++i)
    {
        std::thread thr(
            process_element<Function, Input, Output>,
            ins[i],
            f,
            &promises[i]);
        thr.detach();
    }

    for (size_t i = 0; i < ins.size(); ++i)
    {
        outs[i] = promises[i].get_future().get();
    }
    c(outs);
}

template <class Input, class Output, class Function, class Callback>

void async_vector(const std::vector<Input> ins, Function &&f, Callback &&c)
{
    std::thread thr(
        process_vector<Input, Output, Function, Callback>, ins, f, c);
    thr.detach();
}

// Решение взято с семинара
