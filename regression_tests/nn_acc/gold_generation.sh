# !/bin/bash

cd ../../

rm -rf configs/nn_acc/*_gold

build/X86/gem5.opt --debug-flags=CombBase,SeqBase,CombWrite,CombRead,CombMult,SeqMult configs/nn_acc/comb_ex.py > regression_tests/nn_acc/comb_ex_gold
tail -n +9 regression_tests/nn_acc/comb_ex_gold > regression_tests/nn_acc/tmp
mv -f regression_tests/nn_acc/tmp regression_tests/nn_acc/comb_ex_gold

build/X86/gem5.opt --debug-flags=CombBase,SeqBase,CombWrite,CombRead,CombMult,SeqMult configs/nn_acc/comb_vector_ex.py > regression_tests/nn_acc/comb_vector_ex_gold
tail -n +9 regression_tests/nn_acc/comb_vector_ex_gold > regression_tests/nn_acc/tmp
mv -f regression_tests/nn_acc/tmp regression_tests/nn_acc/comb_vector_ex_gold

build/X86/gem5.opt --debug-flags=CombBase,SeqBase,CombWrite,CombRead,CombMult,SeqMult configs/nn_acc/comb_tree_ex.py > regression_tests/nn_acc/comb_tree_ex_gold
tail -n +9 regression_tests/nn_acc/comb_tree_ex_gold > regression_tests/nn_acc/tmp
mv -f regression_tests/nn_acc/tmp regression_tests/nn_acc/comb_tree_ex_gold

build/X86/gem5.opt --debug-flags=CombBase,SeqBase,CombWrite,CombRead,CombMult,SeqMult configs/nn_acc/seq_tree_ex.py > regression_tests/nn_acc/seq_tree_ex_gold
tail -n +9 regression_tests/nn_acc/seq_tree_ex_gold > regression_tests/nn_acc/tmp
mv -f regression_tests/nn_acc/tmp regression_tests/nn_acc/seq_tree_ex_gold

cd -
