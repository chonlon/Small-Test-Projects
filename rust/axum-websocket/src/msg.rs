use serde::{Deserialize, Serialize};
use std::time::{SystemTime, UNIX_EPOCH};

#[derive(Debug, Clone, Eq, PartialEq, Serialize, Deserialize)]
pub struct Msg {
    pub room: String,
    pub username: String,
    // assume username is unique and not empty, in a real app we would get it from db
    pub timestamp: u64,
    pub chat_message: ChatMessage,
}

#[derive(Debug, Clone, Eq, PartialEq, Serialize, Deserialize)]
pub enum ChatMessage {
    Join,
    Leave,
    Say(String),
}

impl<T> From<T> for Msg
where
    T: AsRef<str>,
{
    fn from(chat_message: T) -> Self {
        serde_json::from_str(chat_message.as_ref()).unwrap()
    }
}

impl From<&Msg> for String {
    fn from(msg: &Msg) -> Self {
        serde_json::to_string(&msg).unwrap()
    }
}

impl Msg {
    pub fn new(room: String, username: String, chat_message: ChatMessage) -> Self {
        Msg {
            room,
            username,
            timestamp: SystemTime::now()
                .duration_since(UNIX_EPOCH)
                .unwrap()
                .as_secs(),
            chat_message,
        }
    }

    fn join<T: AsRef<str>>(room: T, username: T) -> Self {
        Msg::new(
            room.as_ref().to_string(),
            username.as_ref().to_string(),
            ChatMessage::Join,
        )
    }

    fn leave<T: AsRef<str>>(room: T, username: T) -> Self {
        Msg::new(
            room.as_ref().to_string(),
            username.as_ref().to_string(),
            ChatMessage::Leave,
        )
    }

    fn chat<T: AsRef<str>>(room: T, username: T, chat_message: T) -> Self {
        Msg::new(
            room.as_ref().to_string(),
            username.as_ref().to_string(),
            ChatMessage::Say(chat_message.as_ref().to_string()),
        )
    }
}

#[cfg(test)]
mod test {
    fn test_msg() -> super::Msg {
        super::Msg {
            room: "test".to_string(),
            username: "test".to_string(),
            timestamp: 0,
            chat_message: super::ChatMessage::Join,
        }
    }

    #[test]
    fn test_from_str() {
        let msg = test_msg();
        let msg_str = String::from(&msg);
        let msg_from_str = super::Msg::from(msg_str);
        assert_eq!(msg, msg_from_str);
    }

    #[test]
    fn test_from_msg() {
        let msg = test_msg();
        let msg_str: String = (&msg).into();
        let msg_from_str = super::Msg::from(msg_str);
        assert_eq!(msg, msg_from_str);
    }
}
