#include "BlockChain.h"

BlockContents::BlockContents(int block_number, std::string parent_hash, int transaction_count,
                             std::list<std::map<int, int>> transactions)
{
    this->block_number = block_number;
    this->parent_hash = parent_hash;
    this->transaction_count = transaction_count;
    this->transactions = transactions;
}

std::string BlockContents::hash_contents()
{
    std::string hash_transactions;
    std::string hash_contents;

    std::string to_hash = "";
    for (auto it = transactions.begin(); it != transactions.end(); it++) {
        for (auto map_it = it->begin(); map_it != it->end(); map_it++) {
            to_hash += std::to_string(map_it->first) + "." + std::to_string(map_it->second);
        }
    }

    sha256::hash256_hex_string(to_hash, hash_transactions);

    to_hash = std::to_string(block_number) + "." + parent_hash + "." + std::to_string(transaction_count) + "." +
                          hash_transactions;

    sha256::hash256_hex_string(to_hash, hash_contents);

    return hash_contents;
}

BlockContents::BlockContents(const BlockContents &contents)
{
    this->block_number = contents.block_number;
    this->parent_hash = contents.parent_hash;
    this->transaction_count = contents.transaction_count;
    std::copy(contents.transactions.begin(), contents.transactions.end(), this->transactions.begin());
}

Block::Block(std::string new_hash, BlockContents new_contents) : contents(new_contents)
{
    this->block_hash = new_hash;
}

BlockChain::BlockChain()
{
    std::map<int, int> state = {{1, 5},
                                {2, 5}};
    std::list<std::map<int, int>> genesis_block_transactions;
    genesis_block_transactions.push_back(state);

    BlockContents genesis_block_contents(0, "", 1, genesis_block_transactions);
    std::string genesis_hash = genesis_block_contents.hash_contents();

    Block genesis_block(genesis_hash, genesis_block_contents);

    this->chain.push_back(genesis_block);
}
