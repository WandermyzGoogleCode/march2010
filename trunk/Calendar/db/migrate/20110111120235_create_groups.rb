class CreateGroups < ActiveRecord::Migration
  def self.up
    create_table :groups do |t|
      t.string :name
      t.string :identifier
      t.text :extra_info
      t.integer :creator_id

      t.timestamps
    end
  end

  def self.down
    drop_table :groups
  end
end
