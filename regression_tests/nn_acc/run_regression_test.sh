# !/bin/bash

cd ../../

rm -rf regression_tests/nn_acc/*_log

build/X86/gem5.opt --debug-flags=CombBase,SeqBase,CombWrite,CombRead,CombMult,SeqMult configs/nn_acc/comb_ex.py > regression_tests/nn_acc/comb_ex_log
tail -n +9 regression_tests/nn_acc/comb_ex_log > regression_tests/nn_acc/tmp
mv -f regression_tests/nn_acc/tmp regression_tests/nn_acc/comb_ex_log

diff --brief regression_tests/nn_acc/comb_ex_log regression_tests/nn_acc/comb_ex_gold
comp_value=$?

if [ $comp_value -eq 1 ]
then
    echo "Test comb_ex not pass!"
else
    echo "Test comb_ex pass!"
fi

build/X86/gem5.opt --debug-flags=CombBase,SeqBase,CombWrite,CombRead,CombMult,SeqMult configs/nn_acc/comb_vector_ex.py > regression_tests/nn_acc/comb_vector_ex_log
tail -n +9 regression_tests/nn_acc/comb_vector_ex_log > regression_tests/nn_acc/tmp
mv -f regression_tests/nn_acc/tmp regression_tests/nn_acc/comb_vector_ex_log

diff --brief regression_tests/nn_acc/comb_vector_ex_log regression_tests/nn_acc/comb_vector_ex_gold
comp_value=$?

if [ $comp_value -eq 1 ]
then
    echo "Test comb_vector_ex not pass!"
else
    echo "Test comb_vector_ex pass!"
fi

build/X86/gem5.opt --debug-flags=CombBase,SeqBase,CombWrite,CombRead,CombMult,SeqMult configs/nn_acc/comb_tree_ex.py > regression_tests/nn_acc/comb_tree_ex_log
tail -n +9 regression_tests/nn_acc/comb_tree_ex_log > regression_tests/nn_acc/tmp
mv -f regression_tests/nn_acc/tmp regression_tests/nn_acc/comb_tree_ex_log

diff --brief regression_tests/nn_acc/comb_tree_ex_log regression_tests/nn_acc/comb_tree_ex_gold
comp_value=$?

if [ $comp_value -eq 1 ]
then
    echo "Test comb_tree_ex not pass!"
else
    echo "Test comb_tree_ex pass!"
fi

build/X86/gem5.opt --debug-flags=CombBase,SeqBase,CombWrite,CombRead,CombMult,SeqMult configs/nn_acc/seq_tree_ex.py > regression_tests/nn_acc/seq_tree_ex_log
tail -n +9 regression_tests/nn_acc/seq_tree_ex_log > regression_tests/nn_acc/tmp
mv -f regression_tests/nn_acc/tmp regression_tests/nn_acc/seq_tree_ex_log

diff --brief regression_tests/nn_acc/seq_tree_ex_log regression_tests/nn_acc/seq_tree_ex_gold
comp_value=$?

if [ $comp_value -eq 1 ]
then
    echo "Test seq_tree_ex not pass!"
else
    echo "Test seq_tree_ex pass!"
fi

rm -rf regression_tests/nn_acc/*_log

cd -


