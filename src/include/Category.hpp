#ifndef CATEGORY_HPP
#define CATEGORY_HPP

// Categories in scene node, used to send commands
namespace Category {
	enum Type {
		None = 0,
		Scene = 1 << 0,
		Player = 1 << 1,
		Worker = 1 << 2,
		SelectedWorker = 1 << 3,
	};
}



#endif /* CATEGORY_HPP */
