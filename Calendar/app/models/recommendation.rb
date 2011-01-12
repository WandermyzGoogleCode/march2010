# Table schema: (event_id: integer, group_id: integer, user_id: integer, admin_id: integer, extra_info: text, timestamp: integer)
class Recommendation < ActiveRecord::Base
  belongs_to :event
  belongs_to :group
  belongs_to :admin, :class_name => "User"
end
