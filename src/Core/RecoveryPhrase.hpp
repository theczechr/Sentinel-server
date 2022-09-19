#include <string>

class RecoveryPhrase {
  public:
	RecoveryPhrase() {}
	RecoveryPhrase(std::string recovery_phrase) : recovery_phrase_(recovery_phrase) {}

	operator RecoveryPhrase() const {
		return RecoveryPhrase(recovery_phrase_);
	}

	operator std::string() const {
		return recovery_phrase_;
	}

	// Check

  private:
	std::string recovery_phrase_;
	bool		enabled_;
};
